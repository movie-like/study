#include"ZApplication.h"
#include"ZException.h"
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow)
{
	try
	{
		ZApplication{}.init();
	}
	catch (ZException zException)
	{
		std::wstring s = zException.getErrorString();
		LPCWCHAR lpCWChar = s.c_str();
		MessageBox(zException.getHWnd(), lpCWChar, zException.getErrorType(), MB_OK);
	}
	catch (...)
	{
		MessageBox(nullptr, L"Other Error", L"Unknown Error Type", MB_OK);
	}
	return 0;
}