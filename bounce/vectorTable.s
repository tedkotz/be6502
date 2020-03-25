        .import reset
        .segment  "VECTORS"
        .word $8000            ; NMI vector
        .addr reset            ; Reset vector
        .word $8000            ; IRQ/BRK vector

