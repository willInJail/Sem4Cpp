#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Renderer.h"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(
            512,
            512
        ),
        "GEMS"
    );

    Game game;

    Renderer renderer;

    while (window.isOpen())
    {
        sf::Event event;

        while (
            window.pollEvent(
                event
            )
            )
        {
            if (
                event.type ==
                sf::Event::Closed
                )
            {
                window.close();
            }

            if (
                event.type ==
                sf::Event::MouseButtonPressed
                )
            {
                if (
                    event.mouseButton.button ==
                    sf::Mouse::Left
                    )
                {
                    game.HandleClick(
                        event.mouseButton.x,
                        event.mouseButton.y
                    );
                }
            }
        }

        window.clear();

        renderer.Draw(
            window,
            game.GetBoard()
        );

        window.display();
    }

    return 0;
}