
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
  /*
   *  The parameters:
   *    z0 = a + bi, the starting point
   *    xside, the length along the real axis
   *    yside, the length along the imaginary axis
   *    nx, number of points along real axis (discretisation)
   *    ny, number of points along imaginary axis (discretisation)
   *    depth, the maximum depth of each orbit is when it is declared divergent
   */
  double a = -2.0;
  double b = -2.0;
  double xside = 4.0;
  double yside = 4.0;
  int nx = 1000;
  int ny = 1000;
  int depth = 1000;

  /* Allocate the memory. */
  fprintf(stderr, "Allocating memory...\n");
  int* m = calloc(nx*ny, sizeof(int));
  assert( m != NULL );

  /*
   * Compute! The result is stored "upside-down" to the normal raster
   * scan order, starting in the lower left corner, going from left to right,
   * and then row by row from the bottom to the top of the image.
   */
  fprintf(stderr, "Computing...\n");
  for (int row=0; row < ny; row++)
    for (int column=0; column < nx; column++) {
      assert( (row*nx + column) < (nx*ny) );
      m[row*nx + column] = mandelbrot(a+column*xside/(nx-1),b+row*yside/(ny-1),depth);
    }

  /*
   * Convert the result to the format suitable for writing out as a PBM file.
   *
   * The output array must be large enough to accommodate the image.
   * Each int of the input is compressed into a single bit in the output.
   * Thus, the correct number of bytes must be allocated to cover nx*ny bits.
   * (size_t) ceil(nx*ny / (double) 8.0)
   */
  fprintf(stderr, "Transforming to PBM...\n");
  size_t out_size = (size_t) ceil(nx*ny / (double) 8.0);
  unsigned char* out = calloc(out_size, sizeof(unsigned char));
  assert( out != NULL );

  /*
   * In PBM, bitmap is stored in the normal raster scan order, starting from
   * the upper left corner, going from left to right, and then row by row from
   * the top to the bottom of the image.
   *
   * This order is different from the result in m. So, must convert.
   */
  unsigned char mask = 0x80; /* set the first bit only */
  unsigned char* out_i = out;

  for (int row=0; row < ny; row++)
    for (int column=0; column < nx; column++) {

      /* Find the next point to process. */
      int x = m[row*nx + column];

      /* If that point is not converging, set the bit in the output. */
      if (x == depth) *out_i |= mask;

      /* Reset the mask if the rightmost bit is reached,
         otherwise shift the mask right. */
      if (0x1 == mask) {
        mask = 0x80;
        out_i++;
      } else {
        mask >>= 1;
      }

      //mask = (0x1 == mask) ? 0x80 : (mask >> 1);
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

  /* Free memory and finish the program. */
  fprintf(stderr,"All done, exiting...\n");
  free(m);
  return 0;
}

/* To compile:
gcc -lm -std=c99 -Wall -pedantic -o src/mandelzoom_mark2.out src/mandelzoom_mark2.c
*/
