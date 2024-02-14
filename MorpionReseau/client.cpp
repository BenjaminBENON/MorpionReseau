
#include "GameInstance.h"
#include "socket.h"
#include "socket_thread.h"


using namespace rapidjson;


int main() 
{
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }

    //Creation du 2eme THREAD
    socket_thread socketThread;

    //Initialisation de la partie
    GameInstance oGame(600, 600);
    sf::RenderWindow window(sf::VideoMode(oGame.x, oGame.y), "MORPION");


    //int click = 0;
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
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    //Communiquer entre threads pour donner la position à l'autre thread
                    std::cout << mousePosition.x << " et " << mousePosition.y << std::endl;
                }
            }
        }
        oGame.drawWindow(window);
        window.display();
    }

    //ENVOYER UN SEND ICI directement ou faire un petit tricks

    WaitForSingleObject(socketThread.getThreadHandle(), INFINITE);

    WSACleanup();
    return 0;
}
