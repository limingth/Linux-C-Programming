/*给出一百分制成绩，要求输出成绩等级’A’,’B’,’C’,’D’,’E’。
 * 90分以上为’A’，80－89分为’B’，70－79分为’C’，60－69分为’D’，
 * 60分以下为’E’
*/
#include <stdio.h>

char get_grade(int mark)
{
    switch (mark / 10)
    {
        case 10:
        case 9 :    return 'A'; break;
        case 8 :    return 'B'; break;
        case 7 :    return 'C'; break;
        case 6 :    return 'E'; break;
        default :   return 'D'; break;
    }
}

int main(int argc, const char *argv[])
{
    int mark;
    char grade;

    do {
    printf("Please enter a integer <= 100: ");
    scanf("%d", &mark);
    }
    while(mark > 100 || mark < 0);

    grade = get_grade(mark);
    printf("%d is %c\n", mark, grade);

    return 0;
}
