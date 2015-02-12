;;===============================
;;Name: Jesse Chen
;;===============================

.orig x3000

LOOP    LD R0, A        ;Load A into R0
        LD R1, B        ;Load B into R1
        LD R2, ANSWER   ;Load ANSWER into R2
        NOT R1, R1      ;B = !B begin 2's complement
        ADD R1, R1, 1   ;B++ finish 2's complement
        ADD R0, R0, R1  ;Check A > B
        BRnz LOOP       ;Loop back to beginning
	
A       .fill 25
B       .fill 5
ANSWER  .fill 0
.end
