#pragma once

#include "Bonus.h"

class BombBonus : public Bonus
{
public:
    void Apply(
        Board& board,
        int x,
        int y,
        int color
    ) override;
};