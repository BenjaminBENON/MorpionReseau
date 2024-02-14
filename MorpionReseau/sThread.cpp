#include "sThread.h"

sThread::sThread()
{
	run();
}


sThread::~sThread()
{
}


void sThread::run()
{
	hsThread = CreateThread(NULL, 0, static_sThreadProc, (void*)this, 0, NULL);
}


HANDLE sThread::getThreadHandle()
{
	return hsThread;
}


DWORD WINAPI sThread::static_sThreadProc(void* pParam)
{
	sThread* pThread = (sThread*)pParam;
	pThread->OnEnter();
	return 0;
}