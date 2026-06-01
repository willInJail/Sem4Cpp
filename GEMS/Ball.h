#pragma once

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
        x = 400;
        y = 300;

        dx = 4;
        dy = -4;

        radius = 10;

        sticky = false;
        attached = false;
    }
};