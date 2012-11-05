/*
 *从键盘输入一指定金额（以元为单位，如345.78），然后显示支付该金额的各种面额的人民币的数量，要求显示100元、50元、10元、5元、2元、1元、1角、5分、
 1分各多少张。
 */
#include <stdio.h>

int get_answer(float money)
{
    int a[9] = {0};
    float bill[9] = {100.0, 50.0, 10.0, 5.0, 2.0, 1.0, 0.1, 0.05, 0.01};
    int i;
    for (i = 0; i < 9; i++) 
    {
        while(money >= bill[i])
        {
            money -= bill[i];
            a[i]++;
        }
    }

    for (i = 0; i < 9; i++) 
    {
        printf("%.2f Yuan %d piece\n", bill[i], a[i]);
    }
}

int main(int argc, const char *argv[])
{
    float money = 0;
    printf("Please input the money: ");
    scanf("%f", &money);
    get_answer(money);
    return 0;
}
