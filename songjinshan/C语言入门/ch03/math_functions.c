#include <math.h>
#include <stdio.h>

int main(void)
{
    double pi = 3.1416;
    /* 数学中的ln函数在C标准库中叫log */
    printf("sin(pi/2)=%f\nln1=%f\n", sin(pi/2), log(1.0));
    return 0;
}

