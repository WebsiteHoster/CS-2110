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
        str r0, r5, 0   ;Store 0 in z
        br done
recurse add r6, r6, -2  ;Get ready to call mult
        add r0, r0, -1  ;Calc y - 1
        str r0, r6, 1   ;Store y - 1 on stack
        ldr r0, r5, 4   ;Get x
        str r1, r6, 0   ;Put it on stack
        jsr mult        ;Recursion!!
        ldr r0, r6, 0   ;Put recursion result in r0
        ldr r1, r5, 4   ;Get x
        add r0, r0, r1  ;This is the result!!
        str r0, r5, 0   ;Store answer in z
done    ldr r0, r5, 0   ;Get z
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