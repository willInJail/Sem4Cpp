#pragma once

#include <vector>

#include "Board.h"
#include "Bonus.h"

class Game
{
private:

    Board board;

    int selectedX;
    int selectedY;

    bool hasSelection;

public:

    Game();

    Board& GetBoard();

    void HandleClick(
        int mouseX,
        int mouseY
    );

private:

    bool IsAdjacent(
        int x1,
        int y1,
        int x2,
        int y2
    );

    bool FindMatches();

    void DFS(
        int x,
        int y,
        int color,
        std::vector<std::vector<bool>>& visited,
        std::vector<std::pair<int, int>>& component
    );

    void RemoveCells(
        const std::vector<
        std::pair<int, int>>&cells
    );

    void DropCells();

    void ApplyRandomBonus(
        int x,
        int y,
        int color
    );
};