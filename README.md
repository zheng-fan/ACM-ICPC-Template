# ACM/ICPC Template by fz

本模板采用LaTeX编写而成，建议使用Tex Live进行编译：

* Windows用户可以在清华大学开源镜像站下载到[Tex Live安装包][2]。
* Linux用户可以直接在软件源中安装。例如Ubuntu用户执行`sudo apt-get install xelatex`即可安装Tex Live。

执行`xelatex fz.tex`即可编译，Windows用户可以执行fz.bat，Linux用户可以直接make。

注意：

* 在Windows下不可使用CTex套件，因为它会导致cpp文件的中文注释显示错乱。Windows下Tex Live暂未测试，因此建议在Linux下进行编译。
* Linux下可能需要添加部分字体。
* Makefile中使用了astyle对源代码进行格式化。
* 由于LaTeX自身的特性，因此模板需要编译数次。目前编译两次暂未发现问题，编译一次会导致目录生成错乱。
* 针对双面打印做了一些优化，因此建议双面打印。

**本模板的tex是在[mzry(李昀)模板][1]的基础上修改而成，感谢李昀！**

[1]: https://github.com/mzry1992/ACMICPCTemplate/tree/master/newTempalte
[2]: https://mirrors.tuna.tsinghua.edu.cn/CTAN/systems/texlive/Images/
