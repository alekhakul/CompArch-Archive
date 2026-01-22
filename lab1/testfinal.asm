.ORIG x3000

; ALU
ADD R1, R2, R3      ; Reg ADD
ADD R1, R2, #-16    ; Immediate ADD (min val -16)
AND R2, R2, x0      ; Immediate AND (using 0)
XOR R3, R4, #-1     ; Immediate XOR
NOT R4, R5          

; Load/Store
LDB R1, R2, #-32    ; Min offset
STB R1, R2, #31     ; Max offset
LDW R1, R2, #0      ; Zero offset
STW R1, R2, #-1     ; Negative offset

; Branch/Jump
BRnzp TARG        ; Unconditional
NOP                 
BRz TARG          ; Conditional
JMP R3              ; Reg Jump
RET                 
JSR TARG          ; Subroutine call (Label)
JSRR R4             ; Subroutine call (Reg)

; Shift
LSHF R1, R2, #15    ; Max shift
RSHFL R1, R2, #4    
RSHFA R1, R2, #5    

; LEA
LEA R0, DATA        ; Load address of DATA

; Traps
TRAP x20            
HALT                

; FILL
TARG  ADD R0, R0, #0
DATA    .FILL xFFFF
        .FILL #-10

.END
