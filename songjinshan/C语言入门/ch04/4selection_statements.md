# 第4章 分支语句

## 4.1 if语句

有时我们需要检查一个条件，然后根据检查的结果执行不同的后续代码，在C语言中可以用分支语句Selection Statement实现，如：

```c
if (x != 0) {
    printf("x is nonzero.\n");
}
```

其中x != 0表示"x不等于0"的条件，这个表达式称为控制表达式Controlling Expression，如果条件成立，则{}中的语句被执行，否则{}中的语句不执行，直接跳到}后面。if和控制表达式改变了程序的控制流程Control Flow，不再是从前到后顺序执行，而是根据不同的条件执行不同的语句，这种控制流程称为分支Branch。

关系运算符和相等性运算符：

| 运算符 | 含义       |
| ------ | ---------- |
| ==     | 等于       |
| !=     | 不等于     |
| >      | 大于       |
| <      | 小于       |
| \>=    | 大于或等于 |
| <=     | 小于或等于 |

这里要注意以下几点：

- 这里的==表示数学中相等关系，相当于数学中的=号。在C语言中=号是赋值运算符。
- 如果表达式所表示的比较关系成立则值为真True,否则为False，在C语言中分别用int型的1和0表示。
- 在数学中a<b<c表示b即大于a又小于c，但作为C语言的表达式却不是这样。以上集中运算符都是左结合的。
- 这些运算符的两个操作数应该是相同类型的，两边都是整型或都是浮点型可以比较，但两个字符串不能做比较。
- ==和!=称为相等性运算符Equality Operator, 其余四个称为关系运算符Relational Operator，相等性运算符的优先级低于关系运算符。

和if语句相关的语法规则如下：

语句---> if (控制表达式) 语句

语句---> {语句列表}

语句---> ;

在C语言中，任何允许出现语句的地方既可以是由;号结尾的一条语句，也可以是由{}括起来的若干条语句或声明组成的语句块Statement Block, 语句块和上一张介绍的函数体的语法相同。注意语句块的}后面不需要加;号。如果}后面加了;号，则这个;号本身有事一条新的语句了，在C语言中一个单独的;号表示一条空语句Null Statement.

上例的语句块只有一条语句，其实没必要携程语句块，可以简单地写成：

```c
if (x != 0)
    printf("x is nonzore.\n");
```

语句块中也可以定义几步变量，如：

```c
void foo(void)
{
    int i = 0;
    {
        int i = 1;
        int j = 2;
        printf("i=%d, j=%d\n", i, j);
    }
    printf("i=%d\n", i); /* cannot access j here */
}    
```

和函数的局部变量同样道理，每次进入语句块时为变量j分配存储空间，每次退出语句块是释放变量j的存储空间。语句块也构成一个作用域，语句块中的变量j在退出语句块之后就没有了，因此最后一行的printf不能打印变量j，否则编译器会报错。语句块可以用在任何允许出现语句块的地方，不一定非得用在if语句中，单独使用语句块通常是为了定义一些比函数的局部变量更"局部"的变量。

## 4.2 if/else语句

```c
if (x % 2 == 0)
    printf("x is even.\n");
else 
    printf("x is odd.\n");
```

这里的%是取模Modulo运算符，C语言规定%运算符的两个操作数必须是整型的。**%运算符的结果总是与被除数同号**。

if或if/else可以嵌套使用：

```c
if (x > 0)
    printf("x is positive.\n");
else if (x < 0)
    printf("x is negative.\n");
else 
    printf("x is zero.\n");
```

也可以这样：

```c
if (x > 0) {
    printf("x is positice.\n");
} else {
    if (x < 0)
        printf("x is negative.\n");
    else
        printf("x is zero.\n");
}
```

## 4.3 布尔代数

运算符的优先级顺序是：!高于* / %, 高于+ - , 高于> < >= <=, 高于== != , 高于&& , 高于|| , 高于=

写一个控制表达式可能同时用到这些运算符中的多个，如果记不清楚运算符的优先级一定要多套括号。

## 4.4 switch语句

```c
#include <stdio.h>

void print_day(int day)
{
    switch (day) {
        case 1:
            printf("Monday.\n");
            break;
        case 2:
            printf("Tuesday\n");
            break;
        case 3:
            printf("Wednesday\n");
            break;
        case 4:
            printf("Thursday\n");
            break;
        case 5:
            printf("Friday\n");
            break;
        case 6:
            printf("Saturday\n");
            break;
        case 7:
            printf("Sunday\n");
            break;
        default:
            printf("Illegal day number!\n");
            break;
    }
}    

int main(void)
{
    print_day(2);
    return 0;
}    
```

如果传入的参数是2，则从case 2分支开始执行，先是打印相应的信息，然后遇到break语句，它的作用是跳出整个switch语句块。

C语言规定各case分支的常量表达式必须互不相同，如果控制表达式不等于任何一个常量表达式，则从default分支开始执行。通常把default分支写在最后，但不是必须的。使用switch语句要注意以下几点：

- 1 case后面跟表达式的必须是常量表达式，这个值和全局变量的初始值一样，必须在编译时计算出来。
- 2 浮点型不适合做精确比较，所以C语言规定case后面跟的必须是整型常量表达式。
- 3 进入case后如果没有遇到break语句就会一致往下执行，后面其他case或default分支的语句也会被执行，直到遇到break或执行到整个switch语句块的末尾。通常每个case后面都要加上break语句，但有事故意不加break来利用这个特性。例如:

```c
#include <sdtio.h>

void print_day(int day)
{
    switch(day) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            printf("Weekday\n");
            break;
        case 6:
        case 7:
            printf("Weekend.\n");
            break;
        default:
            printf("Illegal day number!\n");
            break;
    }
}    

int main(void)
{
    print_day(2);
    return 0;
}    
```

switch语句不是必不可缺的，可以用一个或多个if...else的组合代替。但是一方面用switch语句回事代码更清晰，另一方面，有事编译器会对switch语句进行整体优化，使它比等价的if/else语句生成的指令效率跟高。

