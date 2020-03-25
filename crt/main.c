// PORTB
static volatile char * const VIO0_IO  = (volatile char *)0x6000;
// PORTA
static volatile char * const VIO1_IO  = (volatile char *)0x6001;
// DDRB
static volatile char * const VIO0_CFG = (volatile char *)0x6002;
// DDRA
static volatile char * const VIO1_CFG = (volatile char *)0x6003;

#define LCD_SIG_E  0x80
#define LCD_SIG_RW 0x40
#define LCD_SIG_RS 0x20

void lcd_control(char a)
{
    // Set Control lines
    *VIO0_IO = a;

    // Toggle Enable bits
    *VIO1_IO=0;
    *VIO1_IO=(0|LCD_SIG_E);
    *VIO1_IO=0;
}

void lcd_output(char a)
{
    // Set Control lines
    *VIO0_IO = a;

    // Toggle Enable bits
    *VIO1_IO=LCD_SIG_RS;
    *VIO1_IO=(LCD_SIG_RS|LCD_SIG_E);
    *VIO1_IO=LCD_SIG_RS;
}

void lcd_output_str( const char* str )
{
    while(*str)
    {
        lcd_output(*str++);
    }
}

int main( )
{
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

    // Clear Display
    // 0000 0001          Set display mode to auto incremetn to the right
    lcd_control(0x01);

    lcd_output_str("Have a nice day!!!");

    return 0;
}

