;;===============================
;;Name: Jesse Chen
;;===============================

.orig x3000

		LD R6, ARRAY		;Load ARRAY (x6000) starting index into R6
		ADD R6, R6, -1 		;Start at x5FFF
		LD R0, K			;Initialize LOOP1 index K in R0
		LD R1, LENGTH		;Load LENGTH (for-loop condition) into R1
		NOT R1, R1			;Two's complement
		ADD R1, R1, 1 		;-LENGTH

LOOP1	ST R0, K			;Store R0 in K
		ADD R0, R0, R1		;K - LENGTH
		BRzp BREAK1			;If K < LENGTH -> BREAK1

		AND R2, R2, 0		;Initialize/reset isSorted
		ADD R2, R2, 1 		;isSorted = 1

		LD R0, K			;Undo two's complement on K
		LD R3, I 			;Initialize LOOP2 index I in R3

LOOP2	ST R3, I
		ADD R3, R3, R1		;I - LENGTH
		ADD R3, R3, R0		;I - LENGTH + K
		BRzp ELSE			;If I < LENGTH - K -> ELSE
		
		LDR R4, R6, 1		;Load data from ARRAY[I] into R4
		LDR R5, R6, -1 		;Load data from ARRAY[I - 1] into R5
		NOT R5, R5			;Two's complement
		ADD R5, R5, 1 		;-ARRAY[I - 1]

ELSE	ADD R0, R0, 1 		;Increment K
		ADD R6, R6, 1 		;Increment array index

		BR LOOP1			;Repeat loop

BREAK1 	;ST R5, ANSWER		;Store R5 in ANSWER

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

