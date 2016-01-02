/* Complex Numbers Demo */
#include <stdio.h>
#include <complex.h>

int main(void) {
  double complex z1;
  printf("%lu\n", sizeof(z1)); // Prints 16 (8+8, it must be)
  printf("%lu\n", sizeof(double complex)); // Also 16, as expected.
  return 0;
}

/*
 clang -std=c99 -Wall -pedantic -o src/complex_demo.out src/complex_demo.c
 */
