/**
 * @file    [FileName.c]
 * @author  Ted Kotz <ted@kotz.us>
 * @version 0.1
 *
 * [Description]
 *
 */

/* Includes ******************************************************************/
#include "io_echo.h"

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "pckybd.h"
#include "cc65internals.h"

/* Defines *******************************************************************/
// PORTB
//static volatile char * const VIO0_IO  = (volatile char *)0x6000;
#define  VIO0_IO  ((volatile unsigned char *)0x6000)
// PORTA
//static volatile char * const VIO1_IO  = (volatile char *)0x6001;
#define  VIO1_IO  ((volatile unsigned char *)0x6001)
// DDRB
//static volatile char * const VIO0_CFG = (volatile char *)0x6002;
#define  VIO0_CFG  ((volatile unsigned char *)0x6002)
// DDRA
//static volatile char * const VIO1_CFG = (volatile char *)0x6003;
#define  VIO1_CFG  ((volatile unsigned char *)0x6003)

// LCD Control Bits in VIO1
#define LCD_SIG_E  0x80
#define LCD_SIG_RW 0x40
#define LCD_SIG_RS 0x20

#define LCD_CTRL_CLRSCR 0x01

#define LCD_CTRL_HOME   0x02

#define LCD_CTRL_ENTMOD_INC_RT   0x06
#define LCD_CTRL_ENTMOD_DEC_LT   0x05

#define LCD_CTRL_DISPOFF         0x08
#define LCD_CTRL_DISPON_CURSOFF  0x0C
#define LCD_CTRL_DISPON_CURSON   0x0F

#define LCD_CTRL_SET_ADDR_BIT    0x80



/* Types *********************************************************************/
typedef struct ConsoleIoFlags
{
    unsigned cursor:1;
    unsigned echo:1;
} ConsoleIoFlags;

/* Interfaces ****************************************************************/
/* Data **********************************************************************/
const char line_starts[LCD_ROWS] =
{
    0x80,  // 0x80 | 0x00
    0xC0,  // 0x80 | 0x40
    0x94,  // 0x80 | 0x14
    0xD4   // 0x80 | 0x54
};


char display_ram[LCD_ROWS][LCD_COLS];
static char cursor_row=0;
static char cursor_col=0;
static ConsoleIoFlags flags={1,1};
//#pragma zpsym("flags");
//#pragma zpsym("cursor_row");
//#pragma zpsym("cursor_col");

/* Functions *****************************************************************/

/**
 * [Description]
 *
 * @param
 * @return
 */

//void delay(unsigned char c)
//{
//    while(c>0)
//    {
//        c--;
//    }
//}

/**
 * Waits for LCD to go idle and returns status register.
 *
 * @return LCD Status Register
 */
unsigned char lcd_busy_wait(void)
{
    unsigned char retVal;
    // Set to input mode
    *VIO0_CFG = 0x00;

    // Toggle Enable bits
    do{
        *VIO1_IO=LCD_SIG_RW;
        *VIO1_IO=(LCD_SIG_RW|LCD_SIG_E);
        retVal = *VIO0_IO;
    }
    while( retVal & 0x80 );

    *VIO1_IO=LCD_SIG_RW;

    // Set back to output mode
    *VIO0_CFG = 0xFF;

    return retVal;
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

void clrscr (void)
{
    memset(display_ram, ' ', LCD_ROWS * LCD_COLS);
    // Clear Display
    // 0000 0001
    lcd_control(LCD_CTRL_CLRSCR);
    cursor_row=0;
    cursor_col=0;
}

// void refresh_display(void)
// {
//     char i=0;
//     do
//     {
//         char j=0;
//         char* buf=display_ram[i];
//         lcd_control(line_starts[i]);
//         do
//         {
//             lcd_output(buf[j]);
//             ++j;
//         } while( j<LCD_COLS );
//         ++i;
//     } while( i<LCD_ROWS);
// }
//
// void advance_display_row(void)
// {
//     if(cursor_row<(LCD_ROWS-1))
//     {
//         ++cursor_row;
//     }
//     else
//     {
//         char i=0;
//         char* buf = (void*)display_ram;
//         // copy first 2 lines
//         do
//         {
//             buf[i] = buf[i+LCD_COLS];
//             ++i;
//         } while( i < ((LCD_ROWS-1) * LCD_COLS) );
//         do
//         {
//             buf[i] = ' ';
//             ++i;
//         } while( i < (LCD_ROWS * LCD_COLS) );
//         cursor_row=(LCD_ROWS-1);
//     }
// }
//
// void write_to_display(char c)
// {
//     if(c=='\n')
//     {
//         refresh_display();
//         cursor_col=0;
//         advance_display_row();
//     }
//     else if(c=='\r')
//     {
//         refresh_display();
//         advance_display_row();
//     }
//     else if(c=='\f')
//     {
//         clrscr();
//     }
//     else if(cursor_col<LCD_COLS)
//     {
//          display_ram[cursor_row][cursor_col]=c;
//          ++cursor_col;
//     }
// }
//
// void lcd_output_str( const char* str )
// {
//     while(*str)
//     {
//         write_to_display(*str);
//         ++str;
//     }
// }


// This is called by printf, etc
// It needs to be expanded to handle different file descriptors
// and handle control characters such as \n
// https://pubs.opengroup.org/onlinepubs/9699919799/functions/write.html
int write (int /*fd*/, const char* buf, int count)
{
    int i=0;
    while(i<count)
    {
        if(*buf == '\n')
        {
            cputc('\r');
        }
        cputc(*buf);
        ++buf;
        ++i;
    }
    return i;
}

//extern char inputstore;

//  Design target
//  https://pubs.opengroup.org/onlinepubs/9699919799/functions/read.html
int read(int /*fildes*/, char *buf, size_t nbyte)
{
    int count=-1;
    if( nbyte > 0 )
    {
        *buf = cgetc();
        if( *buf == '\r' ) *buf = '\n';
        if(flags.echo)
        {
            if ( '\n' == *buf )
            {
                cputc('\r');
            }
            cputc(*buf);
        }
        count = 1;
    }
    return count;
}




void console_reset(void)
{
    // SET VIO pin MUX settings to control screen and keyboard
    *VIO0_CFG = 0xFF;
    *VIO1_CFG = 0xE0;

    // SET MODE
    // 0011 1000          Set 8-bit, 2-line, 5x8 font mode
    lcd_control(0x38);

    // DISPLAY ON
    // 0000 1110          Display on, Cursor on, Blink Off
    lcd_control(LCD_CTRL_DISPON_CURSOFF);

    // Increment mode
    // 0000 0110          Set display mode to auto increment to the right
    lcd_control(0x06);

    clrscr();
}

void __fastcall__ screensize (unsigned char* x, unsigned char* y)
{
    *x=LCD_COLS;
    *y=LCD_ROWS;
}

void __fastcall__ gotoxy (unsigned char x, unsigned char y)
{
    if( (x < LCD_COLS) && (y < LCD_ROWS) )
    {
        cursor_col = x;
        cursor_row = y;
        lcd_control (LCD_CTRL_SET_ADDR_BIT | line_starts[y] + x);
    }
}

void __fastcall__ gotox (unsigned char x)
{
    gotoxy(x, cursor_row);
}

void __fastcall__ gotoy (unsigned char y)
{
    gotoxy(cursor_col, y);
}

void __fastcall__ cclear (unsigned char length)
{
    char* const row = display_ram[cursor_row];
    while( --length && cursor_col<LCD_COLS)
    {
        lcd_output(' ');
        row[cursor_col]=' ';
        ++cursor_col;
    }
}

void __fastcall__ cclearxy (unsigned char x, unsigned char y, unsigned char length)
{
    gotoxy(x,y);
    cclear(length);
}

void newline (void)
{
    char i;
    char* row;
    ++cursor_row;
    if (cursor_row >= LCD_ROWS) cursor_row=0;

    lcd_control (LCD_CTRL_SET_ADDR_BIT | line_starts[cursor_row]);
    row=display_ram[cursor_row];
    i=LCD_COLS;
    while( i )
    {
        lcd_output(' ');
        row[--i]=' ';
    }
    lcd_control (LCD_CTRL_SET_ADDR_BIT | line_starts[cursor_row] + cursor_col);
}

void __fastcall__ cputc (char c)
{
    char* preservePtr1=__PTR1__;
    unsigned int preserveSreg=__SREG__;
    if(c=='\n')
    {
        newline();
    }
    else if(c=='\r')
    {
        cursor_col = 0;
        lcd_control (LCD_CTRL_SET_ADDR_BIT | line_starts[cursor_row]);
    }
    else if(c=='\f')
    {
        clrscr();
    }
    else if(cursor_col<LCD_COLS)
    {
        lcd_output(c);
         display_ram[cursor_row][cursor_col]=c;
         ++cursor_col;
    }
    __PTR1__ = preservePtr1;
    __SREG__ = preserveSreg;
}

char cgetc (void)
{
    char c;
    char* preservePtr1=__PTR1__;
    unsigned int preserveSreg=__SREG__;
    if (flags.cursor) lcd_control(LCD_CTRL_DISPON_CURSON);
    c=KBINPUT();
    // if(c == '\r') c = '\n';
    lcd_control(LCD_CTRL_DISPON_CURSOFF);
    __PTR1__ = preservePtr1;
    __SREG__ = preserveSreg;
    return c;
}

unsigned char __fastcall__ cursor (unsigned char onoff)
{
    unsigned char returnVal = flags.cursor;
    if( onoff )
    {
        flags.cursor = 1;
    }
    else
    {
        flags.cursor = 0;
    }
    return returnVal;
}

unsigned char __fastcall__ echo (unsigned char onoff)
{
    unsigned char returnVal = flags.echo;
    if( onoff )
    {
        flags.echo = 1;
    }
    else
    {
        flags.echo = 0;
    }
    return returnVal;
}

unsigned char kbhit (void)
{
    return KBSCAN();
}

char* __fastcall__ cgets (char* buf, unsigned char size)
{
    char* retVal=buf;
    if( size <= 1)
    {
        return NULL;
    }
    else
    {
        *buf = cgetc();
        while( *buf != '\r' && *buf != '\n' && (size>1) )
        {
            if(flags.echo)
            {
                cputc(*buf);
            }
            --size;
            ++buf;
            *buf = cgetc();
        }
        if(flags.echo)
        {
            cputc('\r');
            cputc('\n');
        }
        *buf = '\0';
    }
    return retVal;
}
