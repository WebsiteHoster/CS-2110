; Name: Jesse Chen
;RUN FOR 133. DOING EVAL FOR FIRST RIGHT

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
STRING	.stringz "1+2+3"	;Originally "1*2+3*4+5"
		.blkw 200

EVAL 	;ADD R6, R6, -1	  	;Leave space for return value
        ;ADD R6, R6, -1	  	;Allocate space for return address
        ;STR R7, R6, 0	  	;Store return address on stack
        ;ADD R6, R6, -1  	;Leave space for old frame pointer
        ;STR R5, R6, 0   	;Save old frame pointer
        ;ADD R6, R6, -1  	;Make room for result
        ;ADD R5, R6, 0   	;Copy SP to FP
        ;ADD R6, R6, -2  	;Allocate space for saved registers
        ;STR R0, R6, 0   	;Save R0
        ;STR R1, R6, 1   	;Save R1

        ;Pre-subroutine stack management
        STR R1, R6, 1 		;Save len
        STR R0, R6, 0		;Save *str
        ;Return value goes in (R6 - 1)
        ;Index i goes in (R6 - 2)
        STR R7, R6, -3 		;Save return address
        STR R6, R6, -4		;Save FP

        ;subroutine here. STORE RESULT IN R5
        AND R2, R2, 0		;R2 = i = 0

        ;PLUS loop condition
PLUS	;ADD R6, R6, -5		;Push - shift FP up
		STR R2, R6, -2 		;Store current index i in (R6 - 2)
		LDR R3, R6, 1		;Get limit len
		NOT R3, R3			;Two's complement
		ADD R3, R3, 1
		ADD R2, R2, R3		;i - len
		BRzp BREAK1			;Done looping when (I - len) >= 0

			;PLUS loop body
			LDR R2, R6, -2		;R2 = i
			LDR R0, R6, 0		;R0 = &str[0]
			LDR R3, R6, 1 		;R3 = len

			;PLUS if condition
			ADD R1, R0, R2		;R1 = str + i
			LDR R1, R1, 0		;R1 = *(str + i)
			ADD R1, R1, -16		;char - 43 (ASCII value for '+')
			ADD R1, R1, -16
			ADD R1, R1, -11
			BRnp SKIP1			;Skip if when current char =/= '+'

				;PLUS if body
				ADD R6, R6, -6		; \ Shift FP for left = eval(str, len)
				LDR R1, R6, 4		; | Reload old i
				STR R1, R6, 1 		; | Save new len = i
				STR R0, R6, 0		; | Save new *str
				JSR EVAL			; | Recursion
				LDR R2, R6, -7		; / R2 = left

				ADD R6, R6, -6		; \ Shift FP for right = eval(str + 					  |			i + 1, len - i - 1)
				LDR R0, R6, 6		; | Reload old *str
				LDR R1, R6, 4		; | Reload old i
				ADD R0, R0, R1 		; | R0 = str + i
				ADD R0, R0, 1 		; | R0 = str + i + 1
				STR R0, R6, 0		; | Save new *str = str + i + 1
									; |
				LDR R3, R6, 7		; | Reload old len
				NOT R1, R1			; | Two's complement i
				ADD R1, R1, 1 		; |
				ADD R3, R3, R1 		; | R3 = len - i
				ADD R3, R3, -1 		; | R3 = len - i - 1
				STR R3, R6, 1		; | Save new len = len - i -1
				JSR EVAL			; |
				LDR R3, R6, -7		; / R3 = right

				ADD R1, R2, R3		;R1 = left + right
				STR R1, R6, -1 		;Store result R1 in stack
				RET

SKIP1		LDR R2, R6, -2		;Load current I
			ADD R2, R2, 1 		;Increment I
			STR R2, R6, -2 		;Save incremented I
			BR PLUS				;Loop PLUS

BREAK1  ;Reset I and do MULT loop

		LDR R0, R6, 0		;R0 = &str[0]
		LDR R0, R0, 0		;R0 = *str
		ADD R0, R0, -16		;*str - '0'
		ADD R0, R0, -16
		ADD R0, R0, -16
		STR R0, R6, -1 		;Store/return char's numerical value in stack

        ;Post-subroutine stack management
BREAK2  LDR R1, R6, 1 		;Reload len
        LDR R0, R6, 0		;Reload *str
        ;STR R5, R6, -1  	;Save subroutine result in R5
        LDR R2, R6, -2 		;Reload index i
        LDR R7, R6, -3 		;Reload return address
        ADD R6, R6, 6 		;Pop - shift FP down

        RET

.end
