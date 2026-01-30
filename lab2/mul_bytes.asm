        .ORIG x3000
        LEA   R5, BASE
        LDW R5, R5, #0

        LDB   R0, R5, #0      ; R0 = mem[0x3100]
        LDB   R1, R5, #1      ; R1 = mem[0x3101]

        AND   R2, R2, #0      ; result = 0
        AND   R4, R4, #0      ; overflow = 0

LOOP    ADD   R1, R1, #0      ; set condition codes from R1
        BRz   DONE            ; if multiplier == 0, exit loop

        ADD   R2, R2, R0
        ADD   R1, R1, #-1

        BRnzp LOOP            ; unconditional branch back

DONE    ADD R3, R2, #0     
        RSHFL R3, R3, #8      ; logical shift right 8 bits
        BRz   NO_OF           ; if shifted result == 0, no overflow

        ADD   R4, R4, #1      ; overflow = 1

NO_OF   STB   R2, R5, #2      ; Mem[0x3102] = low byte of result
        STB   R4, R5, #3      ; Mem[0x3103] = overflow flag

        HALT

BASE    .FILL x3100

        .END


;Register Output
;0: 0x0000
;1: 0x0000
;2: 0x0000
;3: 0x0000
;4: 0x0000
;5: 0x3100
;6: 0x0000
;7: 0x3024