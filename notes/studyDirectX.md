# DirectX  

## 日志

2020.11.5：  
我的项目在稳步前进，我对Windows窗口编程的理解正在不断加深，跟着视频学习我收获了很多有用的知识，包括但不局限与C++的四种类型转换以及它们的应用（详见studyC++学习笔记），今天我初步构建好了应用框架（ZApplication类），封装好了ZWindow类，ZGraphics类，但是今天遇到了一个BUG，D3D11CreateDeviceAndSwapChain函数好像出错了，这让我充分意识到调试层的重要性，下一步是构建好调试层，找出错误信息，以上  

2020.11.07：  
上次的BUG找到了，通过建立好异常处理机制，我很快找到上次的BUG是由于参数错误（DXGI_SWAPCHAIN_DESC结构体没有填完整），可见建立一套异常处理系统真的很重要  

## 什么是DirectX  

## COM

组件对象模型（COM）技术使 DirectX 独立于任何编程语言，并具有版本向后兼容的特
性  
我们经常把COM对象称为接口，并把它当成一个普通的C++类来使用  
当使用C++编写DirectX程序时，许多COM的底层细节都不必考虑，唯一需要知道的一件事情是，我们必须通过特定的函数或其他的COM接口方法来获取指向COM接口的指针，而不能用C++的 `new` 关键字来创建COM接口  
另外，当我们不再使用某个接口时，必须调用它的 `Release` 方法来释放它（所有的COM接口都继承于 `IUnknown` 接口，而 `Release` 方法是 `IUnknown` 接口的成员），而不能用 `delete` 语句  
COM对象在其自身内部实现所有的内存管理工作  
当然，有关 COM 的细节还有很多，但是在实际工作中只需知道上述内容就足以有效地使用DirectX了  
注意：COM接口都以大写字母I为前缀  
例如，表示2D纹理的接口为： `ID3D11Texture2D`

## 初始化DirectX  

基本步骤有下面8步：  
1．使用 `D3D11CreateDevice` 方法创建 `ID3D11Device` 和 `ID3D11DeviceContext`  
2．使用 `ID3D11Device::CheckMultisampleQualityLevels` 方法检测设备支持的 4X 多重采样质量等级    
3．填充一个 `IDXGI_SWAP_CHAIN_DESC` 结构体，该结构体描述了所要创建的交换链的特性  
4．查询 `IDXGIFactory` 实例，这个实例用于创建设备和一个 `IDXGISwapChain` 实例  
5．为交换链的后台缓冲区创建一个渲染目标视图  
6．创建深度/模板缓冲区以及相关的深度/模板视图  
7．将渲染目标视图和深度/模板视图绑定到渲染管线的输出合并阶段，使它们可以被 Direct3D 使用  
8．设置视口  

### 创建ID3D11Device和ID3D11DeviceContext

```C++
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
```