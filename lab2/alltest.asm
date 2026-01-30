.ORIG x3000

;Tests all opcodes
LEA R0, DATA        ; Load address of DATA into R0
ADD R1, R1, #10     ; R1 <- 10
ADD R2, R1, R1      ; R2 <- 20
AND R3, R1, #7      ; R3 <- 10 AND 7 (2)
XOR R4, R3, #-1     ; R4 <- NOT(2) (xFFFD)

; Shift operations
LSHF R5, R3, #2     ; R5 <- 2 << 2 (8)
ADD R6, R4, #0      ; Move R4 to R6
RSHFL R6, R6, #1    ; Logical Shift Right (x7FFE)
RSHFA R4, R4, #1    ; Arithmetic Shift Right (xFFFE)

; Word memory access
STW R2, R0, #0      ; Store 20 at DATA[0]
LDW R7, R0, #0      ; Load DATA[0] into R7 (Result: 20)

; Byte memory access
ADD R2, R2, #0      ; Clear R2 (for clarity)
ADD R2, R2, #-1     ; R2 <- xFFFF
STB R2, R0, #1      ; Store xFF at DATA byte offset 1
LDB R2, R0, #1      ; Load byte back (Result: xFFFF)

; Control flow
BRnzp SKIP          ; Unconditional branch
ADD R1, R1, #1      ; Should be skipped
SKIP JSR SUB             ; Call subroutine

HALT

; Subroutine
SUB ADD R1, R1, #5      ; R1 <- R1 + 5
RET

DATA .FILL x0000
.END