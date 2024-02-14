#pragma once

#include "sThread.h"
#include "Serveur.h"



class socket_sThread : public sThread
{
public:
	socket_sThread();
	~socket_sThread();

private:
	void OnEnter() override;
};