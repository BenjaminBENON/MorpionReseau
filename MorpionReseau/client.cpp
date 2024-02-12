#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <cstring>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#pragma comment(lib, "Ws2_32.lib")

#define PORT 7985
#define WM_SOCKET (WM_USER + 1)

LRESULT CALLBACK ClientWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HWND MakeWorkerWindow();

using namespace rapidjson;

int main() {
    // Initialize Winsock
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }

    // Create a dummy window for socket events handling
    HWND hWnd = MakeWorkerWindow();
    if (hWnd == NULL) {
        std::cerr << "CreateWindow failed\n";
        WSACleanup();
        return 1;
    }

    // Associate window with socket for asynchronous operations
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Create socket
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed\n";
        DestroyWindow(hWnd);
        WSACleanup();
        return 1;
    }

    // Server address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("10.1.144.30"); // Assuming server is running locally
    serverAddr.sin_port = htons(PORT);

    // Connect to server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        if (WSAGetLastError() != WSAEWOULDBLOCK) {
            std::cerr << "Connection failed\n";
            closesocket(clientSocket);
            DestroyWindow(hWnd);
            WSACleanup();
            return 1;
        }
    }

    std::cout << "Connecting to server...\n";

    WSAAsyncSelect(clientSocket, hWnd, WM_SOCKET, FD_READ);
    // Create JSON object with name and surname
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

    std::string name;
    std::cout << "Entrez votre pseudo : ";
    std::cin >> name;

    Value position(kArrayType); // Crée un tableau JSON

    // Ajoute les coordonnées x et y au tableau JSON
    position.PushBack(1.6439f, allocator);
    position.PushBack(12.42039f, allocator);

    document.AddMember("Name", StringRef(name.c_str()), allocator);
    document.AddMember("MousePosition", position, allocator);

    // Convert JSON object to string
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    std::string jsonString = buffer.GetString();


    // Send JSON string to server
    send(clientSocket, jsonString.c_str(), jsonString.length(), 0);


    // Message loop to handle socket events
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Close socket and clean up Winsock
    closesocket(clientSocket);
    DestroyWindow(hWnd);
    WSACleanup();

    return 0;
}

LRESULT CALLBACK ClientWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_SOCKET:
        switch (WSAGETSELECTEVENT(lParam)) {
            /*case FD_CONNECT:
                std::cout << "Connected to server\n";
                break;*/
        case FD_READ:
        {
            char buffer[1024] = { 0 };
            int valread = recv(wParam, buffer, sizeof(buffer), 0);
            if (valread > 0)
            {
                std::cout << "Send message to server: " << buffer << std::endl;

            }
            break;
        }
        case FD_WRITE:
            std::cout << "Ready to write to server" << std::endl;
            break;
        default:
            std::cerr << "Unexpected event on socket\n";
            break;
        }
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

HWND MakeWorkerWindow()
{
    WNDCLASS wndclass;
    const char* ProviderClass = "AsyncSelect";
    HWND Window;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = ClientWndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = NULL;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = L"SocketWindowClass";

    if (RegisterClass(&wndclass) == 0)
    {
        printf("RegisterClass() failed with error %d\n", GetLastError());
        return NULL;
    }
    else
    {
        printf("RegisterClass() is OK!\n");
    }

    // Create a window
    if ((Window = CreateWindow(
        L"SocketWindowClass",
        L"",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        NULL,
        NULL)) == NULL)
    {
        printf("CreateWindow() failed with error %d\n", GetLastError());
        return NULL;
    }
    else
    {
        printf("CreateWindow() is OK!\n");
    }
    return Window;
}