#include"ZException.h"
#include<string>
#include<Windows.h>
ZException::ZException(HRESULT hr,HWND hWnd) :hr(hr),hWnd(hWnd)//ZException构造函数
{
}
LPCWCHAR ZException::getErrorType() const
{
	return L"Window Error Type";
}
HRESULT ZException::getErrorCode() const
{
	return hr;
}
const HWND ZException::getHWnd() const
{
	return hWnd;
}
std::wstring ZException::getErrorString() const
{
	return translateErrorCode(hr);
}
std::wstring ZException::translateErrorCode(HRESULT hr) noexcept
{
	WCHAR* pMsgBuf = nullptr;
	DWORD nMsgLen/*错误码的长度*/ = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr,
		hr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPWSTR>(&pMsgBuf),
		0,
		nullptr);//调用WindowAPI获取错误码所代表的错误信息
	if (nMsgLen == 0)
	{
		return L"Unidentified Error";
	}
	std::wstring errorString = pMsgBuf;
	LocalFree(pMsgBuf);
	return errorString;
}