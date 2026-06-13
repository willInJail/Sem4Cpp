#pragma once

class Board;

class Bonus
{
public:
    virtual ~Bonus() {}

    virtual void Apply(
        Board& board,
        int x,
        int y,
        int color
    ) = 0;
};