#include <SFML/Graphics.hpp>
#include "Board.h"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(512, 512),
        "GEMS"
    );

    Board board;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button ==
                    sf::Mouse::Left)
                {
                    board.HandleClick(
                        event.mouseButton.x,
                        event.mouseButton.y
                    );
                }
            }
        }

        window.clear();

        board.Draw(window);

        window.display();
    }

    return 0;
}