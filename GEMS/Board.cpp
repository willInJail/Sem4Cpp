#include "Board.h"
#include <ctime>
#include <cstdlib>

Board::Board()
{
    srand((unsigned)time(0));

    cells.resize(SIZE, std::vector<int>(SIZE));

    GenerateBoard();
}

void Board::GenerateBoard()
{
    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            cells[y][x] = rand() % 5;
        }
    }
}

sf::Color Board::GetColor(int id)
{
    switch (id)
    {
    case 0: return sf::Color::Red;
    case 1: return sf::Color::Green;
    case 2: return sf::Color::Blue;
    case 3: return sf::Color::Yellow;
    case 4: return sf::Color(200, 0, 200);
    default: return sf::Color::Black;
    }
}

void Board::Draw(sf::RenderWindow& window)
{
    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            sf::RectangleShape rect;

            rect.setSize(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));

            rect.setPosition(
                (float)x * CELL_SIZE,
                (float)y * CELL_SIZE
            );

            rect.setFillColor(GetColor(cells[y][x]));

            if (hasSelection &&
                selected.x == x &&
                selected.y == y)
            {
                rect.setOutlineThickness(4);
                rect.setOutlineColor(sf::Color::White);
            }

            window.draw(rect);
        }
    }
}

bool Board::IsAdjacent(sf::Vector2i a, sf::Vector2i b)
{
    int dx = abs(a.x - b.x);
    int dy = abs(a.y - b.y);

    return dx + dy == 1;
}

void Board::Swap(sf::Vector2i a, sf::Vector2i b)
{
    std::swap(cells[a.y][a.x], cells[b.y][b.x]);
}

void Board::HandleClick(int mouseX, int mouseY)
{
    int x = mouseX / CELL_SIZE;
    int y = mouseY / CELL_SIZE;

    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE)
        return;

    if (!hasSelection)
    {
        selected = sf::Vector2i(x, y);
        hasSelection = true;
    }
    else
    {
        sf::Vector2i second(x, y);

        if (IsAdjacent(selected, second))
        {
            Swap(selected, second);

            bool found = true;

            while (found)
            {
                std::vector<std::vector<bool>> marked(
                    SIZE,
                    std::vector<bool>(SIZE, false)
                );

                found = FindMatches(marked);

                if (found)
                {
                    RemoveMatches(marked);
                    DropCells();
                }
            }
        }

        hasSelection = false;
    }
}

bool Board::FindMatches(std::vector<std::vector<bool>>& marked)
{
    bool found = false;

    // Горизонталь
    for (int y = 0; y < SIZE; y++)
    {
        int count = 1;

        for (int x = 1; x < SIZE; x++)
        {
            if (cells[y][x] == cells[y][x - 1])
            {
                count++;
            }
            else
            {
                count = 1;
            }

            if (count >= 3)
            {
                found = true;

                for (int k = 0; k < count; k++)
                {
                    marked[y][x - k] = true;
                }
            }
        }
    }

    // Вертикаль
    for (int x = 0; x < SIZE; x++)
    {
        int count = 1;

        for (int y = 1; y < SIZE; y++)
        {
            if (cells[y][x] == cells[y - 1][x])
            {
                count++;
            }
            else
            {
                count = 1;
            }

            if (count >= 3)
            {
                found = true;

                for (int k = 0; k < count; k++)
                {
                    marked[y - k][x] = true;
                }
            }
        }
    }

    return found;
}

void Board::RemoveMatches(const std::vector<std::vector<bool>>& marked)
{
    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            if (marked[y][x])
            {
                int originalColor = cells[y][x];

                cells[y][x] = -1;

                int chance = rand() % 100;

                // Бонус перекраски
                if (chance < 10)
                {
                    TriggerBonus(x, y, originalColor);
                }

                // Бомба
                else if (chance < 15)
                {
                    TriggerBomb();
                }
            }
        }
    }
}

void Board::DropCells()
{
    for (int x = 0; x < SIZE; x++)
    {
        int empty = SIZE - 1;

        for (int y = SIZE - 1; y >= 0; y--)
        {
            if (cells[y][x] != -1)
            {
                cells[empty][x] = cells[y][x];

                if (empty != y)
                    cells[y][x] = -1;

                empty--;
            }
        }

        while (empty >= 0)
        {
            cells[empty][x] = rand() % 5;
            empty--;
        }
    }
}

void Board::TriggerBonus(int x, int y, int color)
{
    for (int i = 0; i < 3; i++)
    {
        int rx = rand() % SIZE;
        int ry = rand() % SIZE;

        if (abs(rx - x) <= 3 &&
            abs(ry - y) <= 3)
        {
            if (!(abs(rx - x) + abs(ry - y) == 1))
            {
                cells[ry][rx] = color;
            }
        }
    }
}

void Board::TriggerBomb()
{
    for (int i = 0; i < 5; i++)
    {
        int x = rand() % SIZE;
        int y = rand() % SIZE;

        cells[y][x] = -1;
    }
}