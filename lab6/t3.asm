.ORIG x3000
    LEA R0, DATA
    LDB R1, R0, #0
    LDB R2, R0, #1
    LEA R3, DEST
    STB R1, R3, #1
    STB R2, R3, #0
    LDW R4, R3, #0
    HALT

DATA .FILL x8A9B
DEST  .FILL x0000
    .END