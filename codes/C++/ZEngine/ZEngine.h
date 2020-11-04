#pragma once

#include<Windows.h>
#include<d3d11.h>
class ZEngine
{
public:
	ZEngine(HWND hWnd);
	~ZEngine();
private:
	D3D_FEATURE_LEVEL featureLevel;
	ID3D11Device* pDevice;
	IDXGISwapChain* pSwapChain;
	ID3D11DeviceContext* pDeviceContext;
};