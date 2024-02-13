#include "GameObject.h"
#include "GameInstance.h"
#include "Serveur.h"

#include <iostream>
#include <vector>


DWORD WINAPI ThreadFunction1(LPVOID lpParam) 
{
    Serveur* pServer = new Serveur;
    pServer->createServer();

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    pServer->~Serveur();
    return 0;
}


DWORD WINAPI ThreadFunction2(LPVOID lpParam) 
{
    GameInstance oGame(600, 600);

    sf::RenderWindow window(sf::VideoMode(oGame.x, oGame.y), "MORPION");

    std::vector<GameObject*> list;
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

            if (event.type == sf::Event::MouseButtonPressed && click < 9) // Vérifie si le jeu n'est pas terminé
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    int row = mousePosition.y / (oGame.y / 3);
                    int col = mousePosition.x / (oGame.x / 3);

                    // Vérifie si la case est vide
                    if (oGame.getBoard()[row][col] == -1)
                    {
                        click++;
                        oGame.switchPlayer();
                        list.push_back(new GameObject(mousePosition, oGame));
                        oGame.getBoard()[row][col] = oGame.getPlayerTurn();

                        // Vérifie s'il y a un vainqueur après chaque coup
                        if (oGame.checkWin(oGame.getPlayerTurn()))
                        {
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
                if (list[i] != nullptr)
                {
                    window.draw(*(list[i]->pShape));
                }
            }
        }

        window.display();

        // Vérifie s'il y a égalité
        if (click == 9)
        {
            std::cout << "Match nul !" << std::endl;
            window.close();
        }

    }

    return 0;
}


int main()
{
    // Initialize Winsock
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("WSAStartup failed\n");
        exit(EXIT_FAILURE);
    }


    // Handles pour les threads
    HANDLE hThread1, hThread2;
    // Créer les threads
    hThread1 = CreateThread(NULL, 0, ThreadFunction1, NULL, 0, NULL);
    hThread2 = CreateThread(NULL, 0, ThreadFunction2, NULL, 0, NULL);


    // Attendre la fin des threads
    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);
    // Fermer les handles des threads
    CloseHandle(hThread1);
    CloseHandle(hThread2);



    WSACleanup();
    return 0;
}

