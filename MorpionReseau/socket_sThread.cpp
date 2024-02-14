#include "socket_sThread.h"




socket_sThread::socket_sThread()
{
}


socket_sThread::~socket_sThread()
{
}


void socket_sThread::OnEnter()
{
    Serveur* pServer = new Serveur;
    pServer->createServer();

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    pServer->~Serveur();
    //return;
}