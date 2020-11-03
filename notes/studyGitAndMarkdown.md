# Markdown
用一到六个#表示从大到小的标题  
用键盘左上角的反引号括住加入的代码 
如果想加入代码区块，使用连续三个反引号括住区块内容，而且我们可以指定区块内的代码语言，只需要在三个反引号后面加上该语言的名字如C++，javascript等等  
每行结尾两个以上的空格加一个回车表示换行  
除此之外还可用html格式的`<br />`表示换行

# Git
首先了解一下Git是什么  
然后，我们需要下载安装Git  
接着打开GitBash这个命令行工具进行配置  
`git config --global user.name XXX`  
`git config --global user.email XXX`  
其中 `--global` 表示这个配置是全局的（系统用户的），如果一个项目没有自己的配置就会使用这个全局的配置，如果要给某一个项目特定的配置，请使用  
`git config user.name XXX`  
`git config user.email XXX`  
这样就是项目自身的配置  
<br />
<br />
但是想要配置一个本地的项目首先需要初始化一个.git文件夹，这个文件夹是用来存放你的项目信息，git就是通过这些信息管理你的本地项目的  
而想要初始化.git文件夹，需要在你的本地项目文件夹中打开gitbash输入`git init`  
这样git会自动帮你在该文件夹中创建一个隐藏文件夹.git  
到此为止一个git本地仓库就算配置好了  
<br />
<br />
我们之所以使用Git就是为了方便开发，而在开发中代码不断修修改改容易造成混乱，所以要尽早使用分支结构branch（本质其实就是一条版本路线）  
使用`git branch`查看本地的分支  
使用`git branch -r`查看远端的分支  
使用`git branch -a`查看本地和远端的分支  
如果想要新建分支，应使用`git branch XXX`  
但是此时我们并没有转换到该分支上，所以我们应该再使用`git checkout XXX`来转换到该分支上  
有一种简单的写法可以包含以上两步`git checkout -b XXX`意思是创建并转换到XXX分支上  
当我们初始化git时，默认在master分支上（Git分支管理的本质是创建和移动指针）  
<br />
<br />
我们可以通过`git status`来查看当前工作区和暂存区的状态（你目前在哪一个分支上，哪些文件在工作区，哪些被添加到了暂存区）  
我们可以通过`touch XXX.XX`命令新建一个文件，并使用`vim XXX.XX` 命令用Git自带的vim编辑器修改文件（在windows下右键新建文件并通过别的编辑器修改也是可以的）  
可以通过`cd 磁盘或文件夹名字`进入文件夹  
通过`cd ..`返回上一级  
通过`mkdir 文件夹名字`新建文件夹  
开始时，暂存区里是没有东西的。我们可以用`git add XXX.XX`把文件添加到暂存区  
当然，如果想要把文件从暂存区撤回，我们也可以用`git rm --cached XXX.XX`撤回在暂存区的文件（rm是remove的意思，cache是缓存，cached是被缓存的文件）  
接下来，为了把文件提交到本地库，我们还需要`git commit XXX.XX` 命令，意思是提交XXX.xx这个文件到本地库，当然也可以直接使用`git commit`默认提交所有文件  
当你提交完成后，你应该会进入Git Bash的Vim文本编辑器界面，并且会提示你输入commit message，如果不输入任何信息，则会终止commit  
为了commit成功，你可以输入一些对本次commit的描述，输入完成后按<btn>Esc</btn>键，然后输入:wq三个字符表示终止编辑  
当然，为了方便，Git提供了更简洁的集成命令`git commit -m "描述信息"` 来方便我们使用    
<br />
<br />
当你提交了多次，你可能会想要查看提交记录，这时你需要`git log`命令  
这条命令会详细列出每一次提交的相关信息  
当然，提交的信息很多时，GitBash这个控制台应用会自动进入多屏显示模式  
多屏显示的控制方式为:
<br />    
空格:向上翻页  
b:向下翻页  
q:退出  
<br />
当然，有时信息太多太长并不方便阅读  
我们可以使用`git log --pretty=oneline`  
以及`git log --oneline`  
来精简化log的输出信息  
同时，我们还可以使用`git reflog`命令来查看HEAD头到每一次提交的版本需要经过多少步  
在Gitbash中显示为HEAD@{N},N为当前是第几次commit的版本，第一次commit时N为0  
<br />
<br />
有时我们可能做出了错误的修改，想要回退到上一次提交的版本  
那么此时我们需要`git reset --hard 提交版本的Hash值`（只需要七位）命令来回退版本  
但实际上，这条命令并不是只能用来回退版本，实际上它的本质是重设HEAD头所在的版本，所以只要是你的本地版本库里有commit记录的版本，你都可以“回”到这个位置  
当然，你还可以使用`git reset --hard HEAD^`来后退版本（这个命令只能后退）^的个数表示后退的次数，你可在HEAD后面接上任意数量的^后退任意次版本  
但是，当想要后退的版本太多，你可以使用`git reset --hard HEAD~N`其中N表示后退的次数  
关于`git reset --hard XXX`命令我们可能还有疑惑，就是--hard这个参数是什么意思  
实际上，Git提供了几种不同的reset参数，区别如下  
<br />
`--soft`:仅仅在本地库移动HEAD指针而不做其他操作  
`--mixed`:在本地库移动HEAD指针并重置暂存区  
`--hard`在本地库移动HEAD指针并重置暂存区和工作区  
<br />
<br />
当我们在本地完成了工作，想要把库推送到远程库时，我们可以使用`git push`命令，但在此之前，GitBash还需要知道要把本地库推送到哪  
我们可以通过`git remote -v`来查看本地配置的远程库有没有别名，如果没有设定远程库别名，则每次拉取或推送都要输入一长串完整地址，这显然很不方便   
我们可以使用`git remote add origin 远程库地址`命令来添加远程库别名，GitHub上地址通常长这样，https://github.com/zacharyzhang1208/Study.git  
此时，如果添加成功，那么`git remote -v`命令会输出关于你的远程库的信息  
`origin  https://github.com/zacharyzhang1208/Study.git (fetch)`
`origin  https://github.com/zacharyzhang1208/Study.git (push)`  
其中fetch表示GitBash把你的origin这个别名指向了成了`https://github.com/zacharyzhang1208/Study.git`并把它作为fetch的抓取地址  
push那一行同理  
此时远程库别名就配置好了
<br />
<br />
当我们通过`git remote add`命令给远程库起完了别名origin并把地址链接上后，我们就可以通过origin这个名字快速push我们的版本到远程库上了  
需要命令`git push 远程库名字 分支名字` 如 `git push origin master`  
当你输入完这条命令，Git通常会弹出窗口要你输入账号密码，输入完后等待一段时间就push成功了，此时你应该可以在你的GitHub上看到你刚刚push的内容  
<br />
<br />
当我们想要复制别人的库时，可以使用`git clone 远程库地址` 命令  
这条命令可以概括为做了三件事  
<br />
初始化本地库  
完整地把远程库fetch到本地（本地远程仓库）  
创建origin远程仓库地址别名  
<br />
本地远程仓库存在的意义是Git向远程仓库push之前进行merge的参照物，且在push前被用来检查是否和远程仓库版本一致    
如果想要更新这个区域，应使用 `git fetch`  





