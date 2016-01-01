/* The vector ADT */
#include "vector.h"

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
		case VECTOR_ERR_NULL:
			return "NULL was passed into the function";
			break;
	}

	/* This part should never be reached, but if the error code is not recognised,
	   don't change it and report the error via the error description string. */
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
	   allocate the memory for the elements.
		 NB: malloc(0) can return either a unique pointer *or* NULL,
		 http://stackoverflow.com/questions/2022335/whats-the-point-in-malloc0
		 In any case the result can be passed to free(). */
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
		vector_error = VECTOR_ERR_NULL;
		return false;
	}

	/* Report success,
	   and return the boolean value telling whether the vector is empty. */
	vector_error = VECTOR_SUCCESS;
	return ( 0 == v->size );
}

/* Returns the size of the given vector.
	 Returns -1 and sets the global error if the vector is NULL. */
int vector_size(const vector* v) {

	/* If NULL was passed, report the error and return -1 */
	if (!v) {
		vector_error = VECTOR_ERR_NULL;
		return -1;
	}

	/* Otherwise, report success and return the size of the vector. */
	vector_error = VECTOR_SUCCESS;
	return v->size;
}

/* Returns a pointer to the vector element at position i.
   Returns NULL and sets global error is the value of i is out of range. */
double* vector_at(vector* v, int i) {
	return NULL;
}
