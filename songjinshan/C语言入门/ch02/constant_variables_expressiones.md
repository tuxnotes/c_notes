# 2 常量、变量、表达式

## 2.1 注释

```c
#include <stdio.h>

/*
 * comment1
 * main: generate some simple out put
 */

int main(void)
{
    printf(/* comment2 */"Hello, world.\n"); /*
comment3 */
    return 0;
}
```

第一个注释跨越了四行，注释界定符(Delimiter)是/\*和\*/ ， 中间两行开头的*号没有特殊含义，只是为了看起来整齐，这不是语法规则而是大家都遵守的C代码风格(coding style)之一。

使用注释需要注意的两点：

- 注释不能嵌套(Nest)使用，就是一个主食的文字中不能再出现/\*和\*/了。
- 有的C代码中有类似// comment的注释，两个/斜线(slash)表示从这里直到该行末尾的所有字符都属于注释，这种注释不能跨行，也不能穿插在一行代码中间。



