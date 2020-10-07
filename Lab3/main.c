#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "lab3.h"


int main() {
	size_t sz;
	long unsigned int n;
	size_t i;
	int *x;
	int *y;
	
	printf("Enter vector size: ");
	scanf("%lu", &sz);
	
	x =  (int*)malloc(sz * sizeof(int));
	y =  (int*)malloc(sz * sizeof(int));
	
	printf ("\nEnter first vector: ");
	for (i = 0; i < sz; ++i) {
		scanf("%d", (x+i));
	}
	printf ("\nEnter second vector: ");
	for (i = 0; i < sz; ++i) {
		scanf("%d", (y+i));
	}
	
	setlocale(LC_CTYPE, "Rus");
	printf("x = ");
	print_array(x, sz);
	printf("y = ");
	print_array(y, sz);
	printf( "Inner product: %d\n\n", scalar( x, y,  sz));

	printf("Enter number for prime checking: ");
	if (scanf("%lu", &n)) {	
		prime_int(n) ? printf("%lu Not prime\n", n) : printf("%lu - prime\n", n);
	} else {
		printf("It's not a number\n");
	}
	return 0;
}