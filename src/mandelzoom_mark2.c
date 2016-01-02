
#include <assert.h>
#include <math.h>
#include <complex.h>
#include <stdio.h>
#include <stdlib.h>

/*
   Compute the orbit for a single point in the complex plane,
   and return the number of iterations it took for the orbit to converge,
   limited by the given depth value.
*/
int mandelbrot(const double re, const double im, const int depth) {
  double complex c = re + im * I;
  double complex z = 0.0 + 0.0 * I;
  int count = 0;
  while( (count < depth) && (cabs(z) < 2) ) {
    z = z*z + c;
    count++;
  }
  return count;
}

int main(void) {
  /* The parameters:
       z0 = a + bi, the starting point
       x, the length along the real axis
       y, the length along the imaginary axis
       nx, number of points along real axis (discretisation)
       ny, number of points along imaginary axis (discretisation)
       d, the depth of each orbit
  */
  double a = -1.0;
  double b = -1.0;
  double x = 2.0;
  double y = 2.0;
  int nx = 1000;
  int ny = 1000;
  int depth  = 1000;

  /* Allocate the memory. */
  fprintf(stderr, "Allocating memory...\n");
  int* m = calloc(nx*ny, sizeof(int));
  assert( m != NULL );

  /* Compute! */
  fprintf(stderr, "Computing...\n");
  for (int j=0; j<nx; j++)
    for (int i=0; i<ny; i++) {
      assert( (i*nx + j) < (nx*ny) );
      m[i*nx + j] = mandelbrot(a+i*x/(nx-1),b+j*y/(ny-1),depth);
    }

  /* Write out the result as PBM (b/w bitmap format).
     The output array must be large enough to accommodate the image.
     Each int of the input is compressed into a single bit in the output.
     Thus, the correct number of bytes must be allocated to cover nx*ny bits.
     (size_t) ceil(nx*ny / (double) 8.0)
  */
  fprintf(stderr, "Transforming to PBM...\n");
  size_t out_size = (size_t) ceil(nx*ny / (double) 8.0);
  unsigned char* out = calloc(out_size, sizeof(unsigned char));
  assert( out != NULL );

  int* i = m;
  int* end = m + nx*ny;
  unsigned char* out_i = out;
  unsigned char o = 0b10000000; /* 0b... is a gcc and clang extension */

  while (i < end) {
    /* If the current point has not converged,
       set the corresponding bit in the output. */
    if (*i == depth) *out_i = (*out_i | o);

    /* If the current output byte has reached its most junior bit, that is
       the value of the mask is one, advance the output pointer to the next byte
       and reset the mask. */
    if (o == 1) {
      o = 0b10000000;
      out_i++;
    } else {
      o >>= 1;
    }
    i++;
  }

  /* Open a file and write out the result. */
  fprintf(stderr,"Writing out the PBM...\n");
  char* fname = "mandelzoom-output.pbm";
  FILE* fp = fopen(fname, "w");
  assert( fp != NULL);
  fprintf(fp,"P4\n%d %d\n", nx, ny);
  fwrite(out, sizeof(unsigned char), out_size, fp);
  int result = fclose(fp);
  assert( result == 0);
  free(out);

  /* Clean-up memory and finish the program. */
  fprintf(stderr,"All done, exiting...\n");
  free(m);
  return 0;
}

/*
For some reason, even the simplest programs using cabs() from complex were
failing with segmentation fault under clang under cygwin. Switched to gcc for now.

 gcc -lm -std=c99 -Wall -pedantic -o src/mandelzoom_mark2.out src/mandelzoom_mark2.c
 */
