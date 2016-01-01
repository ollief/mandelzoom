/* The vector ADT */
#include "vector.h"

/* Decode the provided error code. Returns a string. */
char* vector_report(const int error) {
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
		case VECTOR_ERR_OUT_OF_BOUNDS:
			return "the provided index is out of bounds";
			break;
	}

	/* This part should never be reached, but if the error code is not recognised,
	   don't change it and report the error via the error description string. */
	return "undefined error code";
}

/* Create an empty vector of size n. The element values are not defined */
vector* vector_create(const int n) {

	/* Check the input argument. Report error if negative. */
	if (n < 0) {
		vector_error = VECTOR_ERR_PARAMETERS;
		return NULL;
	}

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
bool vector_empty(const vector* v) {

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
double* vector_at(const vector* v, int i) {

	/* The vector cannot be NULL. */
	if (!v) {
		vector_error = VECTOR_ERR_NULL;
		return NULL;
	}

	/* The index cannot be out of bounds. */
	if ((i < 0) || (vector_size(v) <= i)) {
		vector_error = VECTOR_ERR_OUT_OF_BOUNDS;
		return NULL;
	}

	/* Now that all checks have passed, report success and return the pointer
	   to the double value at index i, starting from zero! */
	vector_error = VECTOR_SUCCESS;
	return ((v->data) + i * sizeof(double));
}

/* Similar to MATLAB's function of the same name.
   TODO: only ascending values are supported, descending values return error.
   Returns a vector, or NULL in case of error.
	 The global error variable is set to corresponding value in the latter case. */
vector* linspace(const double x0, const double x1, const int n) {

	/* Only ascending values are supported.
	   TODO: there is no good reason for this restriction */
	if (x0 > x1) {
		vector_error = VECTOR_ERR_PARAMETERS;
		return NULL;
	}

	/* The linspace must be of nonzero size.
	   TODO: could this be fixed by using size_t instead? */
	if (n <= 0) {
		vector_error = VECTOR_ERR_PARAMETERS;
		return NULL;
	}

	vector* v = vector_create(n);
	if (!v) {
		/* the vector_error code is already set */
		return NULL;
	}

	for (size_t i = 0; i < n; i++) {
		*vector_at(v,i) = x0 + i * (x1-x0)/(n-1);
	}

	/* Report success, return the result. */
	vector_error = VECTOR_SUCCESS;
	return v;
}
