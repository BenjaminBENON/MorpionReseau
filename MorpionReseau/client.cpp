
#include "GameInstance.h"
#include "socket.h"


using namespace rapidjson;


// Fonction exécutée par le premier thread
DWORD WINAPI ThreadFunction1(LPVOID lpParam) 
{
    socketClient client;
    client.createSocket();

    // Create JSON object with name and surname
    Document document;
    document.SetObject();
    Document::AllocatorType& allocator = document.GetAllocator();

    std::string name;
    std::cout << "Entrez votre pseudo : ";
    std::cin >> name;

    Value position(kArrayType); // Crée un tableau JSON

    // Ajoute les coordonnées x et y au tableau JSON
    position.PushBack(1.6439f, allocator);
    position.PushBack(12.42039f, allocator);

    document.AddMember("Name", StringRef(name.c_str()), allocator);
    document.AddMember("MousePosition", position, allocator);

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    document.Accept(writer);
    std::string jsonString = buffer.GetString();

    // Send JSON string to server
    send(client.clientSocket, jsonString.c_str(), jsonString.length(), 0);

    // Message loop to handle socket events
    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    client.~socketClient();

    return 0;
}

// Fonction exécutée par le deuxième thread
DWORD WINAPI ThreadFunction2(LPVOID lpParam) 
{
    GameInstance oGame(600, 600);
    sf::RenderWindow window(sf::VideoMode(oGame.x, oGame.y), "MORPION");

    int click = 0;
    while (window.isOpen())
    {
        // Close socket and clean up Winsock
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
    }

    return 0;
}


int main() 
{
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }

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

