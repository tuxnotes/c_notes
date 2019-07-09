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

## 3.2 自定义函数

不仅可以调用C标准库提供的函数，也可以定义自己的函数，如定义的main函数。main函数的特殊之处在于执行程序时它自动被操作系统调用，操作系统就认准了main这个名字，除了名字特殊之处，main函数和别的函数没有区别。

给函数命名也要遵循上一章讲过的标识符命名规则。由于我们定义的main函数不带任何参数，参数列表应写成void。函数体可以由若干条语句和声明组成，C89要求所有声明写在所有语句之前(本书的示例代码都遵循这一规定)，而C99的新特性运行语句和声明按任意顺序排序，只要每个标识符都遵循先声明后使用的原则就行。main函数的返回值是int型的，return 0;这个语句表示返回值是0，main函数的返回值是返回给操作系统看的，因为main函数是被操作系统调用的，通常执行成功就返回0，在执行过程中出错就返回一个非零值。比如我们将main函数中的return语句改成return 4;再执行它，执行结束后可以在shell中看到它的退出状态(Exit Status):

```c
# include <stdio.h>

int main(void)
{
    int hour;
    int minute = 59;
    printf("%d and %d hours\n", hour, minute / 60);
    return 4;
}
```

```bash
$ ./a.out
11 and 0 hours
$ echo $?
4
```

$?是shell中的一个特殊变量，表示上一条命令的退出状态。

关于main函数需要注意两点：

- 1 K&R书上的main函数定义写成了main(){...}的形式，不写返回值类型也不写参数列表，这是Old Style C的风格。Old Style C规定不写返回值类型就表示返回int型，不写参数列表就表示参数类型和个数没有明确指出。这种宽松的规定使编译器无法检查程序中可能存在的Bug，增加了调试难度，不幸的是现在的C标准为了兼容旧的代码仍然保留了这种语法，但读者绝不应该继续使用这种语法。
- 2 其实操作系统在调用main函数时是传参数的，main函数最标准的形式应该是int main(int argc, char *argv[]) , 在第6节 指向指针的指针与指针数组详细介绍。 C标准也允许int main(void)这种写法，如果不使用系统传进来的来个参数也可以写成这种形式。但除了这两种形式之外，定义main函数 的其他写法都是错误的或不可移植的。

关于返回值和return语句将在第5章第1节return语句中详细讨论。

先从不带参数也没有返回值的函数开始学习定义和使用函数：

```c
#include <stdio.h>

void newline(void)
{
    printf("\n");
}

void threeline(void)
{
    newline();
    newline();
    newline();
}    

int main(void)
{
    printf("Three lines.\n");
    threeline();
    printf("Another three lines.\n");
    threeline();
    return 0;
}    
```

通过这个简单的例子可以体会到：

- 1 同一个函数可以被多次调用
- 2 可以用一个函数调用另一个函数，后者再去调第三个函数
- 3 通过自定义函数可以给一组复杂的操作起一个简单的名字，例如threeline。对于main函数来说，只需要通过threeline这个简单的的名字来调用就行，不必直到打印三个空格具体怎么做，所有复杂的操作都被隐藏在threeline这个名字后面
- 4 使用自定义函数可以使代码更简洁，main函数在任何地方想打印三个空行只需要调用一个简单的threeline(),而不必每次都写三个printf("\n")

阅读代码和阅读文章的过程不一样。**阅读代码的过程就是模仿计算机执行程序的过程，我们不仅要记住当前读到了哪一行代码，还要记住现在读的代码是被那个函数调用的，这段代码返回后应该从上一个函数的什么地方接着往下读**。

### 3.2.1 函数声明 函数定义 函数原型

**函数原型Prototype**: 声明一个函数的名字、参数类型和个数、返回值类型。如void threeline(void)

代码中可以单独写一个函数原型，后面加;号结束，而不写函数体.如：

```c
void threeline(void);
```

这种写法只能叫函数声明而不能 叫函数定义，只有带函数体的声明才叫定义。前面讲过，只有分配存储空间的变量声明才叫定义，其实函数也一样，编译器只有见到函数定义才会生成指令，而指令在程序运行时当然也要占存储空间。

那没有函数体的函数声明有什么用呢？

它为编译器提供了有用信息，编译器在翻译代码的过程中，只有见到函数原型(不管带不带函数体)之后才直到这个函数的名字、参数类型和返回值，这样碰到函数调用时才知道怎么生成相应的指令，所以**函数原型必须出现在函数调用之前**，这也是遵循"先声明后使用"的原则。

上面的例子中，main调用threeline，threeline在调用newline，要保证每个函数的原型出现在调用之前，就只能按先newline再threeline再main的顺序定义了。如果使用不带函数体的声明，则可改变函数的定义顺序：

```c
#include <stdio.h>

void newline(void);
void threeline(void);

int main(void)
{
    ...
} 

void newline(void)
{
    ...
}    

void threeline(void)
{
    ...
}    
```

由于有Old Style C语法的存在，并非所有函数声明都包含完整的函数原型，如void threeline(); 这个声明并没有明确指出参数类型和个数，所以不算函数原型，这个声明提供给编译器的信息只有函数名和返回值类型。如果这样的声明之后调用函数，编译器不知道参数的类型和个数，就不会做语法检查，所以容易引入Bug。

## 3.3 形参和实参

带参数的函数定义中要指明参数的个数和每个参数的类型。定义参数就像定义变量一样，需要为每个参数指明类型，参数的命名也要遵循标识符命名规则：

```c
#include <stdio.h>

void print_time(int hour, int minute)
{
    printf("%d:%d\n", hour, minute);
}    

int main(void)
{
    print_time(23,59);
    return 0;
}    
```

需要注意的是，定义变量时可以把相同类型的变量列在一起，而定义参数却不可以，如下面的写法是错误的：

```c
void print_time(int hour, minute)
{
    printf("%d:%d\n", hour, minute);
}    
```

### 3.3.1 形参和实参

**形参相当于函数中定义的变量，调用函数传递参数的搓成相当于定义形参变量并且用实参的值来初始化**。

例如这样调用：

```c
void print_time(int hour, int minute)
{
    printf("%d:%d\n", hour, minute);
}    

int main(void)
{
    int h = 23, m =59;
    print_time(h, m);
    return 0;
}    
```

相当于在函数print_time中执行了这样一些语句：

```c
int hour = h;
int minute = m;
printf("%d:%d\n", hour, minute);
```

main函数的变量h和print_time函数的参数hour是两个不同的变量，只不过他们的存储空间中都保存了相同的值23，因为变量h的值赋给了参数hour。同理变量m的值赋给了参数minute。**C语言的这种传递参数的方式称为Call by Value**。**在调用函数时，每个参数都需要得到一个值，函数定义中有几个形参，在调用时就要传几个实参，不能多也不能少，每个参数的类型也必须对应得上**。

但是为什么我们每次调用printf传的实参个数不一样呢？因为C语言规定了一种特殊的参数列表格式，用命令man 3 printf可以查看到printf函数的原型：

```c
int printf(const char *format, ...);
```

第一个参数是const char *类型的，后面的...可以代表0个或任意多个参数，这些参数的类型也是不确定的，这称为可变参数Variable Argument，可变参数将在第24章第6节可变参数详细讨论。

总之，每个函数的原型都明确规定了返回值类型以及参数的类型和个数，即使像printf这样规定为"不确定"也是一种明确的规定，**调用函数是要严格遵守这些规定**，有时候把函数叫做接口(interface)，调用函数就是使用这个接口，使用接口的前提是必须和接口保持一致。









