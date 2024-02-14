#pragma once

#include <Winsock2.h>
#include <Windows.h>

class thread
{
public:
	thread();
	virtual ~thread();

	void run();

	HANDLE getThreadHandle();
	
private:
	static DWORD WINAPI static_threadProc(void* pParam);
	virtual void OnEnter() = 0;

	HANDLE hThread;

};