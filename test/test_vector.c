#include <stdbool.h>

#include "../unity/src/unity.h"
#include "../src/vector.h"

/* Test vector_empty function which returns true if the vector is
   an empty vector, that is a vector of length 0 */
void test_vector_empty(void) {
	vector v;
	vector_error = VECTOR_SUCCESS; /* reset status */

	TEST_ASSERT_FALSE( vector_empty(NULL) );
	TEST_ASSERT_EQUAL(vector_error, VECTOR_ERR_NULL);

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

/* Test vector_create function, which returns a new vector of desired length.
   The contents of the vector is undefined */
void test_vector_create(void) {
	vector* v;
	vector_error = VECTOR_SUCCESS; /* reset status */

	/* An empty vector creation.
	   Cannot test v->data as malloc(0) can return either a pointer or NULL. */
	v = vector_create(0);
	TEST_ASSERT_TRUE( vector_empty(v) );
	TEST_ASSERT_EQUAL(vector_error, VECTOR_SUCCESS);

	/* One element vector creation */
	v = vector_create(1);
	TEST_ASSERT_FALSE( vector_empty(v) );
	TEST_ASSERT_EQUAL(1, v->size);
	TEST_ASSERT_NOT_NULL( v->data );
	TEST_ASSERT_EQUAL(vector_error, VECTOR_SUCCESS);

	/* Incorrect vector size is given. */
	v = vector_create( -42 );
	TEST_ASSERT_NULL( v );
	TEST_ASSERT_EQUAL(vector_error, VECTOR_ERR_PARAMETERS);

	/* Three element vector creation */
	v = vector_create( 3 );
	TEST_ASSERT_FALSE( vector_empty(v) );
	TEST_ASSERT_EQUAL(3, v->size);
	TEST_ASSERT_NOT_NULL( v->data );
	TEST_ASSERT_EQUAL(vector_error, VECTOR_SUCCESS);

}

/* Test vector_size function. */
void test_vector_size(void) {
	vector* v;

	/* Test empty vector. */
	v = vector_create(0);
	TEST_ASSERT_EQUAL(0, vector_size(v));
	TEST_ASSERT_EQUAL(VECTOR_SUCCESS, vector_error);

	/* Test the NULL pointer. */
	v = NULL;
	TEST_ASSERT_EQUAL(-1, vector_size(v));
	TEST_ASSERT_EQUAL(VECTOR_ERR_NULL, vector_error);

	/* Test multiple element vector. */
	v = vector_create(3);
	TEST_ASSERT_EQUAL(3, vector_size(v));
	TEST_ASSERT_EQUAL(VECTOR_SUCCESS, vector_error);
}
