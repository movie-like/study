#include "ZWindow.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow)
{
	ZWindow wnd(400, 600, L"ZEngine");
	MSG msg;
	BOOL result;
	while ((result = GetMessage(&msg,nullptr,0,0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}