        section .text
        global format

; -----------------------------------------------
; DESCRIPTION   | Function to format key to 32 bytes.
; -----------------------------------------------
; ENTRY         | RDI - pointer to format key
;               | RSI - pointer to original key
; -----------------------------------------------
; RETURN        | NONE
; -----------------------------------------------
; DESTROYS      | NONE
; -----------------------------------------------
format:
        push rax
        push rcx

        mov rcx, 4

.loop:
        mov rax, qword [rsi]
        mov qword [rdi], rax

        add rdi, 4
        add rsi, 4

        loop .loop

.ret:
        pop rcx
        pop rax

        ret

