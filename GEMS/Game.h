#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Ball.h"
#include "Paddle.h"
#include "Block.h"
#include "Bonus.h"

class Game
{
private:

    Ball ball;
    Paddle paddle;

    std::vector<Block> blocks;
    std::vector<Bonus> bonuses;

    int score;
    int lives;

    bool bottomShield;

public:

    Game();

    void Update();
    void Draw(sf::RenderWindow& window);

    void MoveLeft();
    void MoveRight();

    void ReleaseBall();

private:

    void CreateBlocks();

    void UpdateBall();

    void CheckWallCollision();

    void CheckPaddleCollision();

    void CheckBlockCollision();

    void CheckBonusCollision();

    void SpawnBonus(float x, float y);

    void ApplyBonus(BonusType type);

    sf::FloatRect GetBallRect();
};