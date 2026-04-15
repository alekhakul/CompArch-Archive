.ORIG x3000
    LEA R0, DATA
    LDB R1, R0, #0
    LDB R2, R0, #1
    ADD R3, R1, #1
    ADD R4, R2, #1
    HALT
DATA .FILL #-1
    .END