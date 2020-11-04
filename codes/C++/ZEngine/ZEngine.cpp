#include"ZEngine.h"

ZEngine::ZEngine(HWND hWnd)
{
	D3D11CreateDevice
	(
		nullptr,//pAdaptor：指定为哪个物理显卡创建设备对象，当该值为空，则默认主显卡
		D3D_DRIVER_TYPE_HARDWARE,//DriverType：一般来讲，该参数总是指定为D3D_DRIVER_TYPE_HARDWARE，表示使用3D硬件加快渲染速度
		nullptr,//Software：用于支持软件光栅化设备，我们总是将该参数设为空值
		0,//Flags：可选的设备创建标志值，该参数通常设为0
		nullptr,//pFeatureLevels：D3D_FEATURE_LEVEL数组，元素顺序表示特征等级的测试顺序，当该值为空，表示选择支持的最高等级
		0,//FeatureLevels：D3D_FEATURE_LEVEL数组中元素数量，因为我们把pFeatureLevels参数设为nullptr，所以该参数值为0
		D3D11_SDK_VERSION,//SDKVersion：始终设为D3D_SDK_VERSION
		&pDevice,//ppDevice：返回设备对象的地址（本质上是当D3DCreateDevice执行过程中会替你创建设备对象，然后把设备对象的地址存到你的pDevice这个变量里面）
		&featureLevel,//pFeatureLevels：返回pFeatureLevels数组中第一个支持的特征等级（如果pFeatureLevels为nullptr，则返回可支持的最高等级）
		&pDeviceContext//ppImmediateContext：返回创建后的设备上下文
	);
}