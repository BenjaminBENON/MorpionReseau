
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <fcntl.h>      /* Needed only for _O_RDWR definition */
#include <io.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#pragma once

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Gdi32.lib")

#include <Windows.h>
#include <cstring>


#define PORT 8080
#define WM_SOCKET (WM_USER + 1)

LRESULT CALLBACK ClientWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HWND MakeWorkerWindow();

class Client {
public:
	Client();
};
