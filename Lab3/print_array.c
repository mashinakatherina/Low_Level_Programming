#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "lab3.h"

/** Function for printing array
*/
int print_array(const int a[], size_t sz){
	size_t i;
	printf ("[");
	for (i = 0; i < sz; ++i) {
		printf(" %d", a[i]);
		if (i != sz - 1) {
			printf(",");
		}
	}
	printf("]\n");
	return 0;
}