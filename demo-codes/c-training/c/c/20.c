#include <stdio.h>

int main(int argc, const char *argv[])
{
    int money = 50, count = 30;
    int i, j, k;
    for (i = 0; i <= count; i++) 
        for (j = 0; j <= count; j++) 
            for (k = 0; k <= count; k++) 
            {
                if ((i + j + k == count) && (3 * i + 2 * j + k == money)) 
                    printf("man = %d, woman = %d, child = %d\n", i, j, k);
            }
    return 0;
}
