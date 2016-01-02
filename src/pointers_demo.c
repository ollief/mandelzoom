
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  double* m = calloc(10,sizeof(double));
  assert( m != NULL );
  m[0] = 0.0; m[1] = 1.0; m[2] = 2.0; m[3] = 3.0; m[4] = 4.0;
  printf("%f\n",m[4]);
  printf("%f\n", *(m+4));
  return 0;
}

/*
 clang -std=c99 -Wall -pedantic -o src/pointers_demo.out src/pointers_demo.c
 */
