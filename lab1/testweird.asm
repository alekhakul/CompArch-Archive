.ORIG x3000
    LEA R0, OhkYo       ; Load address of NUM into R0
    LDW R2, R0, #0    ; Load value at R0 into R2
    JSR ALEX
    HALT

ALEX LSHF R2, R2, #1
    rshfl R2, R2, #2
    RSHFA R2, R2, #1
    RET

OhkYo .FILL x8000
.END