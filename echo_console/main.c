#include "io_echo.h"
#include <stdio.h>

static char shared_val=0;

void main_interrupt( void) {
    shared_val++;
}

int main( )
{
    //char x=0;
    char tmp[LCD_COLS+1];

    console_reset();

    printf("Hello, \rWorld! Have a nice day!\n");
    //lcd_output_str("Have a nice day!!!\n");

    //for(x=1;x<100;++x)
    //for(;;)
    while(1)
    {
        //scanf("%c", &tmp);
        //tmp=getchar();
        //if(tmp == '\r') tmp = '\n';
        //putchar(tmp);

        //scanf("%s", tmp);
        //printf("%s\n", tmp);

        fgets(tmp, LCD_COLS+1, stdin);
        fputs(tmp,stdout);
        //putchar('\n');


        //printf("Value: 0x%02X  0x%02X\n", x, inputstore);
        //if(inputstore == '\r') inputstore = '\n';
        //putchar(inputstore);
        //printf("%c", inputstore);
        //scanf("%c", &inputstore);
        //KBINPUT();
    }

    return 0;
}

