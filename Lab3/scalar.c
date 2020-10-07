#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "lab3.h"

/** Function for counting inner product of two vectors
 * @param const int a[], const int b[] - pointers to vector beginning
 * @param int sz - vector size
 * @return size of array
 */
int scalar( const int a[], const int b[], size_t sz ) {
    size_t i = 0; 
    int ans = 0;
    for ( i = 0; i < sz; i++ ) 
        ans += a[i] * b[i];
    return ans;
}