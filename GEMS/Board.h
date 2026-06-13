#pragma once

#include <vector>
#include "Gem.h"

class Board
{
private:
    static const int SIZE = 8;

    std::vector<std::vector<Gem>> cells;

public:
    Board();

    void Generate();

    int GetSize() const;

    int GetColor(int x, int y) const;

    void SetColor(int x, int y, int color);

    void Swap(int x1, int y1, int x2, int y2);

    bool IsInside(int x, int y) const;
};