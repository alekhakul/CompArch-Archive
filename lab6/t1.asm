.ORIG x3000
    ADD R1, R0, #1    ; R1 = 1
    ADD R1, R1, #1    ; R1 = 2 (stalls to wait)
    ADD R1, R1, #1    ; R1 = 3 (stalls to wait)
    ADD R2, R1, R1    ; R2 = 6 (stalls to wait)
    HALT
    .END