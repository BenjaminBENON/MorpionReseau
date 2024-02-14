#pragma once

#include "thread.h"
#include "socket.h"



class socket_thread : public thread
{
public :
	socket_thread();
	~socket_thread();

private :
	void OnEnter() override;
	//void Exit();
};