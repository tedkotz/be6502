/**
 * @file    pckybd.h
 * @author  Ted Kotz <ted@kotz.us>
 * @version 0.1
 *
 * [Description]
 *
 */
#ifndef   PCKYBD_H
#define   PCKYBD_H
/* Includes ******************************************************************/
/* Defines *******************************************************************/
/* Types *********************************************************************/
/* Interfaces ****************************************************************/
/* Data **********************************************************************/
/* Functions *****************************************************************/

/**
 * Initialize the keyboard and associated variables and set the LEDs
 *
 */
extern void KBINIT(void);

/**
 * Wait for a key press and return with its assigned ASCII code in A.
 *
 * @return ASCII code corresponding to key press
 */
extern char __fastcall__ KBINPUT(void);

/**
 * Wait for a key press and return with its unprocessed scancode in A.
 *
 * @return raw scancode of pressed key
 */
extern char __fastcall__ KBGET(void);

/**
 * Scan the keyboard for 105uS, returns 0 in A if no key pressed.
 * Return ambiguous data in A if key is pressed.  Use KBINPUT OR KBGET
 * to get the key information.  You can modify the code to automatically
 * jump to either routine if your application needs it.
 *
 * @return 0, if no key pressed
 */
extern char __fastcall__ KBSCAN(void);


#endif // PCKYBD_H
