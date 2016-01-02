/*
  This little program crashes when performing cabs(c) when compiled with clang
  under cygwin. It works if compi led by gcc.

  clang --version:
    clang version 3.5.1 (tags/RELEA SE_351/final)
    Target: x86_64-unknown-windows-cygnus

  gcc --version:
    gcc (GCC) 4.9.3

  Compile as:
  clang -std=c99 -Wall -o src/complex_crash_demo.out src/complex_crash_demo.c
 */

#include <math.h>
#include <complex.h>
#include <stdio.h>

int main(void) {
  double complex c = 1.0 + 1.0 * I;
  printf("Starting values: c = %.2f + %.2fi\n", creal(c), cimag(c));
  double r = cabs(c);
  printf("%f\n",r);

  return 0;
}
