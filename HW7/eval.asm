; Name: Jesse Chen


; Main
; Do not edit this function!

.orig x3000

		LD R6, STACK		; Initialize the stack

		LEA R0, STRING		; R0 = &str[0]
		ADD R1, R0, 0

SL_LOOP	LDR R2, R1, 0		; \ R1 = strlen(str)
		BRz SL_END			; |
		ADD R1, R1, 1		; |
		BR SL_LOOP			; |
SL_END	NOT R2, R0			; |
		ADD R2, R2, 1		; |
		ADD R1, R1, R2		; /

		ADD R6, R6, -2		; \ R0 = eval(str, len)
		STR R0, R6, 0		; |
		STR R1, R6, 1		; |
		LD R2, EVALPTR		; |
		JSRR R2				; |
		LDR R0, R6, 0		; |
		ADD R6, R6, 3		; /

		ST R0, ANS
		HALT

STACK	.fill xf000
ANS		.fill -1
EVALPTR	.fill EVAL
STRING	.stringz "1*2+3*4+5"
		.blkw 200

EVAL 	ADD R6, R6, -1	  	;Leave space for return value
        ADD R6, R6, -1	  	;Allocate space for return address
        STR R7, R6, 0	  	;Store return address on stack
        ADD R6, R6, -1  	;Leave space for old frame pointer
        STR R5, R6, 0   	;Save old frame pointer
        ADD R6, R6, -1  	;Make room for result
        ADD R5, R6, 0   	;Copy SP to FP
        ADD R6, R6, -2  	;Allocate space for saved registers
        STR R0, R6, 0   	;Save R0
        STR R1, R6, 1   	;Save R1

        LD R2, I 			;R2 = I = 0
        					;R3 = left = eval(str, i)
        					;R4 = right = eval(str + i + 1, len - i - 1)
PLUS    ST R2, I 			;Store current I
		LDR R5, R5, 5		;Get limit (I < len)
		NOT R5, R5			;Two's complement
		ADD R5, R5, 1
		ADD R2, R2, R5		;I - len
		BRzp BREAK1			;Done looping when (I - len) >= 0

		;PLUS loop body
		LDR R2, R0, 0		;Load first character
		ADD R2, R2, -43		;char - 43 (ASCII value for +)
		BRnp CONT1

		;PLUS if body
		

CONT1	LD R2, I 			;Load current I
		ADD R2, R2, 1 		;Increment I
		BR PLUS				;Loop PLUS

BREAK1  ;stuff after PLUS

        JSR EVAL       		;Recursion

        LDR R0, R6, 0   	;Put recursion result in R0
        LDR R1, R5, 4   	;Get x
        ADD R0, R0, r1  	;This is the result!!
        STR R0, R5, 0   	;Store answer in z

DONE    LDR R0, R5, 0   	;Get z
        STR R0, R5, 3   	;Put in return value location

        LDR R0, R5, -2  	;Restore R0
        LDR R1, R5, -1  	;Restore R1
        LDR R7, R5, 2   	;Restore return address
        ADD R6, R5, 1   	;Make SP point to old FP
        LDR R5, R6, 0   	;Load old FP back into R5
        ADD R6, R6, 2   	;Make SP point to return value

		RET

I 		.fill 0

.end
