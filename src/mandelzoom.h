/*
 *
 * Mandelzoom (idea from "The Armchair Universe")
 *
 * Ollie Frolovs <ollie.frolovs.2012@my.bristol.ac.uk>
 *
 * November 2012
 */

// Allocate & deallocate memory held by the matrix
int **AllocateMandelzoomMemory(int asize);
void FreeMandelzoomMemory(int **pic, int asize);

// Create a matrix representation of a part of the Mandelbrot Set
int CreateMandelzoom(int **pic, int asize, double acorner, double bcorner, double side, int depth);

// Print the representation of the Mandelbrot Set as a matrix
void PrintMandelzoomMatrix(int **pic, int asize);
