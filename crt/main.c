#include <stdio.h>
#include <string.h>

// PORTB
//static volatile char * const VIO0_IO  = (volatile char *)0x6000;
#define  VIO0_IO  ((volatile char *)0x6000)
// PORTA
//static volatile char * const VIO1_IO  = (volatile char *)0x6001;
#define  VIO1_IO  ((volatile char *)0x6001)
// DDRB
//static volatile char * const VIO0_CFG = (volatile char *)0x6002;
#define  VIO0_CFG  ((volatile char *)0x6002)
// DDRA
//static volatile char * const VIO1_CFG = (volatile char *)0x6003;
#define  VIO1_CFG  ((volatile char *)0x6003)

// LCD Control Bits in VIO1
#define LCD_SIG_E  0x80
#define LCD_SIG_RW 0x40
#define LCD_SIG_RS 0x20

#define LCD_ROWS 4
#define LCD_COLS 20

const char line_starts[LCD_ROWS] =
{
    0x80,  // 0x80 | 0x00
    0xC0,  // 0x80 | 0x40
    0x94,  // 0x80 | 0x14
    0xD4   // 0x80 | 0x54
};


char display_ram[LCD_ROWS][LCD_COLS];
char cursor_row=0;
char cursor_col=0;

//void delay(unsigned char c)
//{
//    while(c>0)
//    {
//        c--;
//    }
//}

void lcd_busy_wait(void)
{
    // Set to input mode
    *VIO0_CFG = 0x00;

    // Toggle Enable bits
    do{
        *VIO1_IO=LCD_SIG_RW;
        *VIO1_IO=(LCD_SIG_RW|LCD_SIG_E);
    }
    while( *VIO0_IO & 0x80 );

    *VIO1_IO=LCD_SIG_RW;

    // Set back to output mode
    *VIO0_CFG = 0xFF;
}

void lcd_control(char a)
{
    lcd_busy_wait();

    // Set Control lines
    *VIO0_IO = a;

    // Toggle Enable bits
    *VIO1_IO=0;
    *VIO1_IO=(0|LCD_SIG_E);
    *VIO1_IO=0;
}

void lcd_output(char a)
{
    lcd_busy_wait();

    // Set Control lines
    *VIO0_IO = a;

    // Toggle Enable bits
    *VIO1_IO=LCD_SIG_RS;
    *VIO1_IO=(LCD_SIG_RS|LCD_SIG_E);
    *VIO1_IO=LCD_SIG_RS;
}

void clear_display(void)
{
    memset(display_ram, ' ', LCD_ROWS * LCD_COLS);
    // Clear Display
    // 0000 0001
    lcd_control(0x01);
    cursor_row=0;
    cursor_col=0;
}

void refresh_display(void)
{
    char i=0;
    do
    {
        char j=0;
        char* buf=display_ram[i];
        lcd_control(line_starts[i]);
        do
        {
            lcd_output(buf[j]);
            ++j;
        } while( j<LCD_COLS );
        ++i;
    } while( i<LCD_ROWS);
}

void advance_display_row(void)
{
    if(cursor_row<(LCD_ROWS-1))
    {
        ++cursor_row;
    }
    else
    {
        char i=0;
        char* buf = (void*)display_ram;
        // copy first 2 lines
        do
        {
            buf[i] = buf[i+LCD_COLS];
            ++i;
        } while( i < ((LCD_ROWS-1) * LCD_COLS) );
        do
        {
            buf[i] = ' ';
            ++i;
        } while( i < (LCD_ROWS * LCD_COLS) );
        cursor_row=(LCD_ROWS-1);
    }
}

extern void disable_ints(void);
extern void enable_ints(void);

void write_to_display(char c)
{
    if(c=='\n')
    {
        refresh_display();
        cursor_col=0;
        advance_display_row();
    }
    else if(c=='\r')
    {
        refresh_display();
        advance_display_row();
    }
    else if(c=='\f')
    {
        clear_display();
    }
    else if(cursor_col<LCD_COLS)
    {
         display_ram[cursor_row][cursor_col]=c;
         ++cursor_col;
    }
}

void lcd_output_str( const char* str )
{
    while(*str)
    {
        write_to_display(*str);
        ++str;
    }
}


// This is called by printf, etc
// It needs to be expanded to handle different file descriptors
// and handle control characters such as \n
// https://pubs.opengroup.org/onlinepubs/9699919799/functions/write.html
int write (int /*fd*/, const char* buf, int count)
{
    int i=0;
    while(i<count)
    {
        write_to_display(buf[i]);
        ++i;
    }
    return i;
}

void KBINIT(void);
extern char __fastcall__ KBINPUT(void);
//extern char inputstore;

//  Design target
//  https://pubs.opengroup.org/onlinepubs/9699919799/functions/read.html
int read(int /*fildes*/, char *buf, size_t nbyte)
{
    int i=-1;
    char inputstore;
    if( nbyte > 0 )
    {
        inputstore=KBINPUT();
        if(inputstore == '\r') inputstore = '\n';
        *buf=inputstore;
        i=1;
    }
    return i;
}

static char shared_val=0;

void main_interrupt( void) {
    shared_val++;
}


int main( )
{
    char x=0;
    char tmp[LCD_COLS+1];
    *VIO0_CFG = 0xFF;
    *VIO1_CFG = 0xE0;

    // SET MODE
    // 0011 1000          Set 8-bit, 2-line, 5x8 font mode
    lcd_control(0x38);

    // DISPLAY ON
    // 0000 1110          Display on, Cursor on, Blink Off
    lcd_control(0x0E);

    // Increment mode
    // 0000 0110          Set display mode to auto incremetn to the right
    lcd_control(0x06);

    clear_display();

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

