    .ORIG x0200
    .FILL x0000 ; Vector x00 (don't use)
    .FILL x1200 ; Vector x01 (Interrupt)
    .FILL x1600 ; Vector x02 (Protection)
    .FILL x1A00 ; Vector x03 (Unaligned)
    .FILL x1C00 ; Vector x04 (Unknown)
    .END