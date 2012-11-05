/*
 *求斜边的长度
*/

#include <stdio.h>
#include <math.h>

double get_lenth(int a, int b)
{
    int c = a * a + b * b;
    double d = sqrt((double)c);
    return d;
}

int main(int argc, const char *argv[])
{
    int a, b;

    printf("Please enter two edges: ");
    scanf("%d %d", &a, &b);
    printf("%lf\n", get_lenth(a, b));

    return 0;
}
