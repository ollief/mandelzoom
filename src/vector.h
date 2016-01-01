/* The vector ADT */

#include <stdlib.h>  /* malloc and friends */
#include <stdbool.h> /* I can has bool in C99 */

/* A vector is an array of numbers of double precision.
   This structure is not to be used directly. */
typedef struct {
	int size;
	double* data;
} vector;

/* The error reporting is performed through the global variable
   vector_error which takes one of the predefined integer values. */
int vector_error;

/* The predefined error codes of the Vector library.
   For textual descriptions, see vector_report() function. */
#define VECTOR_SUCCESS 0
#define VECTOR_ERR_MALLOC 1
#define VECTOR_ERR_MALLOC_DATA 2
#define VECTOR_ERR_PARAMETERS 3
#define VECTOR_ERR_NULL 4

/* Forward declarations */
char* vector_report(const int error);
vector* vector_create(const int n);
bool vector_empty(const vector* v);
int vector_size(const vector* v);
