PORTB = $6000
PORTA = $6001
DDRB  = $6002
DDRA  = $6003
E     = %10000000
RW    = %01000000
RS    = %00100000

        .export reset

reset:
        ldx #$ff                ; Reset Stack Pointer
        txs

        ;lda #$ff
        ;sta DDRB                ; Set All Control pins to outputs
        stx DDRB                ; Set All Control pins to outputs

        lda #$E0
        sta DDRA                ; Set 3 high pins to outputs

        ; SET MODE
        lda #%00111000          ; Set 8-bit, 2-line, 5x8 font mode
        jsr LCD_CONTROL_A

        ; DISPLAY ON
        lda #%00001110          ; Display on, Cursor on, Blink Off
        jsr LCD_CONTROL_A

        ; Increment mode
        lda #%00000110          ; Set display mode to auto incremetn to the right
        jsr LCD_CONTROL_A

        ; Clear Display
        lda #%00000001          ; Set display mode to auto incremetn to the right
        jsr LCD_CONTROL_A

        ; Print character
        lda #'H'
        jsr LCD_OUTPUT_A

        ; Print character
        lda #'e'
        jsr LCD_OUTPUT_A

        ; Print character
        lda #'l'
        jsr LCD_OUTPUT_A

        ; Print character
        lda #'l'
        jsr LCD_OUTPUT_A

        ; Print character
        lda #'o'
        jsr LCD_OUTPUT_A

        ; Print character
        lda #','
        jsr LCD_OUTPUT_A

        ; Print character
        lda #' '
        jsr LCD_OUTPUT_A

        ; Print character
        lda #'W'
        jsr LCD_OUTPUT_A

        ; Print character
        lda #'o'
        jsr LCD_OUTPUT_A

        ; Print character
        lda #'r'
        jsr LCD_OUTPUT_A

        ; Print character
        lda #'l'
        jsr LCD_OUTPUT_A

        ; Print character
        lda #'d'
        jsr LCD_OUTPUT_A

        ; Print character
        lda #'!'
        jsr LCD_OUTPUT_A

END:
        jmp END
        ;brk


LCD_OUTPUT_A:
        sta PORTB

        lda #RS                 ; Clear LCD control bits And Toggle Enable bit
        sta PORTA               ; Keep RS set to select output register (vs control)
        lda #(E|RS)
        sta PORTA
        lda #RS
        sta PORTA
        rts


LCD_CONTROL_A:
        sta PORTB

        lda #0                  ; Clear LCD control bits And Toggle Enable bit
        sta PORTA               ; Keep RS clear to select control register (vs ouput)
        lda #E
        sta PORTA
        lda #0
        sta PORTA
        rts


