#pragma once

#include<Windows.h>
#include"ZGraphics.h"
#include<memory>
#include<string>

class ZWindow
{
private:
	class ZWindowBase
	{
	public:
		static LPCWSTR getName() noexcept;
		static HINSTANCE getInstance() noexcept;
	private:
		ZWindowBase() noexcept;
		~ZWindowBase();
		ZWindowBase(const ZWindowBase&) = delete;
		ZWindowBase& operator=(const ZWindowBase&) = delete;
		static const LPCWSTR wndClassName;
		static ZWindowBase zWindowBase;
		HINSTANCE hInstance;
	};
public:
	~ZWindow();
	ZWindow(int width, int height,LPCWSTR wndName);
	ZWindow(const ZWindow&) = delete;
	ZGraphics& getZGraphics();
	const HWND getHWnd();
private:
	static LRESULT CALLBACK handleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK handleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT handleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
private:
	int width;
	int height;
	HWND hWnd;
	std::unique_ptr<ZGraphics>pZGraphics;
};