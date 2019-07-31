# 6 循环语句

## 6.1 while语句

前面介绍了用递归求n!的方法，其实每次递归调用都在重复做同样一件事，就是把n乘到(n-1)!上然后把结果返回。虽说是重复，但每次做都稍微有一点区别(n的值不一样)，这种每次都有一点区别的重复工作称为迭代(Iteration)。计算最擅长的就是把一件工作重复做成千上万此而不出错。将factorial的递归方式改成while语句：

```c
int factorial(int n)
{
    int result = 1;
    while(n > 0){
        result = result * n;
        n = n - 1;
    }
    return result;
}
```

