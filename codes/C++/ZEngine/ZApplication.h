#pragma once

#include"ZWindow.h"

class ZApplication
{
public:
	ZApplication();
	int init();
private:
	void doFrame();
private:
	ZWindow zWindow;
};
