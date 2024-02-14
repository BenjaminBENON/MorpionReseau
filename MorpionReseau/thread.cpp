//#include "thread.h"
//
//thread::thread()
//{
//	run();
//}
//
//
//thread::~thread()
//{
//}
//
//
//void thread::run()
//{
//	hThread = CreateThread(NULL, 0, static_threadProc,(void*)this,0,NULL);//2eme NULL remplacé par this
//}
//
//DWORD WINAPI thread::static_threadProc(void* pParam)
//{
//	//thread* pThread = (thread*)pParam;
//
//	return 0;
//}