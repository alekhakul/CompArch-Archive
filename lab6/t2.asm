.ORIG x3000
    JSR SUBROUTINE      ; Jumps to SUBROUTINE
    ADD R1, R0, #1      ; Skipped initially
    ADD R3, R7, #0      ; Copies R7 into R3
    HALT                ; Trap x25
    
SUBROUTINE ADD R2, R0, #5      ; R2 = 5
    RET                 ; Jumps to R7
    .END