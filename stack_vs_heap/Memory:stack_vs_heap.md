# Memory: Stack vs Heap

This document from https://www.gribblelab.org/CBootCamp/7_Memory_Stack_vs_Heap.html

[C Programming Boot Camp][https://www.gribblelab.org/CBootCamp/]

# 1 Stack vs Heap

So far we have seen how to declare basic type variables such as int, double
etc. and complex types such as arrays and structs. The way we have been 
declaring them so far , with a sybtax that is like other languages such
as MATLAB , Python, etc, puts these variables on the **stack** in c.

## 1.1 The Stack

什么是stack？stack是计算机内存的一块特殊区域，用来存储每个函数(包括main函数)
创建的临时变量.stack是LIFO类型的数据结构，基本由CPU进行管理和优化。每当函数
创建一个新的变量，变量就会被压入栈中，当函数退出的时候，所有由这个函数push到
stack中的变量都会被释放(删除).

使用stack进行变量存储的优点是：内存是自动管理的。不需要手动分配内存，当不
需要的时候也不需要手动释放。并且CPU对stack内存的组织是非常高效的，读写非常
快速。

A key to understanding the stack is the notion that ** whnd a function exits**
all of its variables are popped off of the stack(and hence lost forever).
Thus stack variables are **local** in nature. This is related to a concept
we saw earlier as **variable scope**, or local vs global variables. A common
bug in c programming is attempting to accesses a variable that was created
on the stack inside some function, from a place in your program outside of
that function(i.e after function has exited)

理解stack的关键点是：当函数退出后，所有此函数在stack中创建的变量会永久释放。
这是stack的局部性。这与之前提到的变量作用范围的概念相关--局部变量和全局变量。
C语言编程中的一个常见错误是在函数函数外部访问另一个函数在stack中创建的变量，
但是创建变量的函数已经退出。
stack的另一个特性需要记住的是，stack中存储的变量数量是有限制的。这点在heap
中是不同的。

总结stack的特点如下：

 - the stack grows and shrinks as function push and pop local variables
 - there is no need to manage the memory yourself, variables are allocated and freed automatically
 - the stack has size limits
 - stack variables only exist while the function that created them, is running
 
## 1.2 The Heap

heap是计算机中内存的一块区域，但不是自动管理的，CPU也很少参与管理。It is a 
more free-floating region of memory (and is larger). 在heap中分配内存，你
必须使用malloc()或calloc() C内置函数。一旦你在heap中分配了内存，当你不需要
这些内存是，你负责使用free()函数来释放内存。如果你不这么做，你的程序就存在
内存泄露。That is , memory on the heap will still be aside(and won't be
available to other processes). 在debugging部分提到，有个一个工具valgrind能
帮助你检测内存泄露。

Unlike the stack, the heap does not have size restriction on variable 
size (apart from the obvious physical limitaions of your computer). Heap
memory is slightly slower to be read from and srite to, because one has to
use pointer to access memory on the heap. We will talk about pointers shortly.
与stack不同的是，heap对变量个数没有限制(取决于物理内存).heap内存的读写会稍微
的慢一点，因为需要使用指针来访问heap内存。

Unlike the stack, variables created on the heap are accessible by any function, anywhere in your program. Heap variables are essientially global in scope.
与stack不同的是，heap中创建的变量可以被你程序中的任何位置的任何函数访问。Heap中的变量基本是全局范围的。

## 1.3 Stack vs Heap Pros and Cons

**Stack**

    - vary fast access
    - don't have to explicitly de-allocate variables
    - space is managed efficiently by CPU, memory will not become fragmenteed
    - local variables only
    - limit on stack size (OS-dependent)
    - variables cannot be resized
    
**Heap**

    - varaibles can be accessed globally
    - no limite on memory size
    - (relatively) slower access
    - no guaranteed efficient use of space, memory may become fragmented over time as blocks of memory are allocated, then freed
    - you must manage memory (you're in charge of allocating and freeing variable)
    - variables can be resized using realloc()
    

## 1.4 Examples

Here is a short program that create its variables on the **stack** .
It looks like the other programs we have seen so far.

```c

#include <stdio.h>

double multiplyByTwo (double input) {
    double twice = input * 2.0;
    return twice;
}

int main (int argc, char *argv[])
{
    int age = 30;
    double salary = 12345.67;
    double myList[3] = {1.2, 2.3, 3.4};

    printf("double your salary is %.3f\n", multipleByTwo(salary));
    return 0;
}

```

在104-106行声明了几个变量: an int, a doubl and  an array of three doubles.
当main函数分配这三个变量的时候，这三个变量就会被压入栈中。当main函数退出时
这些变量会从栈中弹出。multipleByTwo函数也是这样。

As a side note, there is a way to tell C to keep a stack variable around, 
enven after its creator function exits, and that is to use the **static** 
keyword when declaring the variable. A variable declared with the **static**
keyword thus becomes something like a global variable, but one that is only
visible inside the funtion that created it. It's a strange construction, one
that you probably won't need except under very specific circumstances.

Here is another version of this program that allocates all of its varaibles 
on the **heap** instead of the stack:

```c
#include <stdio.h>
#include <stdlib.h>

 double *multipleByTwo (double *input) {
    double *twice = malloc(sizeof(double));
    *twice = *input * 2.0;
    return twice;
 }

 int main(int argc, char *argv[])
 {
    int *age = malloc(sizeof(int));
    *age = 30;
    double *salary = malloc(sizeof(double));
    *salary = 12345.67;
    double *myList = malloc(3 * sizeof(double));
    myList[0] = 1.2;
    myList[1] = 2.3;
    myList[2] = 3.4;

    double *twiceSalary = multipleByTwo(salary);

    pintf("double your salary is %.3f\n", *twiceSalary);

    free(age);
    free(salary);
    free(myList);
    free(twiceSalary);

    return 0;
 }

 ```

 使用malloc()函数在堆上分配内存，使用free()函数释放内存。
 The malloc() (and calloc() and free()) deal with **pointers** not actual
 values.

## 1.5 When to use the Heap?

什么时候使用heap,什么时候使用stack。当需要分配大块内存时(如大的数组，大的
结构体)，且你需要变量保存较长的时间(like a global)，那么你应该在heap上分配。
如果你处理的是空间占用相对较小的变量，且仅在函数中使用，那就在stack中分配，
即容易又快速。如果你需要数组和结构能动态改变大小(如数组可以根据需要进行扩大
和缩小)，那很可能你需要在heap中分配，使用内存函数malloc(), calloc(), free()
函数手动管理内存.

## 1.6 Links

    - [The Stack and the Heap][http://www.learncpp.com/cpp-tutorial/79-the-stack-and-the-heap/]
    - [What and Where are the stack and heap][http://stackoverflow.com/questions/79923/what-and-where-are-the-stack-and-heap]
