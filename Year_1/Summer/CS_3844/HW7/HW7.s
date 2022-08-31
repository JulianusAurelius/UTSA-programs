absdiff_se:                 ; x in %rdi, y in %rsi
    compq   %rsi, %rdi      ; %rdi - %rsi
    jl      .less           ; if x < y, jump to .less
    incq    ge_cnt(%rip)    ; else, increment ge (>=) counter
    movq    %rdi, %rax      ; x in %rax so we can return this value later
    subq    %rsi, %rax      ; x - y in %rax
    ret                     ; return x - y
.less:
    inc    lt_cnt(%rip)     ; increment lt (<) counter 
    movq    %rsi, %rax      ; y in %rax so we can return this value later
    subq    %rdi, %rax      ; y - x in %rax
    ret                     ; return y - x



absdiff:                    ; x in %rdi, y in %rsi
    movq    %rdi, %rax      ; x in our return value
    subq    %rsi, %rax      ; x - y in %rax
    movq    %rdi, %rdx      ; x in %rdx
    subq    %rdi, %rdx      ; y - x in %rdx
    compq   %rsi, %rdi      ; x:y
    cmovl   %rdx, %rax      ; if x < y, return y - x, else return x - y
    ret                     ; return
    
                            ; Old code I had, converted to conditional move instead, but kept this to show my work
                            ;   compq   %rsi, %rdi      ; %rdi - %rsi
                            ;    jl      .less           ; if x < y, jump to .less
                            ;    movq    %rdi, %rax      ; else, x in %rax so we can return this value later
                            ;    subq    %rsi, %rax      ; x - y in %rax
                            ;    ret                     ; return x - y
                            ;.less:                      ; x < y
                            ;    movq    %rsi, %rax      ; y in %rax so we can return this value later
                            ;    subq    %rdi, %rax      ; y - x in %rax
                            ;    ret                     ; return y - x



fact_do:                    ; n in %rdi
    movq    $1, %rax        ; set %rax to 1
.start_loop:
    imulq   $2, %rax        ; %rax = 2 * %rax
    decq    %rdi            ; decrement n
    compq   $1, %rdi        ; n:1
    jg      .start_loop     ; if n > 1, jump to .start_loop
    ret                     ; return %rax



fact_while:                 ; n in %rdi
    movq    $1, %rax        ; set %rax to 1
    compq   $1, %rdi        ; n:1
    jg      .start_loop     ; if n > 1, jump to .start_loop
    ret                     ; return %rax (Currently 1)
.start_loop:
    imulq   %rdi, %rax      ; %rax = %rdi * %rax
    decq    %rdi            ; decrement n
    compq   $1, %rdi        ; n:1
    jg      .start_loop     ; if n > 1, jump to .start_loop
    ret                     ; return %rax


fact_while  ; 2nd version   ; n in %rdi
    movq    $1, %rax        ; set %rax to 1
        ;movl    $1, %eax        ; set %eax to 1
        ;; For above, change to movq and %rax?
    jmp     .last           ; jump to .last
.start_loop:
    imulq   %rdi, %rax      ; %rax = 2 * %rax
    decq    %rdi            ; decrement n
.last:
    compq   $1, %rdi        ; n:1
    jg      .start_loop     ; if n > 1, jump to .start_loop
    rep     ;ret            ; return %rax