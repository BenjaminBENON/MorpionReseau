// Client side C program to demonstrate Socket
// programming
#include "client.h"

Client::Client() {

    // Initialize Winsock
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "WSAStartup failed\n";
    }

    // Create a dummy window for socket events handling
    HWND hWnd = MakeWorkerWindow();
    if (hWnd == NULL) {
        std::cerr << "CreateWindow failed\n";
        WSACleanup();
    }

    // Associate window with socket for asynchronous operations
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    WSAAsyncSelect(clientSocket, hWnd, WM_SOCKET, FD_CONNECT);

    // Create socket

    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed\n";
        DestroyWindow(hWnd);
        WSACleanup();
    }

    // Server address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("10.1.144.42"); // Assuming server is running locally
    serverAddr.sin_port = htons(PORT);

    // Connect to server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        if (WSAGetLastError() != WSAEWOULDBLOCK) {
            std::cerr << "Connection failed\n";
            closesocket(clientSocket);
            DestroyWindow(hWnd);
            WSACleanup();
        }
    }

    std::cout << "Connecting to server...\n";

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

}

LRESULT CALLBACK ClientWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_SOCKET:
        switch (WSAGETSELECTEVENT(lParam)) {
        case FD_CONNECT:
            std::cout << "Connected to server\n";

            break;
            //case FD_READ:
            //    // Handle reading data from server
            //    char buffer[1024] = { 0 };
            //    int valread = recv(wParam, buffer, sizeof(buffer), 0);
            //    if (valread > 0) {
            //        std::cout << "Message from server: " << buffer << std::endl;
            //    }
            //    break;
            //case FD_WRITE:
            //    std::cout << "Ready to write to server\n";
            //    break;
            //case FD_CLOSE:
            //    std::cout << "Connection closed\n";
            //    PostQuitMessage(0);
            //    break;
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