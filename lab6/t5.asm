.ORIG x3000
    LEA R0, DATA
    ADD R0, R0, #1
    
    LDB R1, R0, #-1
    LDB R2, R0, #0
    HALT

DATA .FILL x5544
    .END

;Registers:
;0: 0x300b
;1: 0x0044
;2: 0x0055
;3: 0x0000
;4: 0x0000
;5: 0x0000
;6: 0x0000
;7: 0x300a