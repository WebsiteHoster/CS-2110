.orig x3000
        LD R0, A
        LD R1, B
        ADD R2, R1, R0
        NOT R2, R2
        ADD R2, R0, R2
        ADD R2, R2, 1
        HALT

        A .fill 45
        B .fill 60
.end