#include <CUnit/Basic.h>
#include "hash_table.h"
int init_suite(void) {
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}

int clean_suite(void) {
  // Change this function if you want to do something *after* you
  // run a test suite
  return 0;
}

void test_create_destroy() {
 ioopm_hash_table_t *ht = ioopm_hash_table_create();
 CU_ASSERT_PTR_NOT_NULL(ht);
 ioopm_hash_table_destroy(ht);
}
void test_insert_once() {
 ioopm_hash_table_t *h = ioopm_hash_table_create(); //creating a new hash table
 int k = 0;
 char *v = "Hello, world!";
 char *result = NULL;
 bool success=ioopm_hash_table_lookup(h, k, &result); // key does not map to any value in h, thus false 
 CU_ASSERT_PTR_NULL(result);
 CU_ASSERT_FALSE(success);
 ioopm_hash_table_insert(h, k, v);
 success = ioopm_hash_table_lookup(h, k, &result);
 CU_ASSERT_PTR_NOT_NULL(result);
 CU_ASSERT_TRUE(success);
 ioopm_hash_table_destroy(h);
}
void test_insert_three() {
 ioopm_hash_table_t *h = ioopm_hash_table_create();
 int k[3]={1, 18, 35};
 char *v[3]={"bar", "foo", "baz"};
 char *results[3] = {NULL, NULL, NULL};
 bool v_lookup_1 = ioopm_hash_table_lookup(h, k[0], &results[0]);
 bool v_lookup_2 = ioopm_hash_table_lookup(h, k[1], &results[1]);
 bool v_lookup_3 = ioopm_hash_table_lookup(h, k[2], &results[2]);
 CU_ASSERT_FALSE(v_lookup_1);
 CU_ASSERT_FALSE(v_lookup_2);
 CU_ASSERT_FALSE(v_lookup_3);
 CU_ASSERT_PTR_NULL(results[0]);
 CU_ASSERT_PTR_NULL(results[1]);
 CU_ASSERT_PTR_NULL(results[2]);
 ioopm_hash_table_insert(h, k[0], v[0]);
 ioopm_hash_table_insert(h, k[1], v[1]);
 ioopm_hash_table_insert(h, k[2], v[2]);
 v_lookup_1 = ioopm_hash_table_lookup(h, k[0], &results[0]);
 v_lookup_2 = ioopm_hash_table_lookup(h, k[1], &results[1]);
 v_lookup_3 = ioopm_hash_table_lookup(h, k[2], &results[2]);
 CU_ASSERT(v_lookup_1 && v_lookup_2 && v_lookup_3);
 CU_ASSERT_PTR_NOT_NULL(results[0]);
 CU_ASSERT_PTR_NOT_NULL(results[1]);
 CU_ASSERT_PTR_NOT_NULL(results[2]);
 ioopm_hash_table_destroy(h);
}
void test_lookup_empty() {
 ioopm_hash_table_t *ht = ioopm_hash_table_create();
 char *result = NULL;
 for (int i = 0; i < 17; ++i) /// 17 is a bit magical
 {
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, i, &result));
 }
 CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, -1, &result));
 ioopm_hash_table_destroy(ht);
}
int main() {
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("Test of hash table functions", init_suite, clean_suite);
  if (my_test_suite == NULL) {
      // If the test suite could not be added, tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
  }

  // This is where we add the test functions to our test suite.
  // For each call to CU_add_test we specify the test suite, the
  // name or description of the test, and the function that runs
  // the test in question. If you want to add another test, just
  // copy a line below and change the information
  if (
    (CU_add_test(my_test_suite, "create and destroy", test_create_destroy) == NULL) ||
    (CU_add_test(my_test_suite, "insert once", test_insert_once) == NULL) || 
    (CU_add_test(my_test_suite, "several insertions into the same bucket", test_insert_three) == NULL) 
    || (CU_add_test(my_test_suite, "test_lookup_empty", test_lookup_empty) == NULL) 
    ||    0
  )
    {
      // If adding any of the tests fails, we tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
    }

  // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
  // Use CU_BRM_NORMAL to only print errors and a summary
  CU_basic_set_mode(CU_BRM_VERBOSE);

  // This is where the tests are actually run!
  CU_basic_run_tests();

  // Tear down CUnit before exiting
  CU_cleanup_registry();
  return CU_get_error();
}
