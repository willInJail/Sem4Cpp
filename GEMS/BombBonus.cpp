#include "BombBonus.h"
#include "Board.h"

#include <random>

void BombBonus::Apply(
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

    for (int i = 0; i < 5; i++)
    {
        int rx = dist(gen);
        int ry = dist(gen);

        board.SetColor(
            rx,
            ry,
            -1
        );
    }
}