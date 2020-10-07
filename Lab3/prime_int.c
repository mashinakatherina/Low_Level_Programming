#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "lab3.h"

/** Function for checking is number prime
 * @param x - number
 * @return 0 - number is prime; 1 - number isn't prime
 */
int prime_int(int x) {
	
int i;

if (x%2 == 0 || x == 1){
	return 1;
}

for(i = 3; i*i <= x; i += 2){
	if (x % i == 0){
		return 1;
	}
}

return 0;
}	