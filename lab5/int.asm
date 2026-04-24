    .ORIG x1200
    ADD R6, R6, #-2 ; PUSH
    STW R0, R6, #0
    ADD R6, R6, #-2
    STW R1, R6, #0
    ADD R6, R6, #-2
    STW R2, R6, #0
    ADD R6, R6, #-2
    STW R3, R6, #0

    LEA R0, PTBR
    LDW R0, R0, #0
    LEA R1, PT_SIZE
    LDW R1, R1, #0
    AND R2, R2, #0
    ADD R2, R2, #-2 ; Bitmask to clear bit 0

LOOP LDW R3, R0, #0 ; Load PTE
    AND R3, R3, R2 ; Clear ref bit
    STW R3, R0, #0 ; Store modified PTE back to memory
    ADD R0, R0, #2 ; Increment PTE pointer
    ADD R1, R1, #-1 ; Decrement counter
    BRP LOOP

    LDW R3, R6, #0 ; Pop
    ADD R6, R6, #2
    LDW R2, R6, #0
    ADD R6, R6, #2
    LDW R1, R6, #0
    ADD R6, R6, #2
    LDW R0, R6, #0
    ADD R6, R6, #2
    ;.FILL xA000   ; Nested Exception in Interrupt
    RTI ; Return

    ; Data
PTBR .FILL x1000
PT_SIZE .FILL #128
    .END
