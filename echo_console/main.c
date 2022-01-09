#include "io_echo.h"
#include <stdio.h>
#include <conio.h>

static char shared_val=0;

void main_interrupt( void) {
    shared_val++;
}

int main( )
{
    char c;
    char tmp[LCD_COLS+10];
    char* tmp_ptr;

    console_reset();

    printf("Hello, \nWorld!\r Have a nice day!\r\n");
    //lcd_output_str("Have a nice day!!!\n");

    //for(x=1;x<100;++x)
    //for(;;)
    while(1)
    {
        //scanf("%c", &c);
        //c=getchar();
        //if(c == '\r') c = '\n';
        //putchar(c);

        scanf("%s", tmp);
        printf("%s\n", tmp);

        //fgets(tmp, LCD_COLS+1, stdin);
        //fputs(tmp,stdout);
        //putchar('\n');

        //cscanf("%s", tmp);
        //cgets(tmp, LCD_COLS+1);

        //cputs(tmp);
        //cputs("\r\n");

        //tmp_ptr=tmp;
        //while(*tmp_ptr)
        //{
        //    cputc(*tmp_ptr++);
        //}
        //cputc('\r');
        //cputc('\n');


        //cprintf("%s\r\n", tmp);


        //printf("Value: 0x%02X  0x%02X\n", x, inputstore);
        //if(inputstore == '\r') inputstore = '\n';
        //putchar(inputstore);
        //printf("%c", inputstore);
        //scanf("%c", &inputstore);
        //KBINPUT();
    }

    return 0;
}

