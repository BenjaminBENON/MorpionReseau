#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <Windows.h>

#include <iostream>
#include <cstring>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Gdi32.lib")


class Serveur
{

public:
	Serveur();
	~Serveur();
	int createServer();
private :
	static LRESULT CALLBACK SocketWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	HWND MakeWorkerWindow();

	SOCKET server_fd;

};