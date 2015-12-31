#include <stdbool.h>

#include "../unity/src/unity.h"
#include "../src/vector.h"

void test_vector_empty(void) {
	bool r = vector_empty(NULL);
	TEST_ASSERT_FALSE(r);
	TEST_ASSERT_EQUAL(vector_error, VECTOR_ERR_PARAMETERS);
}
