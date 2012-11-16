/*
 * Mandelzoom (idea from "The Armchair Universe")
 *
 * Ollie Frolovs <ollie.frolovs.2012@my.bristol.ac.uk>
 *
 * November 2012
 *
 * --[ Useful references:
 * Some hints on validating command line parameters: 
 * http://stackoverflow.com/questions/4308536/converting-a-string-into-a-double
 *
 * Dynamically allocating multidimensional arrays:
 * http://www.eskimo.com/~scs/cclass/int/sx9b.html
 *
 */

#include <stdio.h>
#include <complex.h>
#include <stdlib.h>

#include "mandelzoom.h"


int **AllocateMandelzoomMemory(int asize) {
	int **pPic;

	pPic = malloc( asize * sizeof(int *) );

	if (! pPic) return NULL;

	for (int i=0; i < asize; i++) {
		pPic[i] = malloc( asize * sizeof(int) );

		// Deallocate everything before returning, otherwise a memory leak
		// would result unless the caller calls exit() upon error.
		if (! pPic[i]) {
			for (int j=0; j < i; j++) 
				free(pPic[j]);
			free(pPic);

			return NULL;
		}
	}

	return pPic;
}

void FreeMandelzoomMemory(int **pic, int asize) {
	for (int i=0; i<asize; i++) 
		free( pic[i] );
	free(pic);
}

/*
 * mandelzoom: creates a matrix representation of a part of the Mandlebrot Set
 *
 * Example: mandelzoom(pic, 400, -2, -1.25, 2.5, 1000);
 * Gives the representations of the entire Mandelbrot Set.
 *
 * The arguments are:
 * pic - a square matrix to hold the fractal
 * asize - the order of the matrix (pic)
 * acorner - Re(z_0) where z_0 - starting point
 * bcorner - Im(z_0) where z_0 - starting point
 * side - the length of the side (along x and y axis)
 * depth - the depth of each orbit
 *
 * TODO using Complex is convenient, but what about performance?
 * TODO use the return codes to indicate error
 * TODO check the arguments
 * TODO should depth be optional with default set to 1000?
 */
 
int CreateMandelzoom(int **pic, int asize, double acorner, double bcorner, double side, int depth) {

	double gap = side / asize;

	for (int m = 0; m < asize; m++) {
		for (int n = 0; n < asize; n++) {

			double _Complex c = (acorner + n * gap) + (bcorner + m * gap) * I;
			double _Complex z = 0 + 0 * I;

			int count = 0;
			while ( (count < depth) && (cabs(z) < 2) ) {
				z = z*z + c;
				count++;
			}
			pic[m][n] = count;
			printf("<%d> ", count);
		}
	}

	return 0;
}

void PrintMandelzoomMatrix(int **pic, int asize) {
	for (int m = 0; m < asize; m++) {
		for (int n = 0; n < asize; n++) 
			printf("%d%s", pic[m][n],(n == asize-1)?"":",");
		printf("\n");
	}
}
