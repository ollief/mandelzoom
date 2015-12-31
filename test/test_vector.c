#include <stdbool.h>

#include "../unity/src/unity.h"
#include "../src/vector.h"

void test_vector_empty(void) {
	vector v;
	vector_error = VECTOR_SUCCESS; /* reset status */

	TEST_ASSERT_FALSE( vector_empty(NULL) );
	TEST_ASSERT_EQUAL(vector_error, VECTOR_ERR_PARAMETERS);

	vector_error = VECTOR_SUCCESS; /* reset status */

  /* A zero-element vector is empty */
	v = (vector) { .size = 0, .data = NULL };
	TEST_ASSERT_TRUE( vector_empty(&v) );
	TEST_ASSERT_EQUAL(vector_error, VECTOR_SUCCESS);

	vector_error = VECTOR_SUCCESS; /* reset status */

	/* One element vector is not empty. Malloc retains some random value in data,
	   it does not actually matter what's exactly is in there.*/
	v = (vector) { .size = 1, .data = malloc(sizeof(double)) };
	TEST_ASSERT_FALSE( vector_empty(&v) );
	TEST_ASSERT_EQUAL(vector_error, VECTOR_SUCCESS);

	vector_error = VECTOR_SUCCESS; /* reset status */

	/* Three element vector is not empty as well. */
	v = (vector) { .size = 3, .data = malloc(3*sizeof(double)) };
	TEST_ASSERT_FALSE( vector_empty(&v) );
	TEST_ASSERT_EQUAL(vector_error, VECTOR_SUCCESS);

	vector_error = VECTOR_SUCCESS; /* reset status */
}
