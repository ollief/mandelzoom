/* The vector ADT */
#include "vector.h"

#include <stdlib.h>  /* malloc and friends */
#include <stdbool.h> /* I can has bool in C99 */

/* Decode the provided error code. Returns a string. */
char* vector_report(int error) {
	switch (error) {
		case VECTOR_SUCCESS:
			return "operation completed successfully";
			break;
		case VECTOR_ERR_MALLOC:
			return "failed to allocate memory for the description of the vector";
			break;
		case VECTOR_ERR_MALLOC_DATA:
			return "failed to allocate memory for the elements of the vector";
			break;
		case VECTOR_ERR_PARAMETERS:
			return "invalid parameters were provided to the function";
			break;
	}

	return "undefined error code";
}

/* Create an empty vector of size n. The element values are not defined */
vector* vector_create(int n) {
	
	/* Allocate the memory for the vector data structure */
	vector* v = malloc(sizeof(vector));

	/* Report the allocation error, if unsuccessful. */	
	if (!v) {
		vector_error = VECTOR_ERR_MALLOC;	
		return NULL;
	}

	/* Since allocation of the vector was successful,
	   allocate the memory for the elements. */
	double* data = malloc( n*sizeof(double) );
	if (! data) {
		vector_error = VECTOR_ERR_MALLOC_DATA;
		return NULL;
	}

	/* The memory for the elements has been allocated successfully,
	   can set up the vector structure and return it. */
	v->size = n;
	v->data = data;

	/* Report success by resetting the error variable, 
	   and return the vector. */
	vector_error = VECTOR_SUCCESS;
	return v;	
}

/* Returns true if the given vector is empty. 
   Returns false if the given vector is not empty.
   If NULL pointer is passed, returns false and sets the vector_error */
bool vector_empty(vector* v) {

	/* NULL should not have been passed into this function.
	   A NULL pointer is not an empty vector, so return false and 
	   set the global error variable. */
	if (!v) {
		vector_error = VECTOR_ERR_PARAMETERS;
		return false;
	}

	/* Read the vector size from the underlying data structure and
	   determine if it is zero. */
	return ( 0 == v->size );
}

