;section .data
;	message:
;		db "hello", 0

global find_word
extern string_equals

%include "colon.inc"

global _start

section .text

find_word:
								; rdi = адрес нультерм.имени
								; rsi = адрес последнего слова
								; returns: rax = 0 если  не найдено, иначе адрес
												

mov r8, rdi													

.loop:

	mov r9, rsi
	cmp rsi, 0 						; установит EF = 0, только если  rsi == null (проверяем, не пустой ли список слов)
	je .exit_false 					        ; выйдем и скажем, что ничего не нашли
	mov rdi, r8						; вернем строку в rdi
	add rsi, 8						; смотрим что там за строка
	call string_equals					; сравниваем строки
	mov rsi, r9						; возвращаем rsi на место (после string_equals у нас укзатель на конец строки)
	cmp rax, 0 						; проверяем, что вернула функция
	jnz .exit_true						; если не ноль - слова совпали
	mov rsi, [rsi]						; иначе следующее слово
    jmp .loop
	
.exit_true:							; если нашли строку - сохраняем указатель на нее
	mov rax, rsi
	ret 
	
.exit_false:
	mov rax, 0						; если не нашли - сохраняем ноль
	ret
