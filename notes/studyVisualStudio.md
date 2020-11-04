# VisualStudio

这里记录一些写代码时遇到的错误  

## 找不到入口函数

当你想写一个窗体应用程序时，确保在 项目属性页->链接器->系统 一栏的 子系统 选项是窗口而不是控制台，否则会出现编译错误，因为当选项时控制台时系统会寻找main函数作为入口而不是WinMain函数作为入口  
<br />
<br />  

## 使用Unicode字符集
当我们与WindowsAPI打交道时，会接触到Unicode字符集，我们可以在 项目属性->配置属性->高级 页面里选择是否使用Unicode字符集  
Microsoft公司为Unicode设计了WindowsAPI，这样可以尽量减少代码的影响  
实际上，可以编写单个源代码文件，以便使用或者不使用Unicode来对它进行编译  
只需要定义两个宏（UNICODE和_UNICODE），就可以修改然后重新编译该源文件  
C++宏实现ANSI和Unicode的通用编程的本质是根据”_UNICODE”定义与否，这些宏展开为ANSI或Unicode字符（字符串）  
如下是tchar.h头文件中部分代码摘抄：  
```C++
#ifdef  _UNICODE
typedef wchar_t TCHAR;
#define __T(x) L##x
#define _T(x) __T(x)
#else
#define __T(x) x
typedef char TCHAR;
#endif
```
其中：  
`##` 是ANSI C标准的预处理语法，它叫做“粘贴符号”，表示将前面的L添加到宏参数上  
也就是说，如果我们写 `_T("Hello")` ，展开后即为 `L"Hello"`    
`_UNICODE` 宏用于C运行期头文件，而 `UNICODE` 宏则用于Windows头文件  
`UNICODE` 和 `_UNICODE` 的区别：  
前者没有下划线，专门用于Windows头文件；后者有一个前缀下划线，专门用于C运行时头文件  
换句话说，也就是在ANSI C++语言里面根据 `_UNICODE` 定义与否，各宏分别展开为Unicode或ANSI字符，在Windows里面根据 `UNICODE` 定义与否，各宏分别展开为Unicode或ANSI字符  
也许我们从来没有注意到，Win32 API实际上有两个版本  
一个版本接受MBCS字符串，另一个接受Unicode字符串  
例如：  
其实根本没有 `SetWindowText()` 这个API函数，相反，有 `SetWindowTextA()` 和 `SetWindowTextW()`  
后缀A表明这是MBCS函数，后缀W表示这是Unicode版本的函数  
这些API函数的头文件在winuser.h中声明，下面例举winuser.h中的SetWindowText()函数的声明部分：  
```C++  
#ifdef UNICODE
#define SetWindowText  SetWindowTextW
#else
#define SetWindowText  SetWindowTextA
#endif // !UNICODE
```  
当编译源代码模块时，通常必须同时定义这两个宏  
Windows定义的Unicode数据类型有哪些：  
WCHAR Unicode字符  
PWSTR 指向Unicode字符串的指针  
PCWSTR 指向一个恒定的Unicode字符串的指针  
对应的ANSI数据类型为CHAR，LPSTR和LPCSTR  
ANSI/Unicode通用数据类型为TCHAR，PTSTR,LPCTSTR  
  
在VS的项目属性中设置Unicode本质其实就是帮你定义好了 `UNICODE` 和 `_UNICODE` 这两个宏  
<br />
<br />


