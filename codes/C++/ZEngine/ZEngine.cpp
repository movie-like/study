#include"ZEngine.h"

ZEngine::ZEngine(HWND hWnd)
{
	D3D11CreateDevice
	(
		nullptr,//pAdaptor��ָ��Ϊ�ĸ������Կ������豸���󣬵���ֵΪ�գ���Ĭ�����Կ�
		D3D_DRIVER_TYPE_HARDWARE,//DriverType��һ���������ò�������ָ��ΪD3D_DRIVER_TYPE_HARDWARE����ʾʹ��3DӲ���ӿ���Ⱦ�ٶ�
		nullptr,//Software������֧�������դ���豸���������ǽ��ò�����Ϊ��ֵ
		0,//Flags����ѡ���豸������־ֵ���ò���ͨ����Ϊ0
		nullptr,//pFeatureLevels��D3D_FEATURE_LEVEL���飬Ԫ��˳���ʾ�����ȼ��Ĳ���˳�򣬵���ֵΪ�գ���ʾѡ��֧�ֵ���ߵȼ�
		0,//FeatureLevels��D3D_FEATURE_LEVEL������Ԫ����������Ϊ���ǰ�pFeatureLevels������Ϊnullptr�����Ըò���ֵΪ0
		D3D11_SDK_VERSION,//SDKVersion��ʼ����ΪD3D_SDK_VERSION
		&pDevice,//ppDevice�������豸����ĵ�ַ���������ǵ�D3DCreateDeviceִ�й����л����㴴���豸����Ȼ����豸����ĵ�ַ�浽���pDevice����������棩
		&featureLevel,//pFeatureLevels������pFeatureLevels�����е�һ��֧�ֵ������ȼ������pFeatureLevelsΪnullptr���򷵻ؿ�֧�ֵ���ߵȼ���
		&pDeviceContext//ppImmediateContext�����ش�������豸������
	);
}