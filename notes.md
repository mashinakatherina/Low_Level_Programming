`nasm -e colon.inc` - что будет после препроцессигна

`nasm -f elf64 -g dict.asm` -- для того, чтобы скомпилировать в `.o`

`nasm -f elf64 -g lib.asm`

`ld -o dict dict.o lib.o`  -- lib.o - это то, что extern

`./dict` - результат работы

`echo $?` - что возвращает


### дебаг

`gdb` 

`b` - точка остановки

`r` - run

`layout asm`

`ni` - следующий шаг

`si` - зайти в функцию

`p $reg` - что в регистре
