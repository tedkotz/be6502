; ---------------------------------------------------------------------------
; crt0.s
; ---------------------------------------------------------------------------
;
; Startup code for cc65 (Single Board Computer version)

.export   _init, _exit
.import   _main

.export   __STARTUP__ : absolute = 1        ; Mark as startup
.import   __RAM_START__, __RAM_SIZE__       ; Linker generated

.import    copydata, zerobss, initlib, donelib

.include  "zeropage.inc"

; ---------------------------------------------------------------------------
; Place the startup code in a special segment

.segment  "STARTUP"

; ---------------------------------------------------------------------------
; A little light 6502 housekeeping

_init:    LDX     #$FF                 ; Initialize stack pointer to $01FF
          TXS
          CLD                          ; Clear decimal mode
        lda #$ff
        sta $6002               ; Set All Control pins to outputs
        clc
        lda #$01
Left_Loop:
        sta $6000              ; Start with 1 and a cleared carry bit
        rol
        bcc Left_Loop

; ---------------------------------------------------------------------------
; Set cc65 argument stack pointer

          LDA     #<(__RAM_START__ + __RAM_SIZE__)
          STA     sp
          LDA     #>(__RAM_START__ + __RAM_SIZE__)
          STA     sp+1

; ---------------------------------------------------------------------------
; Initialize memory storage

        clc
        lda #$01
Left_Loop1:
        sta $6000              ; Start with 1 and a cleared carry bit
        rol
        bcc Left_Loop1
;          JSR     zerobss              ; Clear BSS segment
;          JSR     copydata             ; Initialize DATA segment
;          JSR     initlib              ; Run constructors
        clc
        lda #$01
Left_Loop2:
        sta $6000              ; Start with 1 and a cleared carry bit
        rol
        bcc Left_Loop2

; ---------------------------------------------------------------------------
; Call main()

          JSR     _main

; ---------------------------------------------------------------------------
; Back from main (this is also the _exit entry):  force a software break

_exit:    JSR     donelib              ; Run destructors
          BRK
