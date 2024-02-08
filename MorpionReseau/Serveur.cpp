#include "Serveur.h"

#define PORT 7985
#define WM_SOCKET (WM_USER + 1)

Serveur::Serveur()
{

}



int Serveur::createServer()
{
    // Initialize Winsock
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("WSAStartup failed\n");
        exit(EXIT_FAILURE);
    }

    HWND hWnd = MakeWorkerWindow();

    // Create server socket
    SOCKET server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Bind server socket
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    bind(server_fd, (struct sockaddr*)&address, sizeof(address));

    // Listen for incoming connections
    listen(server_fd, 3);

    // Associate server socket with window for asynchronous operations
    WSAAsyncSelect(server_fd, hWnd, WM_SOCKET, FD_ACCEPT);

    // Message loop to handle socket events
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Close server socket and clean up Winsock
    closesocket(server_fd);
    WSACleanup();

    return 0;
}

LRESULT CALLBACK Serveur::SocketWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
    switch (uMsg)
    {
    case WM_SOCKET:
    {
        switch (WSAGETSELECTEVENT(lParam))
        {
        case FD_ACCEPT:
        {
            // Accept incoming connection
            SOCKET new_socket = accept(wParam, NULL, NULL);
            std::cout << "New connection accepted" << std::endl;

            // Associate new socket with window for asynchronous operations
            WSAAsyncSelect(new_socket, hwnd, WM_SOCKET, FD_READ | FD_WRITE);
            break;
        }
        case FD_READ:
        {
            char buffer[1024] = { 0 };
            int valread = recv(wParam, buffer, sizeof(buffer), 0);
            if (valread > 0)
            {
                std::cout << "Received message from client: " << buffer << std::endl;
                // Echo received message back to client
                send(wParam, buffer, strlen(buffer), 0);
            }
            break;
        }
        case FD_WRITE:
            std::cout << "Ready to write to client" << std::endl;
            break;
        default:
            std::cout << "Unexpected event on socket" << std::endl;
            break;
        }
    }
    break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

HWND Serveur::MakeWorkerWindow()
{
    WNDCLASS wndclass;
    const char* ProviderClass = "AsyncSelect";
    HWND Window;


    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = SocketWndProc;
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
