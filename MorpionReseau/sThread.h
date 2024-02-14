#pragma once

#include <Winsock2.h>
#include <Windows.h>

class sThread
{
public:
	sThread();
	virtual ~sThread();

	void run();

	HANDLE getThreadHandle();

private:
	static DWORD WINAPI static_sThreadProc(void* pParam);
	virtual void OnEnter() = 0;

	HANDLE hsThread;

};