/* The vector ADT */
#include "vector.h"

/* A vector is an array of numbers of double precision.
   This structure is not to be used directly. */
struct vector {
	int size;
	double* data
}

/* The error reporting is performed through the global variable
   vector_error which takes one of the predefined integer values. */
#define VECTOR_SUCCESS 0
#define VECTOR_ERR_MALLOC 1
#define VECTOR_ERR_MALLOC_DATA 2

