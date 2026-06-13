#include "Renderer.h"

sf::Color Renderer::GetColor(
    int color
)
{
    switch (color)
    {
    case 0:
        return sf::Color::Red;

    case 1:
        return sf::Color::Green;

    case 2:
        return sf::Color::Blue;

    case 3:
        return sf::Color::Yellow;

    case 4:
        return sf::Color(
            200,
            0,
            200
        );

    default:
        return sf::Color::Black;
    }
}

void Renderer::Draw(
    sf::RenderWindow& window,
    const Board& board
)
{
    int size =
        board.GetSize();

    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            sf::RectangleShape rect;

            rect.setSize(
                sf::Vector2f(
                    CELL_SIZE - 2,
                    CELL_SIZE - 2
                )
            );

            rect.setPosition(
                (float)x * CELL_SIZE,
                (float)y * CELL_SIZE
            );

            rect.setFillColor(
                GetColor(
                    board.GetColor(
                        x,
                        y
                    )
                )
            );

            window.draw(rect);
        }
    }
}