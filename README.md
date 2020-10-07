<h2 align=center>Низкоуровневое программирование</a> </h2>

<h3 align=center> <a href="Lab1">Лабораторная работа №1 : библиотека ввода-вывода на Assembler</a> </h3>

В этом задании вы реализована библиотека процедур, которые будут выполнять простые действия со строками, числами и их текстовыми представлениями.

<h3 align=center> <a href="Lab2">Лабораторная работа №2 : словарь на Assembler</a> </h3>

1. Make a separate assembly file containing functions that you have already written
in the first assignment. We will call it lib.o.
Do not forget to mark all necessary labels global, otherwise they won’t be visible
outside of this object file!

2. Create a file colon.inc and define a colon macro there to create dictionary words.
This macro will take two arguments:
* Dictionary key (inside quotes).
*	 Assembly label name. Keys can contain spaces and other characters, which are not
allowed in label names.
Each entry should start with a pointer to the next entry, then hold a key as a nullterminated string. The content is then directly described by a programmer—for
example, using db directives, as in the example shown in Listing 5-35.

3. Create a function find_word inside a new file dict.asm. It accepts two arguments:
(a) A pointer to a null terminated key string.
(b) A pointer to the last word in the dictionary. Having a pointer to the last word
defined, we can follow the consecutive links to enumerate all words in the
dictionary.
find_word will loop through the whole dictionary, comparing a given key with
each key in dictionary. If the record is not found, it returns zero; otherwise it
returns record address.

4. A separate include file words.inc to define dictionary words using the colon
macro. Include it in main.asm.

5. A simple _start function. It should perform the following actions:
* Read the input string in a buffer of maximum 255 characters long.
* Try to find this key in dictionary. If found, print the corresponding value. If not,
print an error message.

<h3 align=center> <a href="Lab3">Лабораторная работа №3 : скалярное произведение векторов и проверка напростоту чисел</a> </h3>

#Assignment: Scalar Product

A scalar product of two vectors
The solution should consist of:
*	 Two global arrays of int of the same size.
*	 A function to compute the scalar product of two given arrays.
*	 A main function which calls the product computations and outputs its results.

#Assignment: Prime Number Checker

You have to write a function to test the number for primarity. The interesting thing is that the number will be
of the type unsigned long and that it will be read from stdin.

*	 You have to write a function int is_prime( unsigned long n ), which checks
whether n is a prime number or not. If it is the case, the function will return 1;
otherwise 0.
*	 The main function will read an unsigned long number and call is_prime function on
it. Then, depending on its result, it will output either yes or no.
Read man scanf and use scanf function with the format specifier %lu.
Remember, is_prime accepts unsigned long, which is not the same thing as unsigned int!
