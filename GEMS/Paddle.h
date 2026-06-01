#pragma once

class Paddle
{
public:
    float x;
    float y;

    float width;
    float height;

    float speed;

    Paddle()
    {
        width = 120;
        height = 20;

        x = 340;
        y = 550;

        speed = 8;
    }
};