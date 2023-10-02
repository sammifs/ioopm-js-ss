#include <CUnit/Basic.h>
#include "hash_table.h"
#include "linked_list.h"
#include "iterator.h"
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
bool compare_int_elements(elem_t a, elem_t b) {
    return b.i - a.i == 0;
}
void test_create_destroy_ll() {
 ioopm_list_t *xs = ioopm_linked_list_create(compare_int_elements);
 CU_ASSERT_PTR_NOT_NULL(xs);
 ioopm_linked_list_destroy(xs);
}
void test_linked_list_prepend_contains() {
  ioopm_list_t *list = ioopm_linked_list_create(compare_int_elements);
  CU_ASSERT_FALSE(ioopm_linked_list_contains(list, int_elem(3)));
  ioopm_linked_list_prepend(list, int_elem(3));
  CU_ASSERT_TRUE(ioopm_linked_list_contains(list, int_elem(3)));
  ioopm_linked_list_destroy(list);
}
void test_is_empty_ll() {
 ioopm_list_t *xs = ioopm_linked_list_create(compare_int_elements);
 CU_ASSERT_TRUE(ioopm_linked_list_is_empty(xs));
 ioopm_linked_list_append(xs, int_elem(8));
 CU_ASSERT_FALSE(ioopm_linked_list_is_empty(xs));
 ioopm_linked_list_destroy(xs);
}
void test_size_ll() {
 ioopm_list_t *xs = ioopm_linked_list_create(compare_int_elements);
 int values[5]={3, 5, 2, 1, 8};
 for (int i = 0; i < 5; ++i) {
  ioopm_linked_list_append(xs, int_elem(values[i]));
  CU_ASSERT_TRUE(ioopm_linked_list_size(xs)==i+1);
 }
 ioopm_linked_list_destroy(xs);
}

void test_get_ll() {
 ioopm_list_t *xs = ioopm_linked_list_create(compare_int_elements);
 int values[5]={3, 5, 2, 1, 8};
 elem_t new_values[5];
 for (int i = 0; i < 5; ++i) {
  ioopm_linked_list_append(xs, int_elem(values[i]));
 }
 for (int i = 0; i < 5; ++i) {
  new_values[i]=ioopm_linked_list_get(xs, i);
 }
 for (int i = 0; i < 5; ++i) {
  CU_ASSERT_TRUE(compare_int_elements(int_elem(values[i]),new_values[i]));
 }
 ioopm_linked_list_destroy(xs);
}
void test_remove_ll() {
 ioopm_list_t *xs = ioopm_linked_list_create(compare_int_elements);
 int value=3;
 ioopm_linked_list_append(xs, int_elem(value));
 CU_ASSERT_TRUE(ioopm_linked_list_contains(xs, int_elem(3)));
 elem_t removed_value=ioopm_linked_list_remove(xs, 0);
 CU_ASSERT_FALSE(ioopm_linked_list_contains(xs, int_elem(3)));
 CU_ASSERT_TRUE(removed_value.i==3);
 ioopm_linked_list_destroy(xs);
}
void test_clear_ll() {
 ioopm_list_t *xs = ioopm_linked_list_create(compare_int_elements);
 ioopm_linked_list_insert(xs, 0, int_elem(5));
 CU_ASSERT_FALSE(ioopm_linked_list_is_empty(xs));
 ioopm_linked_list_clear(xs);
 CU_ASSERT_TRUE(ioopm_linked_list_is_empty(xs));
 ioopm_linked_list_destroy(xs);
}
bool is_even_ll(elem_t key, elem_t value, void *x) {
 return value.i%2==0;
}
void test_all_ll() {
 ioopm_list_t *xs = ioopm_linked_list_create(compare_int_elements);
 int values[5] = {2, 4, 14, 8, 18};
 for (int i = 0; i < 5; ++i) {
  ioopm_linked_list_append(xs, int_elem(values[i]));
 }
 CU_ASSERT_TRUE(ioopm_linked_list_all(xs, is_even_ll, NULL));
 ioopm_linked_list_insert(xs, 2, int_elem(7));
 CU_ASSERT_FALSE(ioopm_linked_list_all(xs, is_even_ll, NULL));
 ioopm_linked_list_destroy(xs);
}
void test_any_ll() {
 ioopm_list_t *xs = ioopm_linked_list_create(compare_int_elements);
 int values[5] = {3, 7, 15, 9, 17};
 for (int i = 0; i < 5; ++i) {
  ioopm_linked_list_append(xs, int_elem(values[i]));
 }
 CU_ASSERT_FALSE(ioopm_linked_list_any(xs, is_even_ll, NULL));
 ioopm_linked_list_insert(xs, 2, int_elem(8));
 CU_ASSERT_TRUE(ioopm_linked_list_any(xs, is_even_ll, NULL));
 ioopm_linked_list_destroy(xs);
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
  if ((CU_add_test(my_test_suite, "create and destroy", test_create_destroy_ll) == NULL) ||
    (CU_add_test(my_test_suite, "linked list test prepend and contains", test_linked_list_prepend_contains) == NULL) ||
    (CU_add_test(my_test_suite, "linked_list test is_empty", test_is_empty_ll) == NULL) ||
    (CU_add_test(my_test_suite, "linked list test size", test_size_ll) == NULL) ||
    (CU_add_test(my_test_suite, "linked_list test is_empty", test_remove_ll) == NULL) ||
    (CU_add_test(my_test_suite, "linked_list test is_empty", test_clear_ll) == NULL) ||
    (CU_add_test(my_test_suite, "linked_list test is_empty", test_get_ll) == NULL) ||
    (CU_add_test(my_test_suite, "linked_list test is_empty", test_all_ll) == NULL) ||
    (CU_add_test(my_test_suite, "linked_list test is_empty", test_any_ll) == NULL)
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
