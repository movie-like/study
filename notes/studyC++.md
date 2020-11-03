# C++

## 基本内置类型

C++定义了一组表示整数，浮点数，单个字符和布尔值的算术类型，另外还定义了一种称为void的特殊类型  
算术类型的储存空间大小依机器而定。这里的大小指的是用来表示该类型的二进制位（bit）数  
C++标准规定了每个算术类型的最小储存空间，但是它并不阻止编译器使用更大的储存空间  
实际上，几乎所有的编译器使用的储存空间都比要求的要大  

值得注意的是，字符类型有两种： `char` 类型和 `wchar_t` 类型，后者用于扩展字符集（中文和日文等，这些字符不能用单个 `char` 表示）

### 宽字符的输入输出  

## 指针

### 普通的指针

### this指针

#### this参数介绍

首先从类成员的隐式参数this说起

```C++
struct A
{   
    int value;
    A(int param)
    {
        value=param;
    }
    int getvalue()
    {
        return value;
    }
};
```
以上代码自定义了类A，该结构包含了自定义的构造函数和getvalue()成员函数。
```C++
A a(1);
int b = a.getvalue();
```
以上代码定义了A的对象a，并通过a调用了A的成员函数getvalue()  
需要注意的是，此时的getvalue()函数实际上是对象a调用的，返回的value值实际上隐式地返回a.value。

成员函数时通过一个名为this的隐式参数来访问调用它的那个对象，当通过某个对象调用成员函数时，实际上就是将该对象的地址赋值给隐式的this参数  
所以，类A的geta()函数可以看成是如下定义
```C++
int getvalue(this)
{
   return this->value;
}
```
而通过a调用getvalue()的代码实际上就是
```C++
A::getvalue(&a);
```
this参数是指针常量  
需要注意的是，this参数是指向对象地址的，因此其值不能被改变，但是可以通过this指针修改所指对象的值，也就是说this参数本身是一个常量  

#### 常量成员函数的引入  

this是指向类的对象的，这个对象是非常量的，当类的对象是常量时，就不能将其地址赋值给this  
```C++
const A a(1);
int b = a.getvalue();
```
此时，a是常量，通过常量调用成员函数时，无法将a的地址赋值给隐藏的this参数，报错信息是  
`error C2662: “int A::geta(void)”: 不能将“this”指针从“const A”转换为“A &”`

此时，需要将this声明为指向const的指针，但是由于this是隐式参数，无法直接指定，所以就要使用常量成员函数，即在成员函数的参数列表之后添加const  
它的本质是告诉编译器将这里的this声明为指向const的指针，也就是说在常量成员函数中的隐式参数this是一个指向常量的指针常量  
```C++
int getvalue() const
{
    return value;
}
```
此时，上面提到的代码就不会报错  

实际上，const修饰指针主要是为了告诉编译器能否通过指针修改所指对象的值，并不是说指针所指的对象必须是const类型  
因此，对于非常量的对象，也能调用常量成员函数    
```C++
A a(1);
int b = a.getvalue();
```
也因为常量成员函数中的隐式参数this是一个指向常量的指针常量，所以这个函数不能修改该类里面的任何成员的值（当然你可以读取值，但是不能修改，就是这个意思）  
<br />
<br />

## 容器

### 迭代器类型

实际上我们可以把迭代器理解成一种在C++泛型编程中使用的类型，它的作用和指针很像，但是功能比指针更强大  
它实际上是C++标准库中封装的一个类，目的是为了泛型算法的使用  
每种STL容器中都有自己的迭代器类型，如vector:  
`vector<int>::iterator iter`
这条语句定义了名为iter的变量，它的数据类型是由 `vector<int>` 定义的迭代器类型  

### 迭代器的begin和end操作  

STL的每种容器都定义了一对名为begin()和end()的函数用来返回迭代器  
如果容器不为空，begin操作返回的迭代器指向容器的第一个元素  
```C++
vector<int> ivec;
vector<int>::iterator iter = ivec.begin();   
```
此时iter指向ivec的第一个元素ivec[0]  
需要注意的是，如果使用 `ivec.end();` 函数初始化iter，则iter实际上指向一个不存在的元素，因为由end操作返回的是指向容器“末端元素的下一个”，我们把它称为“超出末端迭代器”（off-the-end iterator），表明它指向一个实际不存在的元素  
如果容器为空，则begin操作返回的迭代器与end操作返回的迭代器相同  

### 迭代器运算

STL的迭代器类型定义了一些操作适用于所有类型的迭代器  

解引用： `*iter` 获取迭代器所指向的元素，我们可以使用解引用操作符 `*` 来访问迭代器所指元素，如 `*iter = 0;` 意为把iter这个迭代器所指元素赋值为0  

解引用并获取成员： `iter->mem` 对iter解引用，获取指定元素中名为mem的成员，这句话等效于 `(*iter).mem`   

自增： `iter++` / `++iter` ，使迭代器自增指向容器中下一个元素

自减： `iter--` / `--iter` ，使迭代器自减指向容器中上一个元素  

判断相等/不等： `iter1 == iter2` / `iter1 != iter2` 如果两个迭代器指向同一个元素或都指向超出末端的下一个位置时相等，否则不等  

### size_type类型  

从逻辑上讲，size()成员函数应该似乎返回整型数值，但事实上，size操作返回是string::size_type类型的值  
许多库类型都定义了一些配套类型（companion type）  
通过这些配套类型，库函数的使用就与机器无关（machine-independent）  
size_type就是这些配套类型中的一种，它被定义并使用在string类和vector类中，与unsigned型（unsigned int获unsigned long）具有相同含义，而且保证足够大的能够存储任意的string对象和vector对象的长度  
string::size_type它在不同的机器上，长度是可以不同的，并非固定的长度，但只要你使用了这个类型，就使得你的程序适合这个机器。与实际机器匹配  
下面给出一个使用它的例子：  
```C++
for(vector<int>::size_type ix = 0; ix != ivec.size(); ++ix)
{
    ivec[ix] = 0;
}
```  

### 顺序容器  

我们之前已经使用过一种容器类型：STL的vector类型，这是一种顺序容器（sequential container）  
顺序容器将单一类型元素聚集起来，根据位置来存储访问这些元素。顺序容器的元素排列次序与元素值无关，是由元素添加到容器里的次序决定的  
STL标准库为我们定义了三种顺序容器类型：  

vector  支持快速随机访问
  
list  支持快速插入/删除

deque  双端队列
  
<br />
<br />

## C++强制类型转换  

### 四种强制类型转换命令 

四种命令都遵循以下格式：  
`cast-name<type>(expression)`  
具体分以下四种  

#### dynamic_cast  


#### const_cast  

顾名思义，该命令会转换掉表达式的const性质

#### static_cast

用于完成“相关类型”之间的转换  
如从 `double` 到 `int` 之间的转换  
对比特位的截断，补齐等操作，编译器会自动完成  

#### reinterpret_cast  

该命令为操作数的二进制位提供了低层次的重新解释  
它可以处理完全的“互不相关类型”之间的转换  
本质上完全是对操作数的比特位复制  
一般我们使用它是为了欺骗编译器以达到某种目的
下面给出一个使用它的例子
```C++
LRESULT WINAPI Window::HandleMsgSetup( HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	if (msg == WM_NCACTIVATE)
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
LRESULT WINAPI Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Z_window* const pWnd = reinterpret_cast<Z_window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return pWnd->HandleMsg(hWnd,msg,wParam,lParam);
}
LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
```
这是一个对WindowsAPI的类封装实现  
在这里我们把一个ClassWndEx中的lpWndProc赋值成了HandleMsgSetup  
当系统需要调用窗口过程函数时就会根据lpWwndproc储存的值寻找到我们定义的窗口过程函数  
WM_NCACREATE是一个Windows系统消息，在窗口创建之前系统会发出这个消息  
关于lpWndproc对应的函数的四个参数：  
`HWND hWnd` 是Windows系统中的窗体句柄  
`UINT msg` 是消息值
`WPARAM wParam` 和 `LPARAM lParam` 是附加参数，当消息类型不同时wParam和lParam所代表的意义也不同  
在上面这个例子中：  
当 `msg == NCACREATE` 时
`WPARAM wParam` - 不使用
`LPARAM lParam` - 是CREATESTRUCT结构类型的指针，其中的参数是CreateWindowEx中的12个参数  
CREATESTRUCT结构定义了传递给应用程序的窗口过程的初始化参数，它定义了窗口外观相关特性，CREATESTRUCT结构具有如下形式：  
``` C++
typedef struct tagCREATESTRUCT {
    LPVOID lpCreateParams;
    HANDLE hInstance;
    HMENU hMenu;
    HWND hwndParent;
    int cy;
    int cx;
    int y;
    int x;
    LONG style;
    LPCSTR lpszName;
    LPCSTR lpszClass;
    DWORD dwExStyle;
} CREATESTRUCT;
```
其中， `LPVOID lpCreateParams` 是一个创建窗口过程中可以用来储存自定义参数的变量  
在这里我们用它来储存我们定义的窗口类对象的指针  

### 旧式强制类型转换

在引入命名的强制类型转换操作符之前，显示类型转换用圆括号将类型括起来实现  
`char *pc = (char*) ip`  
效果与 `reinterpret_cast` 相同，但是这种强制类型转换的可读性较差，难以跟踪错误转换  
所以在现代C++程序中建议使用C++提供的四种命名的强制类型转换命令  

## STL常用库

### 一

`#include<vector>`  
不定长数组  
要使用不定长数组，先要创建数组对象    
`vector<类型名> 对象名` 如 `vector<int> vec`  
下面是几种重要的vector操作:  
使用`vec.push_back(XXX);`来向vec尾部添加元素  
使用`vec.push_front(XXX);`向头部添加元素  
使用`vec.begin();`和`vec.end();`来获取头和尾迭代器   
<br />
<br />

### 二

`#include<algorithm>`
里面有一个sort排序函数很常用，经常搭配vector使用  
`sort(vec.begin(),vec.end())`  
这样排序默认是升序的  
如果想要降序排序，可以重载Comp函数  
``` C++
bool Comp(const int &a,const int &b)
{
    return a>b;
}
```
其中 a表示前一个，b表示后一个  
你甚至可以通过重载Comp函数来实现任何自定义的比较规则进行排序  
如果Comp返回true，则a在b前面  ，否则b在a前面  
<br />
<br />


