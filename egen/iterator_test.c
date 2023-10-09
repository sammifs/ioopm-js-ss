#include <CUnit/Basic.h>
#include "iterator.h"
#include "linked_list.h"

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

bool compare_int_elements(elem_t a, elem_t b) { // ioopm_eq_function
  return b.i == a.i;
}
void iter_create_destroy() {
    ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);

    ioopm_list_iterator_t *iter = ioopm_list_iterator(ls);

    CU_ASSERT_PTR_NOT_NULL(iter);

    ioopm_iterator_destroy(iter);
    ioopm_linked_list_destroy(ls);
}

void iter_has_next() {
    ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);

    ioopm_list_iterator_t *iter = ioopm_list_iterator(ls);

    CU_ASSERT_FALSE(ioopm_iterator_has_next(iter));

    ioopm_linked_list_append(ls, int_elem(15));

    CU_ASSERT_TRUE(ioopm_iterator_has_next(iter));

    ioopm_iterator_destroy(iter);
    ioopm_linked_list_destroy(ls);
}

void iter_next() {
    ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);

    ioopm_linked_list_prepend(ls, int_elem(10));
    ioopm_linked_list_prepend(ls, int_elem(15));

    ioopm_list_iterator_t *iter = ioopm_list_iterator(ls);

    CU_ASSERT_EQUAL(15, ioopm_iterator_next(iter).i);
    CU_ASSERT_EQUAL(10, ioopm_iterator_next(iter).i);

    ioopm_iterator_destroy(iter);
    ioopm_linked_list_destroy(ls);
}

void iter_reset() {
    ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);

    ioopm_linked_list_prepend(ls, int_elem(10));
    ioopm_linked_list_prepend(ls, int_elem(15));
    ioopm_linked_list_prepend(ls, int_elem(25));

    ioopm_list_iterator_t *iter = ioopm_list_iterator(ls);

    while (ioopm_iterator_has_next(iter)) {
        ioopm_iterator_next(iter);
    }

    CU_ASSERT_NOT_EQUAL(ls->head, iter->current);
    ioopm_iterator_reset(iter);
    CU_ASSERT_EQUAL(ls->head, iter->current);

    ioopm_iterator_destroy(iter);
    ioopm_linked_list_destroy(ls);
}

void iter_current() {
    ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);

    ioopm_linked_list_prepend(ls, int_elem(10));

    ioopm_list_iterator_t *iter = ioopm_list_iterator(ls);
    ioopm_iterator_next(iter);
    CU_ASSERT_EQUAL(10, ioopm_iterator_current(iter).i);

    ioopm_iterator_destroy(iter);
    ioopm_linked_list_destroy(ls);
}
int main() {
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite iterator = CU_add_suite("Iterator tests", init_suite, clean_suite);
  if (iterator == NULL) {
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
    (CU_add_test(iterator, "ioopm_list_iterator & ioopm_iterator_destroy", iter_create_destroy) == NULL) ||
    (CU_add_test(iterator, "ioopm_iterator_has_next", iter_has_next) == NULL) ||
    (CU_add_test(iterator, "ioopm_iterator_next", iter_next) == NULL) ||
    (CU_add_test(iterator, "ioopm_iterator_reset", iter_reset) == NULL) ||
    (CU_add_test(iterator, "ioopm_iterator_current", iter_current) == NULL) ||
    0
  )
    {
      // If adding any of the tests fails, we tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
    }

  // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
  // Use CU_BRM_NORMAL to only print errors and a summary
  CU_basic_set_mode(CU_BRM_NORMAL);

  // This is where the tests are actually run!
  CU_basic_run_tests();

  // Tear down CUnit before exiting
  CU_cleanup_registry();
  return CU_get_error();
}