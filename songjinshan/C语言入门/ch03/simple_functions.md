# 3 简单函数

## 3.1 数学函数

在C语言中使用数学函数:

```c
#include <math.h>
#include <stdio.h>

int main(void)
{
    double pi = 3.1416;
    printf("sin(pi/2)=%f\nln1=%f\n", sin(pi/2), log(1.0)); /* 数学中的ln函数在C标准库中叫log*/
    return 0;
}
```

编译运行这个程序：

```bash
$ gcc -lm math_functions.c
$ ./a.out
sin(pi/2)=1.000000
ln1=0.000000
```

上面的代码中，1.0是参数Argument, log是函数Function , log(1.0)是函数调用Function All。

程序第一行的#号和include 表示包含一个头文件(Header File), 后面的尖括号(Angel Bracket)中就是文件名(这些头文件通常位于/usr/include目录下)。头文件中声明了我们程序中使用的库函数，根据先声明后使用的原则，要使用printf函数必须包含stdio.h，要使用数学函数必须包含math.h ， 如果什么库函数都不使用就不必包含任何头文件，例如写一个程序int main(void) {int a; a=2;return 0;} , 不需要包含头文件就可以编译通过。

使用math.h中声明的库函数有一点特殊之处，gcc命令行必须加-lm选项，因为数学函数位于libm.so库文件中(这些库文件通常位于/lib目录下) ， -lm选项告诉编译器，我们程序中用到的数学函数要到这个库文件里找。本书用到的大部分库函数(例如printf)位于libc.so库文件中，使用libc.so中的库函数在编译时不需要加-lc选项，当然加了也不算错，因为这个选项是gcc的默认选项。关于头文件和库函数将在第20章链接详解再详细介绍。

**C标准库和glibc**:

C标准主要由两部分组成， 一部分描述C的语法，另一部分描述C标准库。

C标准库定义了一组标准头文件，每个头文件中包含一些相关的函数、变量、类型声明和宏定义。

要在一个平台上支持C语言，不仅要实现C编译器，还要实现C标准库，这样的实现才算符合C 标准。不符合C标准的实现也是存在的，例如很多单片机的C语言开发工具中只有C编译器而没有完整的C标准库。

在Linux平台上最广泛的C函数库是glibc，其中包含C标准库的实现，也包括本书第三部分介绍的所有系统函数。几乎所有C程序都要调用glic的库函数，所有glibc是Linux平台C程序运行的基础。glibc提供一组头文件和一组库文件，最基本、最常用的C标准库函数和系统函数在libc.so库文件中，几乎所有C程序的运行都依赖于libc.so，有些做数学计算的C程序依赖于libm.so ， 以后还有看到多线程的C程序依赖于libpthread.so。以后说libc时专指libc.so这个库文件，而说glibc时指的是glibc提供的所有库文件。

