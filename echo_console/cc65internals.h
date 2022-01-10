/**
 * @file    cc65internals.h
 * @author  Ted Kotz <ted@kotz.us>
 * @version 0.1
 *
 * [Description]
 *
 */
#ifndef   CC65INTERNALS_H
#define   CC65INTERNALS_H

/* Includes ******************************************************************/
/* Defines *******************************************************************/
/* Types *********************************************************************/
/* Interfaces ****************************************************************/
/* Data **********************************************************************/
//	.importzp	sp, sreg, regsave, regbank
//	.importzp	tmp1, tmp2, tmp3, tmp4, ptr1, ptr2, ptr3, ptr4

extern unsigned int __SREG__;
extern unsigned int __TMP1__;
extern unsigned int __TMP2__;
extern unsigned int __TMP3__;
extern unsigned int __TMP4__;
extern unsigned int __REGSAVE__;
extern unsigned int __REGBANK__;
#pragma zpsym("__SREG__");
#pragma zpsym("__TMP1__");
#pragma zpsym("__TMP2__");
#pragma zpsym("__TMP3__");
#pragma zpsym("__TMP4__");
#pragma zpsym("__REGSAVE__");
#pragma zpsym("__REGBANK__");

extern unsigned char* __SP__;
extern unsigned char* __PTR1__;
extern unsigned char* __PTR2__;
extern unsigned char* __PTR3__;
extern unsigned char* __PTR4__;
#pragma zpsym("__SP__");
#pragma zpsym("__PTR1__");
#pragma zpsym("__PTR2__");
#pragma zpsym("__PTR3__");
#pragma zpsym("__PTR4__");



/* Functions *****************************************************************/

// initlib
// tosadda0
// addeqysp
// axlong
// donelib
// ctypemaskdirect
// decsp3
// decsp6
// incsp1
// incsp2
// incsp4
// incsp6
// ldax0sp
// leaa0sp
// pusheax
// popptr1
// pusha
// pusha0
// pushwysp
// staspidx
// subysp
// zerobss
// gotoxy
// addeq0sp
// addysp
// axulong
// copydata
// decsp1
// decsp4
// incaxy
// popax
// incsp3
// incsp5
// incsp8
// ldaxysp
// negeax
// tosmula0
// push1
// push0
// pushax
// shrax1
// staxysp

#endif // CC65INTERNALS_H
