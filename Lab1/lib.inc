section .data
	buf : times 256 db 0

section .text
 
 
; Принимает код возврата и завершает текущий процесс
exit: 
    xor rax, rax,
    ret 

; Принимает указатель на нуль-терминированную строку, возвращает её длину
string_length:
    xor rax, rax									
	.loop:
		cmp byte[rdi + rax], 0 						
		jz .exit 									
		inc rax 									
		jmp .loop
	.exit:
   ret


; Принимает указатель на нуль-терминированную строку, выводит её в stdout
print_string:
    call string_length			
	   mov rsi, rdi				
	   mov rdx, rax				
	   mov rax, 1					
	   mov rdi, 1					
	   syscall
	   xor rax, rax
    ret

; Принимает код символа и выводит его в stdout
print_char:
    push rdi 
    mov rsi, rsp ; адрес вершины стэка
    mov rdi, 1 ; куда выводить (stdout)
    mov rdx, 1 ; сколько выводить
    mov rax, 1 ; код sys_write
    syscall
    pop rdi ; забираем символ со стэка
    ret

; Переводит строку (выводит символ с кодом 0xA)
print_newline:
    mov rax, 1					
   	mov rdi, 1					
		mov rsi, 10		
		mov rdx, 1			
		syscall
 xor rax, rax	
 ret 

; Выводит беззнаковое 8-байтовое число в десятичном формате 
; Совет: выделите место в стеке и храните там результаты деления
; Не забудьте перевести цифры в их ASCII коды.
print_uint:
; rsp - голова стека, rdi - переданное число
    push r12
    push r13
    mov r12, rsp ; сохраним вершину стека в r12
    mov r13, 10 ; сохраним основание системы счисления для деления
    mov rax, rdi ; сохраним переданное чило в rax
    dec rsp
    mov byte[rsp], 0 ; dec+mov - "руками" делаем однобайтовый pop
	.loop:
		dec rsp ; двигаем указатель
		xor rdx, rdx ; обнуляем rdx
		div  r13 ; делим на 10, остаток в rdx
		add rdx, 0x30 ; переводим в ASCII
		mov  byte[rsp], dl ; сохраняем в стeк
		test rax, rax ; установит ZF = 0, если rax = 0
		jz .print ; если ZF - 0, заканчиваем
		jmp .loop
	.print:
	 mov rdi, rsp ; аргумент для print_string
	 call print_string ; выводим число в stdout
	 mov rsp, r12						
 pop r13
 pop r12 ; восстановим регистры
 ret

; Выводит знаковое 8-байтовое число в десятичном формате 
print_int:
     xor rax, rax
	; rdi - переданное число
         mov rax, rdi ; сохраняем в rax
         test rax, rax ; установим флаги
         jns .plus ; если отрицательное, то пишем знак '-'
         mov  rdi, '-' ; помещаем минус для print_char
         push rax
         call print_char ; выводим минус
         pop rax
         neg rax ; приводим к положительному
         mov rdi, rax
         .plus:
         call print_uint ; выводим число 
         ret

; Принимает два указателя на нуль-терминированные строки, возвращает 1 если они равны, 0 иначе
string_equals:
      xor rcx, rcx
	.loop:
		mov r8b, byte [rdi+rcx]
		mov r9b, byte [rsi+rcx]
		cmp r8b, r9b
		jne .not_equals
		test r8b, r8b
		jz .equals
		inc rcx
		jmp .loop
	.equals:
	mov rax, 1
    ret
	.not_equals:
	mov rax, 0
	ret

; Читает один символ из stdin и возвращает его. Возвращает 0 если достигнут конец потока
read_char:
    push rdi
	push rdx
	dec rsp
	xor rax, rax ; код системного вызова
	xor rdi, rdi ; дескриптор stdin
	mov rdx, 1 ; длинна слова
	mov rsi, rsp ; указатель на начало (и конец)
	syscall
	test rax, rax
	je .return
    xor rax, rax
	mov al, [rsp] ; сохраним в младший байт rax
.return:
    inc rsp
	pop rdx
	pop rdi
    ret 

; Принимает: адрес начала буфера, размер буфера
; Читает в буфер слово из stdin, пропуская пробельные символы в начале, .
; Пробельные символы это пробел 0x20, табуляция 0x9 и перевод строки 0x10.
; Останавливается и возвращает 0 если слово слишком большое для буфера
; При успехе возвращает адрес буфера. 
; Эта функция должна дописывать к слову нуль-терминатор

read_word:
  push rbx ; сохраняем значение rbx
	mov r8, rsi ; сохраняем размер буфера
	mov r9, rdi ; сохраняем адрес буфера
  xor  rbx, rbx ; обнуление счетчика длины
  xor  rdi, rdi ; считывать будем из stdin
  mov  rdx, 1 ; считывать будем по 1 байту
  .skip:
    xor rax, rax ; обнуляем (заносим код sys_read)
    mov rsi, buf ; заносим адрес, куда будем считавать
    syscall
      cmp al, 0 ; сравниваем с концом строки
      je  .finally ; если равно, переходим к завершению
    cmp byte[buf], 0x21 ; сравниваем с кодом последнего 'плохого' символа
    jb  .skip ; если меньше, пропускаем его
  inc rbx ; иначе учитываем
  .read:
    xor rax, rax ; обнуляем (заносим код sys_read)
    lea rsi, [buf + rbx] ; записываем эффективный адрес в rsi (откуда читаем)
    syscall
    cmp byte [buf + rbx], 0x21 ; сравниваем c последним не нужным символом
    jb  .finally ; если меньше (значит символ нам не нужен), -> завершаем чтение
		cmp r8, rbx ; иначе проверяем умещается ли очередной символ
		jbe .exit ; если нет, возвращаем 0
    inc rbx ; иначе учитываем символ
    jmp .read ; и читаем следующий
  .finally:
  mov byte[buf + rbx], 0 ; нультермируем строку в буфере
  mov rdx, rbx ; возвращаем длину строки
  mov rax, buf ; возвращаем указатель на буфер
  pop rbx ; восстанавливаем значение rbx
  ret
	.exit:
	xor rdx, r8 ; записываем длину буфера (=сколько считали символов)
	xor rax, rax ; возвращаем 0
	pop rbx ; восстанавливаем значение rbx
	ret
 

; Принимает указатель на строку, пытается
; прочитать из её начала беззнаковое число.
; Возвращает в rax: число, rdx : его длину в символах
; rdx = 0 если число прочитать не удалось
parse_uint:
parse_uint:
    xor rax, rax
	xor rsi, rsi
    mov r8, 10
    xor rcx, rcx
    xor rdx, rdx
	.loop:
    	mov sil, [rdi+rcx]
	    cmp sil, 0x30 ; проверяем, что этот символ цифра
    	jl .return
    	cmp sil, 0x39
    	jg .return
    	inc rcx
    	sub sil, 0x30 ; символ в число
    	mul r8
    	add rax, rsi
    	jmp .loop
	.return:
    mov rdx, rcx
    ret




; Принимает указатель на строку, пытается
; прочитать из её начала знаковое число.
; Если есть знак, пробелы между ним и числом не разрешены.
; Возвращает в rax: число, rdx : его длину в символах (включая знак, если он был) 
; rdx = 0 если число прочитать не удалось
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

; Принимает указатель на строку, указатель на буфер и длину буфера
; Копирует строку в буфер
; Возвращает длину строки если она умещается в буфер, иначе 0
string_copy:
	; в rsi- указатель куда, в rdi - указатель откуда, rdx - длинна строки
	xor rcx, rcx ; обнуляем счетчик
	push r13 ; сохраним значение регистра
	.loop:
		cmp rcx, rdx ; сравниваем счетчик и количество символов в строке
		je .too_long ; если все символы скопированы - выходим
		mov r13, [rdi + rcx] ; сохраним в r13 текущий символ
		mov [rsi + rcx], r13 ; скопируем
		cmp r13, 0
		je .exit
		inc rcx	; увеличиваем счетчик
		jmp .loop
	.too_long:
		mov rax, 0
	.exit:
		pop r13 ; вернем значение r13	
		ret
