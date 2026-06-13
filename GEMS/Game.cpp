#include "Game.h"
#include "Constants.h"

#include <ctime>
#include <cstdlib>

Game::Game()
{
    srand((unsigned)time(0));

    score = 0;
    lives = 3;

    bottomShield = false;

    CreateBlocks();
}

void Game::CreateBlocks()
{
    const int rows = ROWS;
    const int cols = COLS;

    const int width = WIDTH_1;
    const int height = HEIGHT_1;

    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            Block block;

            block.shape.setSize(
                sf::Vector2f(width - 2, height - 2)
            );

            block.shape.setPosition(
                40 + x * width,
                40 + y * height
            );

            int r = rand() % 100;

            if (r < 10)
            {
                block.type = UNBREAKABLE;
                block.shape.setFillColor(sf::Color(100, 100, 100));
            }
            else if (r < 25)
            {
                block.type = BONUS_BLOCK;
                block.shape.setFillColor(sf::Color::Green);
            }
            else if (r < 40)
            {
                block.type = SPEED_BLOCK;
                block.shape.setFillColor(sf::Color::Red);
            }
            else
            {
                block.type = NORMAL;
                block.shape.setFillColor(sf::Color::Blue);
            }

            if (block.type == UNBREAKABLE)
            {
                block.health = 9999;
            }
            else
            {
                block.health = 3;
            }

            blocks.push_back(block);
        }
    }
}

sf::FloatRect Game::GetBallRect()
{
    return sf::FloatRect(
        ball.x - ball.radius,
        ball.y - ball.radius,
        ball.radius * 2,
        ball.radius * 2
    );
}

void Game::MoveLeft()
{
    paddle.x -= paddle.speed;

    if (paddle.x < 0)
        paddle.x = 0;
}

void Game::MoveRight()
{
    paddle.x += paddle.speed;

    if (paddle.x + paddle.width > WINDOW_WIDTH)
        paddle.x = WINDOW_WIDTH - paddle.width;
}

void Game::Update()
{
    UpdateBall();

    CheckWallCollision();

    CheckPaddleCollision();

    CheckBlockCollision();

    CheckBonusCollision();
}

void Game::ReleaseBall()
{
    if (ball.attached)
    {
        ball.attached = false;

        ball.dx = 4;
        ball.dy = -4;
    }
}

void Game::UpdateBall()
{
    if (ball.attached)
    {
        ball.x = paddle.x + paddle.width / 2;
        ball.y = paddle.y - 15;

        return;
    }

    ball.x += ball.dx;
    ball.y += ball.dy;
}

void Game::CheckWallCollision()
{
    if (ball.x - ball.radius < 0)
    {
        ball.dx = -ball.dx;
    }

    if (ball.x + ball.radius > WINDOW_WIDTH)
    {
        ball.dx = -ball.dx;
    }

    if (ball.y - ball.radius < 0)
    {
        ball.dy = -ball.dy;
    }

    if (ball.y > WINDOW_HEIGHT)
    {
        if (bottomShield)
        {
            bottomShield = false;

            ball.dy = -ball.dy;
        }
        else
        {
            lives--;

            score -= 5;

            ball.x = START_BALL_X;
            ball.y = START_BALL_Y;

            ball.dx = START_BALL_SPEED_X;

            ball.dy = START_BALL_SPEED_Y;
        }
    }
}

void Game::CheckPaddleCollision()
{
    sf::FloatRect paddleRect(
        paddle.x,
        paddle.y,
        paddle.width,
        paddle.height
    );

    if (GetBallRect().intersects(paddleRect))
    {
        ball.dy = -abs(ball.dy);

        if (ball.sticky)
        {
            ball.attached = true;
        }
    }
}

void Game::CheckBlockCollision()
{
    for (size_t i = 0; i < blocks.size(); i++)
    {
        if (!blocks[i].alive)
            continue;

        if (GetBallRect().intersects(
            blocks[i].shape.getGlobalBounds()))
        {
            ball.dy = -ball.dy;

            if (blocks[i].type == UNBREAKABLE)
                return;

            blocks[i].health--;

            score++;

            if (blocks[i].type == SPEED_BLOCK)
            {
                ball.dx *= SPEED_BLOCK_VELOCITY;
                ball.dy *= SPEED_BLOCK_VELOCITY;
            }

            if (blocks[i].health <= 0)
            {
                if (blocks[i].type == BONUS_BLOCK)
                {
                    SpawnBonus(
                        blocks[i].shape.getPosition().x,
                        blocks[i].shape.getPosition().y
                    );
                }

                blocks[i].alive = false;
            }

            return;
        }
    }
}

void Game::SpawnBonus(float x, float y)
{
    Bonus bonus;

    bonus.x = x;
    bonus.y = y;

    int r = rand() % 6;

    switch (r)
    {
    case 0:
        bonus.type = BIG_PADDLE;
        break;

    case 1:
        bonus.type = SMALL_PADDLE;
        break;

    case 2:
        bonus.type = FAST_BALL;
        break;

    case 3:
        bonus.type = STICKY_BALL;
        break;

    case 4:
        bonus.type = BOTTOM_SHIELD;
        break;

    case 5:
        bonus.type = RANDOM_DIRECTION;
        break;
    }

    bonuses.push_back(bonus);
}

void Game::CheckBonusCollision()
{
    sf::FloatRect paddleRect(
        paddle.x,
        paddle.y,
        paddle.width,
        paddle.height
    );

    for (size_t i = 0; i < bonuses.size(); i++)
    {
        if (!bonuses[i].active)
            continue;

        bonuses[i].y += bonuses[i].speed;

        sf::FloatRect bonusRect(
            bonuses[i].x,
            bonuses[i].y,
            BONUS_SIZE,
            BONUS_SIZE
        );

        if (bonusRect.intersects(paddleRect))
        {
            ApplyBonus(
                bonuses[i].type
            );

            bonuses[i].active = false;
        }

        if (bonuses[i].y > WINDOW_HEIGHT)
        {
            bonuses[i].active = false;
        }
    }
}

void Game::ApplyBonus(BonusType type)
{
    switch (type)
    {
    case BIG_PADDLE:
        paddle.width += BIG_PADDLE_BONUS;
        break;

    case SMALL_PADDLE:
        paddle.width -= BIG_PADDLE_BONUS;

        if (paddle.width < MIN_PADDLE_WIDTH)
            paddle.width = MIN_PADDLE_WIDTH;
        break;

    case FAST_BALL:
        ball.dx *= SPEED_BLOCK_VELOCITY;
        ball.dy *= SPEED_BLOCK_VELOCITY;
        break;

    case STICKY_BALL:
        ball.sticky = true;
        break;

    case BOTTOM_SHIELD:
        bottomShield = true;
        break;

    case RANDOM_DIRECTION:

        if (rand() % 2)
            ball.dx = -ball.dx;
        else
            ball.dy = -ball.dy;

        break;
    }
}

void Game::Draw(sf::RenderWindow& window)
{
    sf::RectangleShape paddleShape;

    paddleShape.setSize(
        sf::Vector2f(
            paddle.width,
            paddle.height
        )
    );

    paddleShape.setPosition(
        paddle.x,
        paddle.y
    );

    paddleShape.setFillColor(
        sf::Color::White
    );

    window.draw(paddleShape);

    sf::CircleShape circle;

    circle.setRadius(ball.radius);

    circle.setPosition(
        ball.x - ball.radius,
        ball.y - ball.radius
    );

    circle.setFillColor(
        sf::Color::Yellow
    );

    window.draw(circle);

    for (size_t i = 0; i < blocks.size(); i++)
    {
        if (blocks[i].alive)
        {
            window.draw(
                blocks[i].shape
            );
        }
    }

    for (size_t i = 0; i < bonuses.size(); i++)
    {
        if (!bonuses[i].active)
            continue;

        sf::RectangleShape bonusShape;

        bonusShape.setSize(
            sf::Vector2f(
                BONUS_SIZE,
                BONUS_SIZE
            )
        );

        bonusShape.setPosition(
            bonuses[i].x,
            bonuses[i].y
        );

        bonusShape.setFillColor(
            sf::Color::Magenta
        );

        window.draw(bonusShape);
    }

    if (bottomShield)
    {
        sf::RectangleShape shield;

        shield.setSize(
            sf::Vector2f(WINDOW_WIDTH, 5)
        );

        shield.setPosition(
            0,
            WINDOW_HEIGHT - 5
        );

        shield.setFillColor(
            sf::Color::Green
        );

        window.draw(shield);
    }
}