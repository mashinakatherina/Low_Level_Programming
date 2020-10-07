#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


int main() {
	size_t vectorSize;
	long unsigned int n;
	size_t i;
	int *x;
	int *y;
	
	printf("Enter vector size: ");
	scanf("%lu", &vectorSize);
	
	x =  (int*)malloc(vectorSize * sizeof(int));
	y =  (int*)malloc(vectorSize * sizeof(int));
	
	printf ("\nEnter first vector: ");
	for (i = 0; i < vectorSize; ++i) {
		scanf("%d", (x+i));
	}
	printf ("\nEnter second vector: ");
	for (i = 0; i < vectorSize; ++i) {
		scanf("%d", (y+i));
	}
	
	printf("x = ");
	print_array(x, vectorSize);
	printf("y = ");
	print_array(y, vectorSize);
	printf( "Inner product: %d\n\n", scalar( x, y,  vectorSize));

	printf("Enter number for prime checking: ");
	if (scanf("%lu", &n)) {	
		prime_int(n) ? printf("%lu Not prime\n", n) : printf("%lu - prime\n", n);
	} else {
		printf("It's not a number\n");
	}
	return 0;
}

/** Function for counting inner product of two vectors
 * @param const int a[], const int b[] - pointers to vector beginning
 * @param int vectorSize - vector size
 * @return size of array
 */
int scalar( const int a[], const int b[], size_t vectorSize ) {
    size_t i = 0; 
    int ans = 0;
    for ( i = 0; i < vectorSize; i++ ) 
        ans += a[i] * b[i];
    return ans;
}


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

/** Function for formated printing array
*/
int print_array(const int a[], size_t vectorSize){
	size_t i;
	printf ("[");
	for (i = 0; i < vectorSize; ++i) {
		printf(" %d", a[i]);
		if (i != vectorSize - 1) {
			printf(",");
		}
	}
	printf("]\n");
	return 0;
}
