; ---------------------------------------------------------------------------
; crt0.s
; ---------------------------------------------------------------------------
;
; Startup code for cc65 (Single Board Computer version)

.export   _init, _exit, _disable_ints, _enable_ints, gotoxy
.import   _main, _KBINIT, _failLockUp, _console_reset, _clrscr, _cputs, _gotoxy

.export   __STARTUP__ : absolute = 1        ; Mark as startup
.import   __RAM_START__, __RAM_SIZE__       ; Linker generated

.import    copydata, zerobss, initlib, donelib

.include  "zeropage.inc"


; Needed by conio cputs implementation which assumes asm version of gotoxy.
gotoxy = _gotoxy

; ---------------------------------------------------------------------------
; Place the startup code in a special segment
.segment	"RODATA"
kbdMessage:        .asciiz "Keyboard wait..."


.segment  "STARTUP"


_disable_ints:
          SEI                    ;
          RTS                    ;

_enable_ints:
          CLI                    ;
          RTS                    ;


; ---------------------------------------------------------------------------
; A little light 6502 housekeeping

_init:    LDX     #$FF                 ; Initialize stack pointer to $01FF
          TXS
          CLD                          ; Clear decimal mode
;        lda #$E0
;        sta $6003                ; Set 3 high pins to outputs
;        sta $6001

; ---------------------------------------------------------------------------
; Set cc65 argument stack pointer

          LDA     #<(__RAM_START__ + __RAM_SIZE__)
          STA     sp
          LDA     #>(__RAM_START__ + __RAM_SIZE__)
          STA     sp+1

; ---------------------------------------------------------------------------
; Initialize memory storage
          JSR     zerobss              ; Clear BSS segment
          JSR     copydata             ; Initialize DATA segment
          JSR     initlib              ; Run constructors

          JSR     _console_reset
          LDA     #<kbdMessage
          LDX     #>kbdMessage
          JSR     _cputs
          JSR     _KBINIT
          JSR     _clrscr
          JSR     _enable_ints
; ---------------------------------------------------------------------------
; Call main()

          JSR     _main

; ---------------------------------------------------------------------------
; Back from main (this is also the _exit entry):  force a software break

_exit:    CMP     #$00
          BNE     fail
          CPX     #$00
          BNE     fail

;          jmp _exit
          JSR     donelib              ; Run destructors
;          stp
          BRK
          .byte   00                   ; optional signature byte for BRK instruction

fail:     JSR     _failLockUp          ; X:A still contains return code
          BRK
          .byte   00                   ; optional signature byte for BRK instruction
