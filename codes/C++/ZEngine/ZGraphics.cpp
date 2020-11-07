#include"ZGraphics.h"
#include"ZWindow.h"
#include"ZException.h"
ZGraphics::ZGraphics(HWND hWnd)
{
	HRESULT hr{ 0 };
	DXGI_SWAP_CHAIN_DESC sd{};
	sd.BufferDesc.Width = 0;//ֵΪ�������D3D�������
	sd.BufferDesc.Height = 0;//ֵΪ�������D3D�������
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;//���ǽ���̨�����������ظ�ʽ��ΪDXGI_FORMAT_B8G8R8A8_UNORM�������8λalpha�������������ʾ���ϣ��������Ǳ���������������;
	sd.BufferDesc.RefreshRate.Numerator = 0;//������ȫ��������Ϊ0
	sd.BufferDesc.RefreshRate.Denominator = 0;//������ȫ��������Ϊ0
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;//�ó����Լ�����
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;//�ó����Լ�����
	sd.SampleDesc.Count = 1;//���ز���������������ʱ���ÿ���ݣ���Ϊ1
	sd.SampleDesc.Quality = 0;//��������������ʱ���ÿ���ݣ���Ϊ0
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;//������Ҫ��������������Ⱦ���������
	sd.BufferCount = 1;//������Ҫһ��Ĭ�ϵ�ǰ�����һ���󻺴棬���Դ���Ϊ1
	sd.OutputWindow = hWnd;//��Ⱦ���������
	sd.Windowed = TRUE;//�Ƿ�ȫ��
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;//��ȾЧ��һ�����ó�����Ч�����
	sd.Flags = 0;
	//��ѡ�ı�־ֵ�������ΪDXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH����ô��Ӧ�ó����л���ȫ��ģʽʱ��Direct3D ���Զ�ѡ���뵱ǰ�ĺ�̨������������ƥ�����ʾģʽ�����δָ���ñ�־ֵ����ô��Ӧ�ó����л���ȫ��ģʽʱ��Direct3D ��ʹ�õ�ǰ��������ʾģʽ��������ʾ�������û��ʹ�øñ�־ֵ����Ϊ�������ǵ���ʾ������˵����ȫ��ģʽ��ʹ�õ�ǰ��������ʾģʽ���Եõ��ܺõ�Ч����
	if (FAILED(hr = D3D11CreateDeviceAndSwapChain(
		nullptr,//pAdaptor��ָ��Ϊ�ĸ������Կ������豸���󣬵���ֵΪ�գ���Ĭ�����Կ�
		D3D_DRIVER_TYPE_HARDWARE,//DriverType��һ���������ò�������ָ��ΪD3D_DRIVER_TYPE_HARDWARE����ʾʹ��3DӲ���ӿ���Ⱦ�ٶ�
		nullptr,//Software������֧�������դ���豸���������ǽ��ò�����Ϊ��ֵ
		0,//Flags����ѡ���豸������־ֵ���ò���ͨ����Ϊ0
		nullptr,//pFeatureLevels��D3D_FEATURE_LEVEL���飬Ԫ��˳���ʾ�����ȼ��Ĳ���˳�򣬵���ֵΪ�գ���ʾѡ��֧�ֵ���ߵȼ�
		0,//FeatureLevels��D3D_FEATURE_LEVEL������Ԫ����������Ϊ���ǰ�pFeatureLevels������Ϊnullptr�����Ըò���ֵΪ0
		D3D11_SDK_VERSION,//SDKVersion��ʼ����ΪD3D_SDK_VERSION
		&sd,//pSwapChainDesc
		&pSwapChain,//ppSwapChain�����ؽ���������ĵ�ַ
		&pDevice,//ppDevice�������豸����ĵ�ַ���������ǵ�D3DCreateDeviceִ�й����л����㴴���豸����Ȼ����豸����ĵ�ַ�浽���pDevice����������棩
		nullptr,//pFeatureLevels������pFeatureLevels�����е�һ��֧�ֵ������ȼ������pFeatureLevelsΪnullptr���򷵻ؿ�֧�ֵ���ߵȼ���
		&pDeviceContext/*ppImmediateContext�����ش�������豸������*/)))
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
