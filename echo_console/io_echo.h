/**
 * @file    io_echo.h
 * @author  Ted Kotz <ted@kotz.us>
 * @version 0.1
 *
 * IO functions to support console IO. Target API should be posix, curses
 * or conio.h as spelled out in the cc65 functional reference.
 * https://cc65.github.io/doc/funcref.html
 *
 * time.h, conio.h, read, write, sleep, usleep, nanosleep
 * mutliple display size support
 *
 */
#ifndef   IO_ECHO_H
#define   IO_ECHO_H

/* Includes ******************************************************************/
/* Defines *******************************************************************/
#define LCD_ROWS 4
#define LCD_COLS 20

/* Types *********************************************************************/
/* Interfaces ****************************************************************/
/* Data **********************************************************************/
/* Functions *****************************************************************/
/**
 * [Description]
 *
 * @param
 * @return
 */
extern void disable_ints(void);

/**
 * [Description]
 *
 * @param
 * @return
 */
extern void enable_ints(void);

/**
 * [Description]
 *
 * @param
 * @return
 */
extern void console_reset(void);

extern void clear_display(void);



#endif // IO_ECHO_H
