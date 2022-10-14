/**
 * @file    asm.h
 * @author  Ted Kotz <ted@kotz.us>
 * @version 0.1
 *
 * [Description]
 *
 */
#ifndef   ASM_H
#define   ASM_H

/* Includes ******************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/* Defines *******************************************************************/

/* Types *********************************************************************/
typedef enum RegisterMode
{
    RegMode_Immediate,                                 // 2
    RegMode_Accum,                                     // 1
    RegMode_PcRelative,                                // 2
    RegMode_PcRelativeLong,                            // 3
    RegMode_Implied,                                   // 1
    RegMode_Stack,                                     // 1
    RegMode_Direct,                                    // 2
    RegMode_DirectIndexX,                              // 2
    RegMode_DirectIndexY,                              // 2
    RegMode_DirectIndirect,                            // 2
    RegMode_DirectIndexXIndirect,                      // 2
    RegMode_DirectIndirectIndexY,                      // 2
    RegMode_DirectIndirectLong,                        // 2
    RegMode_DirectIndirectLongIndexY,                  // 2
    RegMode_Absolute,                                  // 3
    RegMode_AbsoluteIndexX,                            // 3
    RegMode_AbsoluteIndexY,                            // 3
    RegMode_AbsoluteLong,                              // 4
    RegMode_AbsoluteLongIndexX,                        // 4
    RegMode_StackRelative,                             // 2
    RegMode_StackRelativeIndirectIndexY,               // 2
    RegMode_AbsoluteIndirect,                          // 3
    RegMode_AbsoluteIndexXIndirect,                    // 4
    RegMode_BlockMove,                                 // 3
    RegMode_StackInterrupt,                            // 2?
    RegMode_WDM,                                       // 2?
} RegisterMode;

typedef struct AsmInst
{
    char mnemonic[7];
    byte registerMode;
} AsmInst;

/* Interfaces ****************************************************************/

/* Data **********************************************************************/
const AsmInst AsmInstLibrary[256];


/* Functions *****************************************************************/

/**
 * [Description]
 *
 * @param
 * @return
 */


#ifdef  __cplusplus
}
#endif

#endif // ASM_H
