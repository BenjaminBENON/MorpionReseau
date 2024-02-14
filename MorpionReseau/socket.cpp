#include "socket.h"


#define IPADRESS "192.168.0.14" //j'ai changé ca


socketClient::socketClient()
{
    HWND hWnd = MakeWorkerWindow();
}


socketClient::~socketClient()
{
	closesocket(clientSocket);
	DestroyWindow(hWnd);
}



LRESULT CALLBACK socketClient::ClientWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) 
    {
    case WM_SOCKET:
        switch (WSAGETSELECTEVENT(lParam))
        {
        case FD_CONNECT:// J ai remis ca à voir si ca ne fait pas buguer
        {
            std::cout << "Connected to server\n";
            break;
        }
        case FD_READ:
        {
            char buffer[1024] = { 0 };
            int valread = recv(wParam, buffer, sizeof(buffer), 0);
            if (valread > 0)
            {
                std::cout << "Message received from server " << buffer << std::endl;

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



HWND socketClient::MakeWorkerWindow()
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




void socketClient::createSocket()
{
    // Associate window with socket for asynchronous operations
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Server address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(IPADRESS); // Assuming server is running locally
    serverAddr.sin_port = htons(PORT);

    // Connect to server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) 
    {
        if (WSAGetLastError() != WSAEWOULDBLOCK) 
        {
            std::cerr << "Connection failed\n";
            closesocket(clientSocket);
            DestroyWindow(hWnd);
            WSACleanup();
            return;
        }
    }

    std::cout << "Connecting to server...\n";

    WSAAsyncSelect(clientSocket, hWnd, WM_SOCKET, FD_READ);
    

 
}


void socketClient::sendJson(rapidjson::Document document)
{
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    document.Accept(writer);
    std::string jsonString = buffer.GetString();


    // Send JSON string to server
    send(clientSocket, jsonString.c_str(), jsonString.length(), 0);
}