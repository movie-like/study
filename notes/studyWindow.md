# Window

## 一个Windows窗体应用的基本框架

不同与控制台应用程序，Windows窗体应用的主函数名必须叫WinMain  

## 使用异常处理  

因为很多时候就算编译通过，程序也会出现很多不可预知的异常，如在我调用DirectX的D3D11CreateDeviceAndSwapChain函数时，实际上当它执行完后并没我为我创建好我要的设备，pSwapChain和pDevice以及pDeviceContext都是空值，但是程序仍然能执行  
所以我们需要一种异常捕获机制来告诉我们程序哪里出现了问题  
以我遇到的问题为例，我可以判断pSwapChain，pDevice，pDeviceContext这三个设备的指针是否为空值，如果为空，则说明创建失败，我就可以通过throw语句来抛出异常，并通过catch语句捕获异常  
一个异常如果没有被捕获，则它将终止当前的程序

## 常用函数说明

`GetMessage（LPMSG lpMsg，HWND hWnd，UINT wMsgFilterMin，UINT wMsgFilterMax)`  
说明：  
这个函数用来从消息队列里获取消息  
  
参数：
lpMsg：指向MSG结构的指针，该结构从线程的消息队列里接收消息信息  
hWnd：取得其消息的窗口的句柄，当其值取NULL时，GetMessage为任何属于调用线程的窗口检索消息，线程消息通过PostThreadMessage寄送给调用线程  
wMsgFilterMin：指定被检索的最小消息值的整数  
wMsgFilterMax：指定被检索的最大消息值的整数  
返回值：如果函数取得WM_QUIT之外的其他消息，返回非零值。如果函数取得WM_QUIT消息，返回值是零；如果出现了错误，返回值是-1  
例如，当hWnd是无效的窗口句柄或lpMsg是无效的指针时，返回值是-1，若想获得更多的错误信息，请调用GetLastError函数  

`MessageBox( HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType)`  
说明：  
这个函数用来弹出一个窗口  
  
参数：
hWnd：此参数代表消息框拥有的窗口，如果为NULL，则消息框没有拥有窗口。（如果你设置了窗口，则不关闭消息框就无法操作原窗口）
lpText：消息框的内容  
lpCaption：消息框的标题  
uType：指定一个决定对话框的内容和行为的位标志集，此参数可以为下列标志组中标志的组合，指定下列标志中的一个来显示消息框中的按钮以及图标  

`DWORD FormatMessage(DWORD dwFlags, LPCVOID lpSource, DWORD dwMessageId, DWORD dwLanguageId, LPTSTR lpBuffer, DWORD nSize, va_list* Arguments);`  
说明：  
这个函数是用来格式化消息字符串，就是处理消息资源的，消息资源是由mc.exe编译的，mc.exe是windows自带的一个系统工具，可以帮你翻译消息资源  
  
参数：

