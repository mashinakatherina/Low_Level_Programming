section .text

global string_length
global string_equals
global string_copy
global print_string
global print_uint
global print_char
global print_int
global parse_uint
global parse_int
global read_char
global read_word
global print_newline

string_length:
    xor rax, rax									; обнуляем rax
	.loop:
		cmp byte[rdi + rax], 0 						; установит ZF = 0, только если [rdi + rax] = 0
		je .exit 									; если ZF == 0, заканчиваем цикл 
		inc rax 									; увеличиваем счетчик
		jmp .loop
	.exit:
   ret

   
print_string:
	mov rsi, rdi									; адрес строки
	call string_length								; считаем длинну строки, помещаем ее в rax
	mov rdx, rax									; помещаем в rdx длинну строки
	mov rax, 1 										; номер системного вызова write
	mov rdi, r15									; дескриптор, который передаем через r15
	syscall
    ret


print_char:
    xor rax, rax
	push rsi										; сохраним rsi
	push rdi										; помещаем в char стек
	mov rsi, rsp 									; адрес строки
	mov rdx, 1										; длинна строки (1)
	mov rax, 1 										; номер системного вызова write
	mov rdi, r15									; дескриптор, который мы храним в r15
	syscall
	pop rsi											; восстановим rsi
	add rsp, 8										; добавим 8 байт в rsp => уменьшим адрес стека => вернем регистр в изначальное состояние
    ret

print_newline:
    xor rax, rax
	mov rdi, 0xA
	call print_char
    ret


print_uint:
													; rsp - голова стека, rdi - переданное число
	push r12
	push r13
	mov r12, rsp									; сохраним вершину стека в r12
	mov r13, 10										; сохраним основание системы счисления для деления
	mov rax, rdi									; сохраним переданное чило в rax
	dec rsp
	mov byte[rsp], 0								; dec+mov - "руками" делаем однобайтовый pop
	.loop:
		dec rsp										; сдвигаем указатель
		xor rdx, rdx								; обнуляем rdx
		div  r13 									; делим на 10, остаток в rdx
		add rdx, 0x30								; переводим в ASCII
		mov  byte[rsp], dl 							; сохраняем в стeк
		test rax, rax								; установит ZF = 0, если rax = 0
		jz .print									; если ZF == 0, заканчиваем деление
		jmp .loop
	.print:
	mov rdi, rsp 									; аргумент для print_string
	call print_string 								; выводим число в stdout
	mov rsp, r12						
    pop r13
    pop r12 										; восстановим регистры
    ret


print_int:
    xor rax, rax
													; rdi - переданное число
	mov rax, rdi									; сохраняем в rax
	test rax, rax									; установим флаги
	jns .not_minus									; если отрицательное, то пицем знак '-'
	mov  rdi, '-'  									; помещаем минус для print_char
	push rax
	call print_char									; выводим минус
	pop rax
	neg rax											; приводим к положительному
	mov rdi, rax
	.not_minus:
	call print_uint									; выводим число 
	ret

	
string_equals:										; rdi - одна строка, rsi - другая 
    xor rax, rax
	push r10
	push r13
	loop:
		mov r10b, byte[rsi]
		mov r13b, byte[rdi]
		inc rsi
		inc rdi
		cmp r10b, r13b
		jne ret_zero
		cmp r13b, 0
		jne loop
		inc rax
	ret_zero:
		pop r13
		pop r10
		ret


read_char:
	push rdi
	push rdx
	dec rsp
	xor rax, rax 										; код системного вызова
	xor rdi, rdi									; дескриптор stdin
	mov rdx, 1										; длинна слова
	mov rsi, rsp									; указатель на начало (и конец)
	syscall
	test rax, rax
	je .return
    xor rax, rax
	mov al, [rsp]									; сохраним в младший байт rax
.return:
    inc rsp
	pop rdx
	pop rdi
    ret 

read_word:
													; rdi - куда записываем, rsi - длинна строки 
	push r13										; сохраняем регистры r13, r14
    push r14
    xor r14, r14
    mov r10, rsi
    mov r13, rdi
	sp_loop:										; пропускаем все пробелы в начале
		call read_char								
		cmp al, 0x20		
		jne write_char								; начинаем записывать слово
		jmp sp_loop
	read_next:
		call read_char		
		cmp al, 0x20 ; space
		je read_end
	write_char:
		cmp al, 0xA
		je read_end
		cmp al, 0x0
		je read_end
		mov byte [r13 + r14], al
		inc r14
		cmp r14, r10
		je read_out
		jmp read_next
	read_end:
		mov rax, r13
		mov byte [r13 + r14], 0
		mov rdx, r14
		jmp return
	read_out:
		xor rax, rax
		xor rdx, rdx
	return:
		pop r14
		pop r13		
	ret

; rdi points to a string
; returns rax: number, rdx : length
parse_uint:
	push r13
	mov r13, 10
    xor rax, rax
	xor rcx, rcx
	xor rdx, rdx
	xor rsi, rsi
	parse_char:
		mov sil, [rdi + rcx]
		cmp sil, 0x30
		jl .return
		cmp sil, 0x39
		jg .return
		inc rcx
		sub sil, 0x30
		mul r13
		add rax, rsi
		jmp parse_char
	.return:
		mov rdx, rcx
		pop r13
		ret

; rdi points to a string
; returns rax: number, rdx : length
parse_int:
    xor rax, rax
    cmp byte [rdi], 0x2d
    je parse_ng
    call parse_uint
    ret
parse_ng:
    inc rdi
    call parse_uint
    cmp rdx, 0
    je .return
    neg rax
    inc rdx
.return:
    ret 


string_copy:
														; в rsi- указатель куда, в rdi - указатель откуда, rdx - длинна строки
	xor rcx, rcx										; обнуляем счетчик
	push r13											; сохраним значение регистра
	.loop:
		cmp rcx, rdx									; сравниваем счетчик и количество символов в строке
		je .too_long										; если все символы скопированы - выходим
		mov r13, [rdi + rcx]							; сохраним в r13 текущий символ
		mov [rsi + rcx], r13							; скопируем
		cmp r13, 0
		je .exit
		inc rcx											; увеличиваем счетчик
		jmp .loop
	.too_long:
		mov rax, 0
	.exit:
		pop r13												; вернем значение r13	
		ret