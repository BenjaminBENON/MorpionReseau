#include "socket_thread.h"




socket_thread::socket_thread()
{
}


socket_thread::~socket_thread()
{
}


void socket_thread::OnEnter()
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
}

