    .ORIG x0200
    .FILL x0000 ; Vector x00 (don't use)
    .FILL x1200 ; Vector x01 (Interrupt)
    .FILL x1400 ; Vector x02 (Page Fault)
    .FILL x1A00 ; Vector x03 (Unaligned)
    .FILL x1600 ; Vector x04 (Protection)
    .FILL x1C00 ; Vector x05 (Unknown)
    .END