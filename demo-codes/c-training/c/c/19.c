#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int get_max(int num[], int size)
{
    int max = num[0];
    int i = 0;
    for (i = 0; i < size; i++) 
    {
        if (max < num[i]) 
        {
            max = num[i];
        }
    }
    return max;
}

int get_min(int num[], int size)
{
    int min = num[0];
    int i = 0;
    for (i = 0; i < size; i++) 
    {
        if (min > num[i]) 
        {
            min = num[i];
        }
    }
    return min;
}

float get_average(int num[], int size)
{
    int sum = 0;
    int i = 0;
    for (i = 0; i < size; i++) 
    {
        sum += num[i];
    }
    return (float)sum / size;
}

int get_sum(int num[], int size)
{
    int sum = 0;
    int i = 0;
    for (i = 0; i < size; i++) 
    {
        sum += num[i];
    }
    return sum;
}

int main(int argc, const char *argv[])
{
    int num[20];
    int i = 0;

    srand(time(NULL));

    printf("The random num are following:\n");
    for (i = 0; i < 20; i++) 
    {
        num[i] = rand() % 50;
        printf("%d\t", num[i]);
    }
    printf("\nThe max num is: %d\n", get_max(num, 20));
    printf("The min num is: %d\n", get_min(num, 20));
    printf("The average is: %f\n", get_average(num, 20));
    printf("The sum is: %d\n", get_sum(num, 20));
    return 0;
}
