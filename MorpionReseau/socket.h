#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define NOMINMAX

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

using namespace rapidjson;

class socketClient
{
public:
	socketClient();
	~socketClient();

	void createSocket();
	void sendJson(rapidjson::Document document); // voir pourquoi ca ne marche pas 

	SOCKET clientSocket;

private:
	static LRESULT CALLBACK ClientWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	HWND MakeWorkerWindow();

	HWND hWnd;
};