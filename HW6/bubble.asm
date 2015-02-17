;;===============================
;;Name: Jesse Chen
;;===============================

.orig x3000

		LD R6, ARRAY		;Load ARRAY (x6000) starting index into R6
		ADD R6, R6, -1 		;Start at x5FFF
		AND R0, R0, 0		;Initialize LOOP1 index K in R0
		LD R1, LENGTH		;Load LENGTH (for-loop condition) into R1
		NOT R1, R1			;Two's complement
		ADD R1, R1, 1 		;-LENGTH

LOOP1	ST R0, K			;Store R0 in K
		ADD R0, R0, R1		;K - LENGTH
		BRzp BREAK			;If K < LENGTH -> break

		AND R2, R2, 0		;Initialize/reset isSorted
		ADD R2, R2, 1 		;isSorted = 1

		AND R3, R3, 0		;Initialize LOOP2 index I in R3 to 1
		ADD R3, R3, 1

LOOP2	

ELSE	LD R0, K			;Undo two's complement on K
		ADD R0, R0, 1 		;Increment K
		ADD R6, R6, 1 		;Increment array index

		BR LOOP1			;Repeat loop

BREAK 	;ST R5, ANSWER		;Store R5 in ANSWER

		HALT

K		.fill 0
I 		.fill 1

ARRAY   .fill x6000
LENGTH  .fill 12
.end

.orig x6000
.fill 28
.fill -50
.fill 7
.fill 0
.fill 216
.fill 4
.fill 15
.fill -82
.fill 34
.fill 101
.fill -5
.fill 61
.end

