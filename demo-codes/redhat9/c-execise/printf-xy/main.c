#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main ()
{
        while (1) {
                time_t sec  = time(NULL);
                struct tm t = *localtime(&sec);

                printf("\x1b[2J");      /* clear screen and home cursor */
                printf("\x1b[31;40m");  /* red foreground, black background */
                printf("\x1b[11;29H");  /* moves cursor to line 11, column 29 */
                printf("+-----^--^-----+\n");
                printf("\x1b[12;29H");
                printf("|\t%02d:%02d:%02d:  |\n", t.tm_hour, t.tm_min, t.tm_sec);
                printf("\x1b[13;29H");
                printf("+-------V------+\n");
                sleep(1);
        }

        return 0;
}
