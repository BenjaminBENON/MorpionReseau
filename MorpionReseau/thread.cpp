#include "thread.h"

thread::thread()
{
	run();
}


thread::~thread()
{
}


void thread::run()
{
	hThread = CreateThread(NULL, 0, static_threadProc,(void*)this,0,NULL);//2eme NULL remplacé par this
}


HANDLE thread::getThreadHandle()
{
	return hThread;
}


DWORD WINAPI thread::static_threadProc(void* pParam)
{
	thread* pThread = (thread*)pParam;
	pThread->OnEnter();
	return 0;
}