#pragma once

enum BonusType
{
    BIG_PADDLE,
    SMALL_PADDLE,
    FAST_BALL,
    STICKY_BALL,
    BOTTOM_SHIELD,
    RANDOM_DIRECTION
};

class Bonus
{
public:
    float x;
    float y;

    float speed;

    BonusType type;

    bool active;

    Bonus()
    {
        speed = 3;
        active = true;
    }
};