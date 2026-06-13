#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Constants.h"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(
            WINDOW_WIDTH,
            WINDOW_HEIGHT
        ),
        "Arkanoid"
    );

    window.setFramerateLimit(60);

    Game game;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            game.MoveLeft();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            game.MoveRight();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            game.ReleaseBall();
        }

        game.Update();

        window.clear();

        game.Draw(window);

        window.display();
    }

    return 0;
}