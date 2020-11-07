#pragma once

#include<d3d11.h>

#pragma comment(lib,"C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.18362.0\\um\\x86\\d3d11.lib")

class ZGraphics
{
public:
	ZGraphics(HWND hWnd);
	ZGraphics(const ZGraphics&) = delete;
	ZGraphics& operator=(const ZGraphics&) = delete;
	~ZGraphics();
	void endFrame();
	void clearBuffer(float red, float green, float blue) noexcept;
private:
	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwapChain = nullptr;
	ID3D11DeviceContext* pDeviceContext = nullptr;
	ID3D11RenderTargetView* pTarget = nullptr;
};