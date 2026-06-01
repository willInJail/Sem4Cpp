#pragma once

#include <SFML/Graphics.hpp>

enum BlockType
{
    NORMAL,
    UNBREAKABLE,
    BONUS_BLOCK,
    SPEED_BLOCK
};

class Block
{
public:
    sf::RectangleShape shape;

    BlockType type;

    int health;

    bool alive;

    Block()
    {
        alive = true;
        health = 1;
        type = NORMAL;
    }
};