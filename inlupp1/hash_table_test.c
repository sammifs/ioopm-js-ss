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
void remove_once() {
 ioopm_hash_table_t *ht = ioopm_hash_table_create();
 char *result_lookup = NULL;
 char *removed = NULL;
 int k = 2; // could be random
 char *v = "Hello, world!";
 ioopm_hash_table_insert(ht, k, v);
 bool lookup_success=ioopm_hash_table_lookup(ht, k, &result_lookup); // k is in ht
 CU_ASSERT_PTR_NOT_NULL(result_lookup); // result was updated
 CU_ASSERT_TRUE(lookup_success); // lookup was successfull
 bool remove_success = ioopm_hash_table_remove(ht, k, &removed);
 CU_ASSERT_TRUE(remove_success); //removal was successfull
 CU_ASSERT_PTR_NOT_NULL(removed); // removed was updated with the removed value
 lookup_success=ioopm_hash_table_lookup(ht, k, &result_lookup); // k is no longer in ht
 CU_ASSERT_FALSE(lookup_success); //lookup was unsuccessfull
 ioopm_hash_table_destroy(ht);
}
void counting_entries() {
char *v="Hello, world!";
 ioopm_hash_table_t *ht = ioopm_hash_table_create();
 CU_ASSERT_EQUAL(0, ioopm_hash_table_size(ht));
 ioopm_hash_table_insert(ht, 1, v);
 CU_ASSERT_EQUAL(1, ioopm_hash_table_size(ht));
 ioopm_hash_table_insert(ht, 7, v); // 2 entries
 ioopm_hash_table_insert(ht, 4, v); // 3 entries
 CU_ASSERT_EQUAL(3, ioopm_hash_table_size(ht));
 ioopm_hash_table_destroy(ht);
}
void is_empty_ht() {
 char *v="Hello, world!";
 ioopm_hash_table_t *ht = ioopm_hash_table_create();
 CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
 ioopm_hash_table_insert(ht, 1, v);
 ioopm_hash_table_insert(ht, 18, v); //2 entries
 ioopm_hash_table_insert(ht, 7, v); // 3 entries
 ioopm_hash_table_insert(ht, 4, v); // 4 entries
 CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));
 ioopm_hash_table_destroy(ht);
}
void clear_ht() {
 ioopm_hash_table_t *ht = ioopm_hash_table_create();
 char *v = "test";
 for (int i = 0; i < No_Buckets; ++i) {
  ioopm_hash_table_insert(ht, i, v);
  ioopm_hash_table_insert(ht, i+1, v);
 }
 ioopm_hash_table_clear(ht);
 CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
 ioopm_hash_table_destroy(ht);
}
void get_keys() {
 ioopm_hash_table_t *ht = ioopm_hash_table_create();
 int keys[5] = {3, 10, 42, 0, 99};
 bool found[5] = {false};
 char *value = "baz";
 for (int i = 0; i < 5; ++i) {
  ioopm_hash_table_insert(ht, keys[i], value);
 }
 int length = ioopm_hash_table_size(ht);
 int *keys_in_ht = ioopm_hash_table_keys(ht);
 bool is_found = false;
 for (int i = 0; i < length; ++i) {
  for (int j = 0; j < 5; ++j) {
   if (keys[j] == keys_in_ht[i])
   {
    found[j]=true;
    is_found = true;
   }
  }
  if (is_found == false) {
   CU_FAIL("Found a key that was never inserted!");
  }
  is_found = false;
 }
 for (int i = 0; i < 5; ++i) {
  CU_ASSERT_TRUE(found[i]);
 }
 free(keys_in_ht);
 ioopm_hash_table_destroy(ht);
}
void get_values() {
 ioopm_hash_table_t *ht = ioopm_hash_table_create();
 char *values[5] = {"three", "ten", "fortytwo", "zero", "ninetynine"};
 bool found[5] = {false};
 for (int i = 0; i < 5; ++i) 
 {
  ioopm_hash_table_insert(ht, i, values[i]);
 }
 char **resulting_values = ioopm_hash_table_values(ht);
 int i = 0;
 bool is_found = false;
 while (resulting_values[i] != NULL) {
  for (int j = 0; j < 5; ++j) {
   if (strcmp(values[j], resulting_values[i]) == 0)
   {
    found[j]=true;
    is_found = true;
   }
  }
  if (is_found == false) {
   CU_FAIL("Found a value that was never inserted!");
  }
  i+=1;
  is_found = false;
 }
 for (int i = 0; i < 5; ++i) {
  CU_ASSERT_TRUE(found[i]);
 }
 free(resulting_values);
 ioopm_hash_table_destroy(ht);
}
void check_same_order() {
 ioopm_hash_table_t *ht = ioopm_hash_table_create();
 int keys[5] = {3, 10, 42, 0, 99};
 char *values[5] = {"three", "ten", "fortytwo", "zero", "ninetynine"};
 for (int i = 0; i < 5; ++i) {
  ioopm_hash_table_insert(ht, keys[i], values[i]);
 }
 int *resulting_keys = ioopm_hash_table_keys(ht);
 char **resulting_values = ioopm_hash_table_values(ht);
 bool is_found = false;
 for (int i = 0; i < 5; ++i) {
  for (int j = 0; j < 5; ++j) {
   if (keys[j] == resulting_keys[i])
   {
    CU_ASSERT_STRING_EQUAL(resulting_values[i], values[j]);
    is_found = true;
   }
  }
  if (is_found == false) {
   CU_FAIL("Found a key that was never inserted!");  
  }
  is_found = false;
 }
 free(resulting_keys);
 free(resulting_values);
 ioopm_hash_table_destroy(ht);
}
void has_key() {
 ioopm_hash_table_t *ht = ioopm_hash_table_create(); //creating a new hash table
 int key = 0;
 char *value = "Hello, world!";
 bool success=ioopm_hash_table_has_key(ht, key); 
 CU_ASSERT_FALSE(success);
 ioopm_hash_table_insert(ht, key, value);
 success = ioopm_hash_table_has_key(ht, key);
 CU_ASSERT_TRUE(success);
 ioopm_hash_table_destroy(ht);
}
void has_value() {
 ioopm_hash_table_t *ht = ioopm_hash_table_create(); //creating a new hash table
 int key = 0;
 char *value = "Hello, world!";
 bool success=ioopm_hash_table_has_value(ht, value); 
 CU_ASSERT_FALSE(success);
 ioopm_hash_table_insert(ht, key, value);
 success = ioopm_hash_table_has_value(ht, value);
 CU_ASSERT_TRUE(success);
 ioopm_hash_table_destroy(ht);
}
bool is_even(int key, char *value, void *x) {
 return key%2 == 0;
}
void for_all() {
 ioopm_hash_table_t *ht = ioopm_hash_table_create();
 char *value = "ignore";
 ioopm_hash_table_insert(ht, 2, value);
 ioopm_hash_table_insert(ht, 6, value);
 ioopm_hash_table_insert(ht, 10, value);
 ioopm_hash_table_insert(ht, 16, value);
 ioopm_hash_table_insert(ht, 18, value);
 CU_ASSERT_TRUE(ioopm_hash_table_all(ht, is_even, NULL));
 ioopm_hash_table_insert(ht, 9, value);
 CU_ASSERT_FALSE(ioopm_hash_table_all(ht, is_even, NULL));
 ioopm_hash_table_destroy(ht);
}
void for_any() {
 ioopm_hash_table_t *ht = ioopm_hash_table_create();
 char *value = "ignore";
 ioopm_hash_table_insert(ht, 3, value);
 ioopm_hash_table_insert(ht, 7, value);
 ioopm_hash_table_insert(ht, 11, value);
 ioopm_hash_table_insert(ht, 15, value);
 ioopm_hash_table_insert(ht, 17, value);
 CU_ASSERT_FALSE(ioopm_hash_table_any(ht, is_even, NULL));
 ioopm_hash_table_insert(ht, 8, value);
 CU_ASSERT_TRUE(ioopm_hash_table_any(ht, is_even, NULL));
 ioopm_hash_table_destroy(ht);
}
void update_str(int key, char **str, void *x) {
 *str = "Chokladboll";
}
void apply_func_test() {
 ioopm_hash_table_t *ht = ioopm_hash_table_create();
 int keys[5] = {3, 10, 42, 0, 99};
 char *values[5] = {"three", "ten", "fortytwo", "zero", "ninetynine"};
 for (int i = 0; i < 5; ++i) {
  ioopm_hash_table_insert(ht, keys[i], values[i]);
 }
 ioopm_hash_table_apply_to_all(ht, update_str, NULL);
 char **updated_values = ioopm_hash_table_values(ht);
 char *expected_str = "Chokladboll";
 int siz = ioopm_hash_table_size(ht);
 for (int i = 0; i < siz; ++i) {
  CU_ASSERT_TRUE(strcmp(updated_values[i], expected_str) ==0);
 }
 free(updated_values);
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
    || (CU_add_test(my_test_suite, "remove_once", remove_once) == NULL) 
    || (CU_add_test(my_test_suite, "Counting entries", counting_entries) == NULL) 
    || (CU_add_test(my_test_suite, "empty hash table is indeed empty", is_empty_ht) == NULL) 
    || (CU_add_test(my_test_suite, "test of clear function", is_empty_ht) == NULL) 
    || (CU_add_test(my_test_suite, "Returns all keys in ht", get_keys) == NULL) 
    || (CU_add_test(my_test_suite, "Returned array contains all values in ht", get_values) == NULL) 
    || (CU_add_test(my_test_suite, "Keys and values are in the same order", check_same_order) == NULL) 
    || (CU_add_test(my_test_suite, "has key", has_key) == NULL) 
    || (CU_add_test(my_test_suite, "has value", has_value) == NULL)
    || (CU_add_test(my_test_suite, "test of all with is_even as predicate", for_all) == NULL)
    || (CU_add_test(my_test_suite, "test of any with is_even as predicate", for_any) == NULL)
    || (CU_add_test(my_test_suite, "test of apply function", apply_func_test) == NULL)
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
