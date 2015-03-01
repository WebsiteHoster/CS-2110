;int mult(a, b) {
;    int c = 0;
;    if (b = 0)
;        c = 0;
;    else
;        c = a + mult(a, b - 1)
;    return c
;}
 
 
.orig x3000

        ld r1, a
        ld r2, b
        ld r6, stkinit
        ld r5, value
        add r6, r6, -2
        str r2, r6, 1
        str r1, r6, 0
        jsr mult
         
        halt

a       .fill 3
b       .fill 4
stkinit .fill x6000
value   .fill 666
 
mult    add r6, r6, -1  ;Leave space for Return Value
        add r6, r6, -1  ;Allocate space for Return Address
        str r7, r6, 0   ;Store return address on stack
        add r6, r6, -1  ;Leave space for old Frame Pointer
        str r5, r6, 0   ;Save Old Frame Pointer
        add r6, r6, -1  ;Make room for c
        add R5, r6, 0   ;Copy sp to fp
        add r6, r6, -2  ;Allocate space for saved registers
        str r0, r6, 0   ;Save R0
        str r1, r6, 1   ;Save R1
 
        ldr r0, r5, 5   ;Get b (and tests it)
        brn error
        brp recurse
        str r0, r5, 0   ;Store 0 in c
        br done
recurse add r6, r6, -2  ;Get ready to call mult
        add r0, r0, -1  ;Calc b - 1
        str r0, r6, 1   ;Store b - 1 on stack
        ldr r0, r5, 4   ;Get a
        str r1, r6, 0   ;Put it on stack
        jsr mult        ;Recursion!!
        ldr r0, r6, 0   ;Put recursion result in r0
        ldr r1, r5, 4   ;Get a
        add r0, r0, r1  ;This is the result!!
        str r0, r5, 0   ;Store answer in c
done    ldr r0, r5, 0   ;Get c
        str r0, r5, 3   ;Put in return value location
       
        ldr r0, r5, -2  ;Restore r0
        ldr r1, r5, -1  ;Restore r1
        ldr r7, r5, 2   ;Restore return address
        add r6, r5, 1   ;Make sp point to old fp
        ldr r5, r6, 0   ;Load old FP back into r5
        add r6, r6, 2   ;Make sp point to return value
        ret

error   halt
.end




        AND R2, R2, 0           ;R2 = 0
        ;ST R2, I                       ;I = R2 = 0
                                                ;R2 = left = eval(str, i)
                                                ;R3 = right = eval(str + i + 1, len - i - 1)
        ;PLUS loop condition
PLUS    ST R2, I                        ;Store current I
                LDR R3, R6, 1           ;Get limit (I < len)
                NOT R3, R3                      ;Two's complement
                ADD R3, R3, 1
                ADD R2, R2, R3          ;I - len
                BRzp BREAK1                     ;Done looping when (I - len) >= 0

                        ;PLUS loop body
                        LD R2, I                        ;Load I
                        LEA R0, STRING          ;R0 = &str[0] MIGHT BE PROBLEMATIC, maybe                                                                                               LDR R0, R6, 6

                        ;PLUS if condition
                        ADD R0, R0, R2          ;Load current char *(str + I)
                        LDR R2, R0, 0
                        ADD R2, R2, -16         ;char - 43 (ASCII value for '+')
                        ADD R2, R2, -16
                        ADD R2, R2, -11
                        BRnp SKIP1                      ;Skip if when current char =/= '+'      

                                ;PLUS if body
                                ;ADD R6, R6, -2         ;Get ready to call EVAL
                        ;LD R2, I                       ;Load I
                        ;STR R2, R6, 1          ;Store I on stack
                        ;LEA R0, STRING         ;R0 = &str[0]
                        ;STR R1, R6, 0          ;Put it on stack
                        ;JSR EVAL               ;Recursion
                        ADD R6, R6, -2          ; \ R2 = left = eval(str, len)
                                LD R1, I                        ; | Copy I to R1
                                LD R2, I                        ; | Load I
                                STR R2, R6, 1           ; | Store I on stack
                                NOT R2, R2                      ; | Two's complement
                                ADD R2, R2, 1           ; |
                                ADD R0, R0, R2          ; | R0 = &str[I - I] = &str[0]
                                STR R0, R6, 0           ; |
                                JSR EVAL                        ; |
                                LDR R2, R6, 2           ; | Changed from LDR R0, R6, 0
                                ADD R6, R6, 3           ; /

                                ;AND R3, R3, 0          ; \ R3 = right = eval(str + i + 1,                                                |                                             len - i - 1)
                                LDR R3, R6, 6           ; | R3 = len
                                LD R4, I                        ; | R4 = I
                                NOT R4, R4                      ; | Two's complement
                                ADD R4, R4, 1           ; |
                                ADD R3, R3, R4          ; | R3 = len - I
                                ADD R3, R3, -1          ; | R3 = len - I - 1
                                ;ADD R6, R6, -2                 ; |
                                STR R3, R6, 1           ; | Store R3 on stack
                                ADD R0, R0, R1          ; | R0 = &str[I]
                                ADD R0, R0, 1           ; | R0 = &str[I + 1]
                                STR R0, R6, 0           ; |
                                JSR EVAL                        ; |
                                LDR R3, R6, 2           ; | Changed from LDR R0, R6, 0
                                ADD R6, R6, 3           ; /

                                ADD R1, R2, R3          ;Return left + right
                                STR R1, R6, 2
                                RET

SKIP1           LD R2, I                        ;Load current I
                        ADD R2, R2, 1           ;Increment I
                        BR PLUS                         ;Loop PLUS

BREAK1  ;Reset I and do MULT loop

                ;ADD R0, R0, R2         ;Load current char *(str + I)
                LDR R2, R0, 0
                ADD R2, R2, -16         ;*str - '0'
                ADD R2, R2, -16
                ADD R2, R2, -16
                STR R2, R6, 2           ;Store/return char's numerical value in stack
                RET

        LDR R0, R6, 0           ;Put recursion result in R0
        LDR R1, R5, 4           ;Get a
        ADD R0, R0, r1          ;This is the result!!
        STR R0, R5, 0           ;Store answer in z

DONE    LDR R0, R5, 0           ;Get z
        STR R0, R5, 3           ;Put in return value location

        LDR R0, R5, -2          ;Restore R0
        LDR R1, R5, -1          ;Restore R1
        LDR R7, R5, 2           ;Restore return address
        ADD R6, R5, 1           ;Make SP point to old FP
        LDR R5, R6, 0           ;Load old FP back into R5
        ADD R6, R6, 2           ;Make SP point to return value

                RET

I               .fill 0

.end
