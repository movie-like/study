#pragma once

#include<d3d11.h>

#pragma comment(lib,"d3d11.lib")

class ZGraphics
{
public:
	ZGraphics(HWND hWnd);
	ZGraphics(const ZGraphics&) = delete;
	ZGraphics& operator=(const ZGraphics&) = delete;
	~ZGraphics();
private:
	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwapChain = nullptr;
	ID3D11DeviceContext* pDeviceContext = nullptr;
};