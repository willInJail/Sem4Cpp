#include "Game.h"

#include "ColorBonus.h"
#include "BombBonus.h"

#include <random>

Game::Game()
{
    hasSelection = false;
}

Board& Game::GetBoard()
{
    return board;
}

bool Game::IsAdjacent(
    int x1,
    int y1,
    int x2,
    int y2
)
{
    int dx = abs(x1 - x2);
    int dy = abs(y1 - y2);

    return dx + dy == 1;
}

void Game::HandleClick(
    int mouseX,
    int mouseY
)
{
    const int CELL_SIZE = 64;

    int x = mouseX / CELL_SIZE;
    int y = mouseY / CELL_SIZE;

    if (!board.IsInside(x, y))
        return;

    if (!hasSelection)
    {
        selectedX = x;
        selectedY = y;

        hasSelection = true;
    }
    else
    {
        if (IsAdjacent(
            selectedX,
            selectedY,
            x,
            y))
        {
            board.Swap(
                selectedX,
                selectedY,
                x,
                y
            );

            while (FindMatches())
            {
                DropCells();
            }
        }

        hasSelection = false;
    }
}

void Game::DFS(
    int x,
    int y,
    int color,
    std::vector<std::vector<bool>>& visited,
    std::vector<std::pair<int, int>>& component
)
{
    if (!board.IsInside(x, y))
        return;

    if (visited[y][x])
        return;

    if (board.GetColor(x, y) != color)
        return;

    visited[y][x] = true;

    component.push_back(
        { x, y }
    );

    DFS(
        x + 1,
        y,
        color,
        visited,
        component
    );

    DFS(
        x - 1,
        y,
        color,
        visited,
        component
    );

    DFS(
        x,
        y + 1,
        color,
        visited,
        component
    );

    DFS(
        x,
        y - 1,
        color,
        visited,
        component
    );
}

bool Game::FindMatches()
{
    int size = board.GetSize();

    std::vector<std::vector<bool>>
        visited(
            size,
            std::vector<bool>(
                size,
                false
                )
        );

    bool found = false;

    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            if (visited[y][x])
                continue;

            int color =
                board.GetColor(x, y);

            if (color == -1)
                continue;

            std::vector<
                std::pair<int, int>
            > component;

            DFS(
                x,
                y,
                color,
                visited,
                component
            );

            if (component.size() >= 3)
            {
                found = true;

                RemoveCells(
                    component
                );
            }
        }
    }

    return found;
}

void Game::RemoveCells(
    const std::vector<
    std::pair<int, int>>&cellsToRemove
)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int>
        chance(0, 99);

    for (auto cell : cellsToRemove)
    {
        int x = cell.first;
        int y = cell.second;

        int color =
            board.GetColor(x, y);

        board.SetColor(
            x,
            y,
            -1
        );

        int value =
            chance(gen);

        Bonus* bonus = nullptr;

        if (value < 10)
        {
            bonus =
                new ColorBonus();
        }
        else if (value < 15)
        {
            bonus =
                new BombBonus();
        }

        if (bonus)
        {
            bonus->Apply(
                board,
                x,
                y,
                color
            );

            delete bonus;
        }
    }
}

void Game::DropCells()
{
    int size =
        board.GetSize();

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int>
        dist(0, 4);

    for (int x = 0; x < size; x++)
    {
        int empty =
            size - 1;

        for (
            int y = size - 1;
            y >= 0;
            y--
            )
        {
            if (
                board.GetColor(
                    x,
                    y
                ) != -1
                )
            {
                int color =
                    board.GetColor(
                        x,
                        y
                    );

                board.SetColor(
                    x,
                    empty,
                    color
                );

                if (empty != y)
                {
                    board.SetColor(
                        x,
                        y,
                        -1
                    );
                }

                empty--;
            }
        }

        while (empty >= 0)
        {
            board.SetColor(
                x,
                empty,
                dist(gen)
            );

            empty--;
        }
    }
}