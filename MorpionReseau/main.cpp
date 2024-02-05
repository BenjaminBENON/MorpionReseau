#include "GameObject.h"
#include "GameInstance.h"

#include <iostream>
#include <vector>


int main()
{

    GameInstance oGame(600, 600);

    sf::RenderWindow window(sf::VideoMode(oGame.x, oGame.y), "MORPION");

    std::vector<GameObject*> list = { nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr };
    int click = 0;

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
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    click++;
                    oGame.switchPlayer();
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    list[click - 1] = new GameObject(mousePosition, oGame);
                }
            }
        }

        if (click > 0)
        {
            for (int i = 0; i < click; i++)
            {
                window.draw(*(list[i]->pShape));
            }
        }
        window.display();

        if (click == 9)
        {
            window.close();
        }
    }

    return 0;
}