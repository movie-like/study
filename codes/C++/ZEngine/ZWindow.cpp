#include"ZWindow.h"

ZWindow::ZWindowBase ZWindow::ZWindowBase::zWindowBase;
const LPCWSTR ZWindow::ZWindowBase::wndClassName = L"ZEngine";

ZWindow::ZWindowBase::ZWindowBase() noexcept : hInstance(GetModuleHandle(nullptr))
{
	WNDCLASSEX	 wndClassEx{};
	wndClassEx.cbSize = sizeof(wndClassEx);
	wndClassEx.lpfnWndProc = handleMsgSetup;
	wndClassEx.style = CS_OWNDC;
	wndClassEx.cbClsExtra = 0;
	wndClassEx.cbWndExtra = 0;
	wndClassEx.hInstance = getInstance();
	wndClassEx.hIcon = nullptr;
	wndClassEx.hCursor = nullptr;
	wndClassEx.hbrBackground = nullptr;
	wndClassEx.lpszMenuName = nullptr;
	wndClassEx.lpszClassName = getName();
	wndClassEx.hIconSm = nullptr;
	RegisterClassEx(&wndClassEx);
}
HINSTANCE ZWindow::ZWindowBase::getInstance() noexcept
{
	return zWindowBase.hInstance;
}
LPCWSTR ZWindow::ZWindowBase::getName() noexcept
{
	return wndClassName;
}
ZWindow::ZWindowBase::~ZWindowBase()
{
	UnregisterClass(wndClassName, getInstance());
}
ZWindow::ZWindow(int width, int height, LPCWSTR name) noexcept
{
	RECT wr{};
	wr.left = 100;
	wr.right = wr.left + width;
	wr.top = 100;
	wr.bottom = wr.top + height;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
	hWnd = CreateWindow(
		ZWindowBase::getName(),
		name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wr.right - wr.left,
		wr.bottom - wr.top,
		nullptr,
		nullptr,
		ZWindowBase::getInstance(),
		this);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
}
ZWindow::~ZWindow()
{
	DestroyWindow(hWnd);
}
LRESULT CALLBACK ZWindow::handleMsgSetup(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	if (msg == WM_NCCREATE)
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		ZWindow* const pWnd = static_cast<ZWindow*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(handleMsgThunk));
		return pWnd->handleMsg(hWnd,msg,wParam,lParam);
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
LRESULT CALLBACK ZWindow::handleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ZWindow* const pWnd = reinterpret_cast<ZWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return pWnd->handleMsg(hWnd, msg, wParam, lParam);
}
LRESULT ZWindow::handleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}