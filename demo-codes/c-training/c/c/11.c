/*
 *冒泡排序
*/ 
#include <stdio.h>

int *bubble(int *arr,int n)
{
    int i, j, tmp;

    for(i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++) 
        {
            if (arr[j] > arr[j + 1]) 
            {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

int main(int argc, const char *argv[])
{
    int arr[20] = {1, 5, 2, 6, 9, 10, 11, 23, 34, 67, 98, 25, 16, 43, 12, 43, 23, 54, 43, 58};
    int i = 0;
    printf("Before sort:\n");
    for (i = 0; i < 20; i++) 
        printf("%d%c", arr[i], (i + 1) % 5 ? '\t' : '\n');
    
    bubble(arr, 20);

    printf("After sort:\n");
    for (i = 0; i < 20; i++) 
        printf("%d%c", arr[i], (i + 1) % 5 ? '\t' : '\n');
    return 0;
}
