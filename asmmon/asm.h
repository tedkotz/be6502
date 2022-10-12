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
    RegMode_Immediate,
    RegMode_Accum,
    RegMode_PcRelative,
    RegMode_PcRelativeLong,
    RegMode_Implied,
    RegMode_Stack,
    RegMode_Direct,
    RegMode_DirectIndexX,
    RegMode_DirectIndexY,
    RegMode_DirectIndirect,
    RegMode_DirectIndexXIndirect,
    RegMode_DirectIndirectIndexY,
    RegMode_DirectIndirectLong,
    RegMode_DirectIndirectLongIndexY,
    RegMode_Absolute,
    RegMode_AbsoluteIndexX,
    RegMode_AbsoluteIndexY,
    RegMode_AbsoluteLong,
    RegMode_AbsoluteLongIndexX,
    RegMode_StackRelative,
    RegMode_StackRelativeIndirectIndexY,
    RegMode_AbsoluteIndirect,
    RegMode_AbsoluteIndexXIndirect,
    RegMode_BlockMove,
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
