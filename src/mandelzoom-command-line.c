/*
 * Mandelzoom command line program
 * 
 * (Most documentation is in mandelzoom.c)
 *
 * Ollie Frolovs <ollie.frolovs.2012@my.bristol.ac.uk>
 *
 * November 2012
 *
 * --[ Useful references:
 * Some hints on validating command line parameters: 
 * http://stackoverflow.com/questions/4308536/converting-a-string-into-a-double
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "mandelzoom.h"

// Helper: Print command line arguments (not relevant outside this command line program) 
void PrintUsageAndExit(void) {
	fprintf(stderr, "Usage: mandelzoom <acorner> <bcorner> <side> <resolution>\n");
	fprintf(stderr, "where acorner, bcorner define the southwest corner of the square\n");
	fprintf(stderr, "with the complex number to wich it corresponds. side is the length of the side.\n");
	fprintf(stderr, "if resolution, the default is 400.\n");

	exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {

	// Resolution of the set, (the order of the representation matrix)
	int asize = 400;

	double acorner = 0;
	double bcorner = 0;
	double side;

	// Validate command line parameters:

	char *pEnd;

	if (argc < 4) {
		fprintf(stderr, "Error: invalid number of arguments.\n");
		PrintUsageAndExit();
	}

  	acorner = strtod (argv[1], &pEnd);
  	if (*pEnd != '\0') {
		fprintf(stderr, "Argument Error: acorner\n");
		PrintUsageAndExit();		
  	}

  	bcorner = strtod (argv[2], &pEnd);
  	if (*pEnd != '\0') {
  		fprintf(stderr, "Argument Error: bcorner\n");
		PrintUsageAndExit();		
  	}

  	side = strtod (argv[3], &pEnd);
  	if (*pEnd != '\0') {
  		fprintf(stderr, "Argument Error: side\n");
		PrintUsageAndExit();		
  	}

  	// The last argument (resolution is optional)
  	if (argc == 5) {
  		asize = strtod(argv[4], &pEnd);

  		if ( (*pEnd != '\0') || (asize < 0) ) {
  			fprintf(stderr, "Argument Error: resolution\n");
  			PrintUsageAndExit();
  		}
  	}

  	// Allocate memory
	int **pPic = AllocateMandelzoomMemory(asize);
	if (! pPic) {
		fprintf(stderr, "Memory Error: failed to allocate enough memory.\n");
		exit(EXIT_FAILURE);
	}

	// Create the representation of the Mandelbrot Set
	int error = CreateMandelzoom(pPic, asize, acorner, bcorner, side, 1000);
	if (error) {
		fprintf(stderr, "Error: unknown error while creating the matrix representation, error = %d.\n", error);
		exit(EXIT_FAILURE);
	}

	// Print the result & deallocate the memory
	PrintMandelzoomMatrix(pPic, asize);
	FreeMandelzoomMemory(pPic, asize);

	return 0;
}
