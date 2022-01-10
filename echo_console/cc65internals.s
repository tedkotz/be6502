; ---------------------------------------------------------------------------
; cc65internals.s
; ---------------------------------------------------------------------------
;
; Make some assembly symbols C accessible.
;


.import cursor
.export ___CURSOR__

.importzp	sp, sreg, regsave, regbank
.importzp	tmp1, tmp2, tmp3, tmp4, ptr1, ptr2, ptr3, ptr4


.exportzp ___SP__, ___PTR1__, ___PTR3__, ___PTR3__, ___PTR4__
.exportzp ___SREG__, ___REGSAVE__, ___REGBANK__
.exportzp ___TMP1__, ___TMP3__, ___TMP3__, ___TMP4__

.segment  "CODE"

___PTR1__ = ptr1
___PTR2__ = ptr2
___PTR3__ = ptr3
___PTR4__ = ptr4
___SP__ = sp

___TMP1__ = tmp1
___TMP2__ = tmp2
___TMP3__ = tmp3
___TMP4__ = tmp4

___SREG__ = sreg
___REGSAVE__ = regsave
___REGBANK__ = regbank

___CURSOR__ = cursor

