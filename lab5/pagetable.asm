.ORIG x1000
    
    ; System Space 0-23
    ; Frames 0-23, V = 1, P = 0
    .FILL x0004 ; Page 0 (Frame 0)
    .FILL x0204 ; Page 1 (Frame 1)
    .FILL x0404 ; Page 2 (Frame 2)
    .FILL x0604 ; Page 3 (Frame 3)
    .FILL x0804 ; Page 4 (Frame 4)
    .FILL x0A04 ; Page 5 (Frame 5)
    .FILL x0C04 ; Page 6 (Frame 6)
    .FILL x0E04 ; Page 7 (Frame 7)
    .FILL x1004 ; Page 8 (Frame 8)
    .FILL x1204 ; Page 9 (Frame 9)
    .FILL x1404 ; Page 10 (Frame 10)
    .FILL x1604 ; Page 11 (Frame 11)
    .FILL x1804 ; Page 12 (Frame 12)
    .FILL x1A04 ; Page 13 (Frame 13)
    .FILL x1C04 ; Page 14 (Frame 14)
    .FILL x1E04 ; Page 15 (Frame 15)
    .FILL x2004 ; Page 16 (Frame 16)
    .FILL x2204 ; Page 17 (Frame 17)
    .FILL x2404 ; Page 18 (Frame 18)
    .FILL x2604 ; Page 19 (Frame 19)
    .FILL x2804 ; Page 20 (Frame 20)
    .FILL x2A04 ; Page 21 (Frame 21)
    .FILL x2C04 ; Page 22 (Frame 22)
    .FILL x2E04 ; Page 23 (Frame 23)

    ; User Space 24-127
    
    ; Page 24: Frame 25
    .FILL x320C

    ; Pages 25-95
    ; Invalid, Unprotected
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008

    ; Page 96: Frame 28
    .FILL x380C

    ; Pages 97-125: Invalid, Unprotected
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008
    .FILL x0008

    ; Page 126: Frame 29
    .FILL x3A0C

    ; Page 127: Invalid, Unprotected
    .FILL x0008

    .END