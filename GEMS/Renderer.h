#pragma once

#include <SFML/Graphics.hpp>

#include "Board.h"

class Renderer
{
private:
    static const int CELL_SIZE = 64;

public:

    void Draw(
        sf::RenderWindow& window,
        const Board& board
    );

private:

    sf::Color GetColor(
        int color
    );
};