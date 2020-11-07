#pragma once

#include<Windows.h>
#include<string>

class ZException
{
public:
	ZException(HRESULT hr,HWND hWnd);
	LPCWCHAR getErrorType() const;
	HRESULT getErrorCode() const;
	const HWND getHWnd() const;
	std::wstring getErrorString() const;
	static std::wstring translateErrorCode(HRESULT hr) noexcept;
private:
	HRESULT hr;
	HWND hWnd;
};
