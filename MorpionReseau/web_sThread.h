#pragma once

#include "sThread.h"


class web_sThread : public sThread
{
public:
	web_sThread();
	~web_sThread();

private:
	void OnEnter() override;
};