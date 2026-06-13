#pragma once

#include "Constants.h"

class Ball
{
public:
    float x;
    float y;

    float dx;
    float dy;

    float radius;

    bool sticky;
    bool attached;

    Ball()
    {
        x = START_BALL_X;
        y = START_BALL_Y;

        dx = START_BALL_SPEED_X;

        dy = START_BALL_SPEED_Y;

        radius = 10;

        sticky = false;
        attached = false;
    }
};