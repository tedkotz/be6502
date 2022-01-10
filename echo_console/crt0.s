; ---------------------------------------------------------------------------
; crt0.s
; ---------------------------------------------------------------------------
;
; Startup code for cc65 (Single Board Computer version)

.export   _init, _exit, _disable_ints, _enable_ints
.import   _main, _KBINIT, _failLockUp

.export   __STARTUP__ : absolute = 1        ; Mark as startup
.import   __RAM_START__, __RAM_SIZE__       ; Linker generated

.import    copydata, zerobss, initlib, donelib

.include  "zeropage.inc"

; ---------------------------------------------------------------------------
; Place the startup code in a special segment

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

          JSR     _KBINIT
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
fail:     JSR     _failLockUp          ; X:A still contains return code
          BRK
