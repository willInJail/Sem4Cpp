#include "Board.h"

#include <random>

Board::Board()
{
    cells.resize(
        SIZE,
        std::vector<Gem>(SIZE)
    );

    Generate();
}

void Board::Generate()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int>
        dist(0, 4);

    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            cells[y][x].color =
                dist(gen);
        }
    }
}

int Board::GetSize() const
{
    return SIZE;
}

int Board::GetColor(
    int x,
    int y
) const
{
    return cells[y][x].color;
}

void Board::SetColor(
    int x,
    int y,
    int color
)
{
    cells[y][x].color = color;
}

void Board::Swap(
    int x1,
    int y1,
    int x2,
    int y2
)
{
    std::swap(
        cells[y1][x1],
        cells[y2][x2]
    );
}

bool Board::IsInside(
    int x,
    int y
) const
{
    return x >= 0 &&
        x < SIZE&&
        y >= 0 &&
        y < SIZE;
}