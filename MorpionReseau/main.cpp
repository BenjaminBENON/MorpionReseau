#include "GameObject.h"
#include "GameInstance.h"
#include "client.h"
#include <iostream>
#include <vector>

int main()
{
    GameInstance oGame(600, 600);

    sf::RenderWindow window(sf::VideoMode(oGame.x, oGame.y), "MORPION");
    new Client();
    std::vector<GameObject*> list;
    int click = 0;

        sf::Event event;
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }

            if (event.type == sf::Event::MouseButtonPressed && click < 9) // Vérifie si le jeu n'est pas terminé
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    int row = mousePosition.y / (oGame.y / 3);
                    int col = mousePosition.x / (oGame.x / 3);

                    // Vérifie si la case est vide
                    if (oGame.getBoard()[row][col] == -1) {
                        click++;
                        oGame.switchPlayer();
                        list.push_back(new GameObject(mousePosition, oGame));
                        oGame.getBoard()[row][col] = oGame.getPlayerTurn();

                        // Vérifie s'il y a un vainqueur après chaque coup
                        if (oGame.checkWin(oGame.getPlayerTurn())) {
                            // Affiche le message de victoire
                            std::cout << "Joueur " << oGame.getPlayerTurn() << " a gagne !" << std::endl;
                            window.close();
                        }
                    }
                }
            }
        }

        // Affiche le plateau de jeu
        if (click > 0)
        {
            for (int i = 0; i < click; i++)
            {
                if (list[i] != nullptr) {
                    window.draw(*(list[i]->pShape));
                }
            }
        }

        window.display();

        // Vérifie s'il y a égalité
        if (click == 9) {
            std::cout << "Match nul !" << std::endl;
            window.close();
        }
    }

    return 0;
}
