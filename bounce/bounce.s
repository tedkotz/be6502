        .export reset

reset:
        lda #$ff
        sta $6002               ; Set All Control pins to outputs
Reset_Loop:
        clc
        lda #$01
Left_Loop:
        sta $6000              ; Start with 1 and a cleared carry bit
        rol
        bcc Left_Loop
        clc
        lda #$80
Right_Loop:
        sta $6000
        ror
        bcc Right_Loop
        jmp Reset_Loop


