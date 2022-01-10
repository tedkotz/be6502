#include "io_echo.h"
#include <conio.h>
#include <stdio.h>

static char shared_val=0;

void main_interrupt( void) {
    shared_val++;
}

int main( )
{
    /* Data ******************************************************************/
    char tmp[32];

    /* Setup *****************************************************************/
    console_reset();

    cprintf("Hello, World!\r\n");
    //cprintf("Hello, \nWorld!\r Have a nice day!\r\n");

    /* Loop ******************************************************************/
    for(;;)
    {
        // Input character
        //cscanf("%c", &tmp[0]);
        //scanf("%c", &tmp[0]);
        //fscanf(stdin, "%c", tmp[0]);
        //tmp[0]=getchar();
        tmp[0]=cgetc();

        if(tmp[0] == '\r')
        {
            tmp[0] = '\n';
        }

        // Output character
        //cputc(tmp[0]);
        //fputc(tmp[0],stdout);
        //putchar(tmp[0]);
        //printf("%c", tmp[0]);
        cprintf("Value: %c:0x%02X\r\n", tmp[0], (int)tmp[0]);


        // Input String
        //cscanf("%s", tmp);
        //fgets(tmp, sizeof(tmp), stdin);
        //scanf("%s", tmp);
        //fscanf(stdin, "%s", tmp);
        //cgets(tmp, sizeof(tmp));

        // Output String
        //cprintf("%s\r\n", tmp);

        //fputs(tmp,stdout);
        //fputc('\n',stdout);
        //fputs("\n",stdout);

        //printf("%s\n", tmp);

        //fprintf(stdout, "%s\n", tmp);

        //cputs(tmp);
        //cputs("\r\n");
    }

    return 0;
}

