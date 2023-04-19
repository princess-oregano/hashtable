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

        mov rcx, 32

.loop:
        cmp dword [rsi], 0
        je .ret

        mov al, byte [rsi]
        mov byte [rdi], al

        inc rdi
        inc rsi

        loop .loop

.ret:
        pop rcx
        pop rax

        ret

