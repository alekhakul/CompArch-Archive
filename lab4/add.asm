    .ORIG x3000
    LEA R0, PTR4000
    LDW R0, R0, #0
    AND R1, R1, #0      
    ADD R1, R1, #1      ; R1 = 1
    STW R1, R0, #0      ; Mem[x4000] = 1 (Init)
    LEA R2, PTRC000
    LDW R2, R2, #0      ; R2 = xC000 (data pointer)
    AND R3, R3, #0      ; R3 = 0 (sum)
    AND R4, R4, #0
    ADD R4, R4, #15     ; Add 15 (only 5 imm bits -1 for signed)
    ADD R4, R4, #5      ; Add 5 for 20 for loop counter
SUM_LOOP LDB R5, R2, #0      ; Load byte
    ADD R3, R3, R5      ; Add to sum
    ADD R2, R2, #1      ; Increment pointer
    ADD R4, R4, #-1     ; Decrement counter
    BRP SUM_LOOP        ; If counter not 0, loop
    LEA R6, PTRC014
    LDW R6, R6, #0      ; R6 = xC014
    STW R3, R6, #0      ; Mem[xC014] = Sum
    AND R0, R0, #0      ; R0 = x0000
    STW R3, R0, #0      ; Triggers protection exc
    HALT                ; Exc should trigger before this
    
PTR4000 .FILL x4000
PTRC000 .FILL xC000
PTRC014 .FILL xC014

    .END