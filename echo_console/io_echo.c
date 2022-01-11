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

#include "cc65internals.h"
#include "pckybd.h"
#include <assert.h>
#include <conio.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

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


#define DISPLAY_RAM_ROWS 8
#define DISPLAY_RAM_COLS 32

#define CONSOLE_DEFAULT_NEWLINE newline_scrollup

/* Types *********************************************************************/
/* Interfaces ****************************************************************/
static void newline_wrap (void);
static void newline_drop (void);
static void newline_scrollup (void);

/* Data **********************************************************************/
const char line_starts[] =
{
    0x80,  // 0x80 | 0x00
    0xC0,  // 0x80 | 0x40
    0x94,  // 0x80 | 0x14
    0xD4   // 0x80 | 0x54
};
const uint8_t LCD_ROWS=4;
const uint8_t LCD_COLS=20;

// const char line_starts[] =
// {
//     0x80,  // 0x80 | 0x00
//     0xC0,  // 0x80 | 0x40
// };
// const uint8_t LCD_ROWS=2;
// const uint8_t LCD_COLS=16;


char display_ram[DISPLAY_RAM_ROWS][DISPLAY_RAM_COLS];
static uint8_t cursor_row=0;
static uint8_t cursor_col=0;
static bool echo = true;
static void (*newline_handler) (void) = CONSOLE_DEFAULT_NEWLINE;
//#pragma zpsym("echoOn");
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
    memset(display_ram, ' ', DISPLAY_RAM_ROWS * DISPLAY_RAM_COLS);
    // Clear Display
    // 0000 0001
    lcd_control(LCD_CTRL_CLRSCR);
    cursor_row=0;
    cursor_col=0;
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

//  Design target
//  https://pubs.opengroup.org/onlinepubs/9699919799/functions/read.html
int read(int /*fildes*/, char *buf, size_t nbyte)
{
    int count=-1;
    if( nbyte > 0 )
    {
        *buf = cgetc();
        if( *buf == '\r' ) *buf = '\n';
        if(echo)
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

static void _console_reset(void)
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

    echo = true;
    __CURSOR__ = true;
    newline_handler = CONSOLE_DEFAULT_NEWLINE;

    clrscr();
}

void __fastcall__ _afailed (const char* file, unsigned line)
{
    _console_reset();
    raise (SIGABRT);
    cprintf ("%s:%u:ASSERT FAILED\n", file, line);
    exit (EXIT_ASSERT);
}

void __fastcall__ failLockUp( unsigned int errCode )
{
    char LEDs=0;
    cprintf ("EC %u\n", errCode);
    for(;;)
    {
        unsigned int i=0x2000;
        LEDs ^= 0xFF;
        KBSLED(LEDs);
        while( i )
        {
            --i;
        }
    }
}

void console_reset(void)
{
    _console_reset();

    assert(((unsigned)LCD_ROWS)<=((unsigned)DISPLAY_RAM_ROWS));
    assert(((unsigned)LCD_COLS)<=((unsigned)DISPLAY_RAM_COLS));
}

void __fastcall__ screensize (unsigned char* x, unsigned char* y)
{
    *x=LCD_COLS;
    *y=LCD_ROWS;
}

void __fastcall__ gotox (unsigned char x)
{
    cursor_col = (x < LCD_COLS) ? x : 0;
    lcd_control (LCD_CTRL_SET_ADDR_BIT | line_starts[cursor_row] + cursor_col);
}

void __fastcall__ gotoy (unsigned char y)
{
    cursor_row = (y < LCD_ROWS) ? y : 0;
    lcd_control (LCD_CTRL_SET_ADDR_BIT | line_starts[cursor_row] + cursor_col);
}

void __fastcall__ gotoxy (unsigned char x, unsigned char y)
{
    cursor_row = (y < LCD_ROWS) ? y : 0;
    gotox(x);
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

static void _newline_finish(void)
{
    char i;
    char* row;

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

static void newline_wrap (void)
{
    ++cursor_row;
    if (cursor_row >= LCD_ROWS)
    {
        cursor_row=0;
    }

    _newline_finish();
}

static void newline_drop (void)
{
    ++cursor_row;
    if (cursor_row >= LCD_ROWS)
    {
        cursor_row=(LCD_ROWS-1);
    }

    _newline_finish();
}

void newline_scrollup (void)
{
    ++cursor_row;
    if (cursor_row >= LCD_ROWS)
    {
        unsigned char x;
        unsigned char y;
        const uint8_t working_rows=(LCD_ROWS-1);
        memmove(&display_ram[0][0], &display_ram[1][0], working_rows * (uint8_t)DISPLAY_RAM_COLS);
        for( y=0; y<cursor_row; ++y)
        {
            // Move cursor to xy(0,i)
            lcd_control (LCD_CTRL_SET_ADDR_BIT | line_starts[y]);
            for( x=0; x<LCD_COLS; ++x)
            {
                lcd_output(display_ram[y][x]);
            }
        }
        cursor_row = working_rows;
    }

    _newline_finish();
}

void __fastcall__ cputc (char c)
{
    // CC65 conio workaround
    // conio assumes that ptr1 and tmp1 are preserved
    // but the CC65 compiler may use them
    // so push them on to the local variable stack
    char* preservePtr1=__PTR1__;
    unsigned int preserveTmp1=__TMP1__;

    switch(c)
    {
        case '\b':
            gotox(cursor_col-1);
            lcd_output(' ');
            lcd_control (LCD_CTRL_SET_ADDR_BIT | line_starts[cursor_row]+cursor_col);
            break;

        case '\f':
            clrscr();
            break;

        case '\n':
            newline_handler();
            break;

        case '\r':
            cursor_col = 0;
            lcd_control (LCD_CTRL_SET_ADDR_BIT | line_starts[cursor_row]);
            break;

        default:
            if(cursor_col<LCD_COLS)
            {
                lcd_output(c);
                display_ram[cursor_row][cursor_col]=c;
                ++cursor_col;
            }
    }

    // Restore zp registers from local variable stack.
    __PTR1__ = preservePtr1;
    __TMP1__ = preserveTmp1;
}

char cgetc (void)
{
    char c;
    if (__CURSOR__)
    {
        lcd_control(LCD_CTRL_DISPON_CURSON);
    }
    c=KBINPUT();
    lcd_control(LCD_CTRL_DISPON_CURSOFF);
    return c;
}

unsigned char __fastcall__ console_echo (unsigned char onoff)
{
    unsigned char returnVal = echo;
    if( onoff )
    {
        echo = true;
    }
    else
    {
        echo = false;
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
            if(echo)
            {
                cputc(*buf);
            }
            --size;
            ++buf;
            *buf = cgetc();
        }
        if(echo)
        {
            cputc('\r');
            cputc('\n');
        }
        *buf = '\0';
    }
    return retVal;
}

void console_newline ( unsigned mode )
{
    switch(mode)
    {
        case 1:
            newline_handler = newline_wrap;

        case 2:
            newline_handler = newline_drop;

        default:
            newline_handler = newline_scrollup;
    }
}
