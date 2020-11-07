#include "ZApplication.h"
#include "ZException.h"
ZApplication::ZApplication() :zWindow(800, 600, L"client")
{
}
int ZApplication::init()
{
	try
	{
		MSG msg;
		BOOL result;
		while ((result = GetMessage(&msg, zWindow.getHWnd(), 0, 0)) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			doFrame();
		}
		if (result == -1)
		{
			return 0;
		}
		return msg.wParam;
	}
	catch (ZException zException)
	{
		std::wstring s = zException.getErrorString();
		LPCWCHAR lpCWChar = s.c_str();
		MessageBox(zWindow.getHWnd(), lpCWChar, zException.getErrorType(), MB_OK);
	}
	catch (...)
	{
		MessageBox(nullptr, L"Other Error", L"Unknown Error Type", MB_OK);
	}
}
void ZApplication::doFrame()
{
	zWindow.getZGraphics().endFrame();
}