#pragma once

#include "Bonus.h"

class ColorBonus : public Bonus
{
public:
    void Apply(
        Board& board,
        int x,
        int y,
        int color
    ) override;
};