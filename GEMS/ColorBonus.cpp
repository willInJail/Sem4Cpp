#include "ColorBonus.h"
#include "Board.h"

#include <random>

void ColorBonus::Apply(
    Board& board,
    int x,
    int y,
    int color
)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int>
        dist(0, board.GetSize() - 1);

    int painted = 0;

    while (painted < 3)
    {
        int rx = dist(gen);
        int ry = dist(gen);

        if (!board.IsInside(rx, ry))
            continue;

        if (abs(rx - x) + abs(ry - y) == 1)
            continue;

        board.SetColor(
            rx,
            ry,
            color
        );

        painted++;
    }
}