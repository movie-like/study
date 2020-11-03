# Java 
想要运行java程序我们只需要安装JRE（java run environment）  
JRE包含了JVM(java虚拟机)和java基本类库  
而想要进行java开发我们需要JDK(java development kit)  
JDK包含JRE和一些调试编译过程中用到的工具如javac.exe等  
<br />
<br />
我们可以通过cmd命令行来执行这些命令，但首先我们需要先配置好环境变量Path，它告诉了Windows系统在哪里寻找你在命令行里打出的命令（其实任何命令本质上都是exe文件），一般系统会现在当前cmd所处的文件目录下寻找文件，如果找不到就去环境变量Path存的地方去找，再找不到就会报错（操作系统真的帮你做了很多事）  
<br />
<br />
当我们从官网下载好了JDK，会发现JDK里有一个bin文件夹，里面存的就是一些java开发时用的命令，我们需要把这个文件夹的路径复制并添加到环境变量Path中，这样我们就能够使用它了（我的路径长这样 `D:\JDK\bin` ）注意，在Windows系统中路径分隔符是反斜杠 `\` ，在其他地方一般是斜杠 `/`  
<br />
<br />
我们可以在一个文件中写入以下代码  
```java
package studyjava.helloworld

public class HelloWorld
{
    public static void main(String args[])
    {
        System.out.println("HelloWorld");
    }
}
```
并把文件名命名为 HelloWorld.java（必须与主函数所在的类名字相同）  
这样我们的第一个java程序就写好了  
我们可以通过命令行调用javac命令编译这个文件  
首先要进入文件所在目录，我的文件在D盘，而cmd打开默认在C盘的用户文件夹，所以先输入`:D`命令来切换到D盘，再通过`dir`查看当前目录的文件列表和`cd XXX`进入XXX目录来切换到我们想要去的文件夹（`cd ..`表示回退到上级菜单）  
接着我们输入`javac HelloWorld.java`表示在当前目录生成原文件编译成的字节码  
如果想要在不同目录存放字节码，使用`javac -d 目录路径 HelloWorld.java`   
为了避免中文乱码，完整写法应该是这样`javac -encoding utf-8 -d . HelloWorld.java` 其中`.`表示当前目录  
此时如果执行成功，你的目录下会多出一个同名的.class文件  
如果报错，则说明源文件代码有问题，需要修改后再去编译  
<br />
<br />
我们接着输入`java HelloWorld` 命令，这样就可以执行我们编写的代码了  
可以看到命令行窗口输出了HelloWorld  
<br />
<br />
一个java命令完整应该长这样`java [options] mainClass [args...]`  
或这样`java [options] -jar jarfile [args...]`  
第一种从指定的java类开始启动，第二种从可运行的jar开始启动  
<br />
<br />
java应用启动的过程有三个步骤，首先启动java运行时环境JRE,然后加载所需的类，最后调用类的main方法  

options 由空格分隔的命令行选项  

mainClass 待启动类包含包路径的类全名，其中需要有main()方法  
（比如上面这个程序的main()方法在studyjava.helloworld包里，要运行这个字节码，应该输入`java studyjava.helloworld.HelloWorld`）

jarfile 待启动的jar包的路径名称

args 传给启动类的main()方法的参数，用空格分开  
<br />
<br />
包（package）其实和C++中的namespace相似，是java中避免命名冲突的一种管理方式  
当你编译java文件时，字节码文件会被编译器放到包名所代表的文件路径下（以被编译的java源文件所在目录为根目录）
