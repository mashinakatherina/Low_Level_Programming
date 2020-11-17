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

##### Assignment: Scalar Product

A scalar product of two vectors
The solution should consist of:
*	 Two global arrays of int of the same size.
*	 A function to compute the scalar product of two given arrays.
*	 A main function which calls the product computations and outputs its results.

##### Assignment: Prime Number Checker

You have to write a function to test the number for primarity. The interesting thing is that the number will be
of the type unsigned long and that it will be read from stdin.

*	 You have to write a function `int is_prime( unsigned long n )`, which checks
whether n is a prime number or not. If it is the case, the function will return 1;
otherwise 0.
*	 The main function will read an unsigned long number and call is_prime function on
it. Then, depending on its result, it will output either yes or no.
Read man scanf and use scanf function with the format specifier `%lu`.
Remember, `is_prime` accepts unsigned long, which is not the same thing as unsigned int!

<h3 align=center> <a href="Lab4">Лабораторная работа №4 : Linked list + Функции высшихз порядков</a> </h3>

##### 10.6.1 Assignment 

The program accepts an arbitrary number of integers through stdin. What you have to do is 1. Save them all in a linked list in reverse order. 
2. Write a function to compute the sum of elements in a linked list. 
3. Use this function to compute the sum of elements in the saved list.
4. Write a function to output the n-th element of the list. If the list is too short, signal about it. 
5. Free the memory allocated for the linked list. 

You need to learn to use 
* Structural types to encode the linked list itself. 
* The EOF constant. Read the section “Return value” of the man scanf. You can be sure that
* The input does not contain anything but integers separated by whitespaces. 
* All input numbers can be contained into int variables. Following is the recommended list of functions to implement: 
* `list_create` – accepts a number, returns a pointer to the new linked list node. 
* `list_add_front` – accepts a number and a pointer to a pointer to the linked list. Prepends the new node with a number to the list. For example: a list (1,2,3), a number 5, and the new list is (5,1,2,3). 
* `list_add_back`, adds an element to the end of the list. The signature is the same as list_add_front. 
* `list_get` gets an element by index, or returns 0 if the index is outside the list bounds. 
* `list_free` frees the memory allocated to all elements of list. 
* `list_length` accepts a list and computes its length. 
* `list_node_at` accepts a list and an index, returns a pointer to struct list, corresponding to the node at this index. If the index is too big, returns NULL. 
* `list_sum` accepts a list, returns the sum of elements.

#### 11.7.1 Common Higher-Order Functions 

In this assignment, we are going to implement several higher-order functions on linked lists, which should be familiar to those used to functional programming paradigm. T
hese functions are known under the names foreach, map, map_mut, and foldl. 
* `foreach` accepts a pointer to the list start and a function (which returns void and accepts an int). It launches the function on each element of the list. 
* `map` accepts a function f and a list. It returns a new list containing the results of the f applied to all elements of the source list. The source list is not affected. For example, f (x) = x + 1 will map the list (1, 2, 3) into (2, 3, 4). 
* `map_mut` does the same but changes the source list. 
* `foldl` is a bit more complicated. It accepts: – The accumulator starting value. – A function f (x, a). – A list of elements. It returns a value of the same type as the accumulator, computed in the following way: 1. We launch f on accumulator and the first element of the list. The result is the new accumulator value a′. 2. We launch f on a′ and the second element in list. The result is again the new accumulator value a′′. 3. We repeat the process until the list is consumed. In the end the final accumulator value is the final result. For example, let’s take f (x, a) = x * a. By launching foldl with the accumulator value 1 and this function we will compute the product of all elements in the list. 
* `iterate` accepts the initial value s, list length n, and function f. It then generates a list of length n as follows   

<h3 align=center> <a href="Lab6">Лабораторная работа №6 : Поворот картинки</a> </h3>

#### 13.10 Assignment: Image Rotation

You have to create a program to rotate a BMP image of any resolution to 90 degrees clockwise.
#### 13.10.1 BMP

File Format BMP (BitMaP) format is a raster graphics format, which means that it stores an image as a table of colored dots (pixels). In this format the color is encoded with numbers of a fixed size (can be 1, 4, 8, 16, or 24 bits). If 1 bit is used per pixel, the image is black and white. If 24 bits are used, the number of different colors possible is roughly 16 million. We only implement the rotation of 24-bit images. The subset of BMP files that your program should be able to work with is described by the structure shown in Listing 13-16. It represents the file header, followed immediately by the pixel data.
Architecture
We want to think about program architecture that is extensible and modular.
1. Describe the pixel structure struct pixel to not work with the raster table directly(as with completely structureless data). This should always be avoided.
2. Separate the inner image representation from the input format. The rotation is performed on the inner image format, which is then serialized back to BMP. There can be changes in BMP format, you might want to support other formats, and you do not want to couple the rotation algorithm tightly to BMP.
To achieve that, define a structure structure image to store the pixel array (continuous, now without padding) and some information that should really be kept. For example, there is absolutely no need to store BMP signature here, or any of the never-used header fields. We can get away with the image width and height in pixels. You will need to create functions to read an image from BMP file and to write it to BMP file (probably also to generate a BMP header from the inner representation).
3. Separate file opening from its reading.
4. Make error handling unified and handle errors in exactly one place (for this very program it is enough). To achieve that, define the from_bmp function, which will read a file from the stream and will return one of the codes that show whether the operation completed successfully or not.
Remember the flexibility concerns. Your code should be easy to use in applications with graphical user interface (GUI) as well as in those without GUI at all, so throwing prints into stderr all over the place is not a good option: restrict them to the error handling piece of code. Your code should be easily adaptable for different input formats as well.

<h3 align=center> <a href="Lab7">Лабораторная работа №7 : malloc & free</a> </h3>

##### 13.11 Assignment: Custom Memory Allocator

In this assignment, we are going to implement our own version of `malloc` and `free` based on the memory
mapping system call `mmap` and a linked list of chunks of arbitrary sizes. It can be viewed as a simplified
version of a memory manager typical for the standard C library and shares most of its weaknesses.
For this assignment, the usage of `malloc`/`calloc`, `free` and `realloc` is forbidden
