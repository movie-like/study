#include"ZGraphics.h"
#include"ZWindow.h"
#include"ZException.h"
ZGraphics::ZGraphics(HWND hWnd)
{
	HRESULT hr{ 0 };
	DXGI_SWAP_CHAIN_DESC sd{};
	sd.BufferDesc.Width = 0;//值为零代表由D3D帮你决定
	sd.BufferDesc.Height = 0;//值为零代表由D3D帮你决定
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;//我们将后台缓冲区的像素格式设为DXGI_FORMAT_B8G8R8A8_UNORM，额外的8位alpha并不会输出在显示器上，但是我们保存它有其他的用途
	sd.BufferDesc.RefreshRate.Numerator = 0;//不处于全屏就设置为0
	sd.BufferDesc.RefreshRate.Denominator = 0;//不处于全屏就设置为0
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;//让程序自己决定
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;//让程序自己决定
	sd.SampleDesc.Count = 1;//多重采样数量：我们暂时不用抗锯齿，设为1
	sd.SampleDesc.Quality = 0;//质量级别：我们暂时不用抗锯齿，设为0
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;//我们需要将缓冲区内容渲染到输出场景
	sd.BufferCount = 1;//我们需要一个默认的前缓存和一个后缓存，所以此项为1
	sd.OutputWindow = hWnd;//渲染的输出窗口
	sd.Windowed = TRUE;//是否全屏
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;//渲染效果一般设置成这样效率最高
	sd.Flags = 0;
	//可选的标志值，如果设为DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH，那么当应用程序切换到全屏模式时，Direct3D 会自动选择与当前的后台缓冲区设置最匹配的显示模式。如果未指定该标志值，那么当应用程序切换到全屏模式时，Direct3D 会使用当前的桌面显示模式。我们在示例框架中没有使用该标志值，因为对于我们的演示程序来说，在全屏模式下使用当前的桌面显示模式可以得到很好的效果。
	if (FAILED(hr = D3D11CreateDeviceAndSwapChain(
		nullptr,//pAdaptor：指定为哪个物理显卡创建设备对象，当该值为空，则默认主显卡
		D3D_DRIVER_TYPE_HARDWARE,//DriverType：一般来讲，该参数总是指定为D3D_DRIVER_TYPE_HARDWARE，表示使用3D硬件加快渲染速度
		nullptr,//Software：用于支持软件光栅化设备，我们总是将该参数设为空值
		0,//Flags：可选的设备创建标志值，该参数通常设为0
		nullptr,//pFeatureLevels：D3D_FEATURE_LEVEL数组，元素顺序表示特征等级的测试顺序，当该值为空，表示选择支持的最高等级
		0,//FeatureLevels：D3D_FEATURE_LEVEL数组中元素数量，因为我们把pFeatureLevels参数设为nullptr，所以该参数值为0
		D3D11_SDK_VERSION,//SDKVersion：始终设为D3D_SDK_VERSION
		&sd,//pSwapChainDesc
		&pSwapChain,//ppSwapChain：返回交换链对象的地址
		&pDevice,//ppDevice：返回设备对象的地址（本质上是当D3DCreateDevice执行过程中会替你创建设备对象，然后把设备对象的地址存到你的pDevice这个变量里面）
		nullptr,//pFeatureLevels：返回pFeatureLevels数组中第一个支持的特征等级（如果pFeatureLevels为nullptr，则返回可支持的最高等级）
		&pDeviceContext/*ppImmediateContext：返回创建后的设备上下文*/)))
	{
		throw ZException(hr,hWnd);
	}
}
ZGraphics::~ZGraphics()
{
	if (pDevice != nullptr)
	{
		pDevice->Release();
	}
	if (pDeviceContext != nullptr)
	{
		pDeviceContext->Release();
	}
	if (pSwapChain != nullptr)
	{
		pSwapChain->Release();
	}
	if (pTarget != nullptr)
	{
		pTarget->Release();
	}
}
void ZGraphics::endFrame()
{
	clearBuffer(1.0f,0.0f,0.0f);
}
void ZGraphics::clearBuffer(float red, float green, float blue) noexcept
{
	ID3D11Resource* pBackBuffer = nullptr;;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer));
	pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pTarget);
	pBackBuffer->Release();
	const float color[4]{ red,green,blue,1.0f };
	pDeviceContext->ClearRenderTargetView(pTarget, color);
	pSwapChain->Present(1u, 0u);//
}
