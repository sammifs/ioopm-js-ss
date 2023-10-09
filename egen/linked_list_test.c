#include <CUnit/Basic.h>
#include "linked_list.h"
#include <stdlib.h>
#include <assert.h>

int init_suite(void)
{
    // Change this function if you want to do something *before* you
    // run a test suite
    return 0;
}
int clean_suite(void)
{
    // Change this function if you want to do something *after* you
    // run a test suite
    return 0;
}
// These are example test functions. You should replace them with
// functions of your own.
bool compare_int_elements(elem_t a, elem_t b) { // ioopm_eq_function
  return b.i == a.i;
}
bool compare_int_elements_with_void(elem_t a, elem_t b, void* arg) { // ioopm_predicate
  return b.i == *((int *) arg);
}
void ll_create_destroy() {
    ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);

    CU_ASSERT_PTR_NOT_NULL(ls);

    ioopm_linked_list_destroy(ls);
}

void ll_append() {
    ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);

    ioopm_linked_list_prepend(ls, int_elem(10));
    ioopm_linked_list_append(ls, int_elem(5));

    bool success;
    CU_ASSERT_EQUAL(5, ioopm_linked_list_get(ls, 1, &success).i);
    CU_ASSERT_TRUE(success);
    
    ioopm_linked_list_destroy(ls);
}

void ll_append_empty() {
    ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);

    ioopm_linked_list_append(ls, int_elem(5));

    bool success;
    CU_ASSERT_EQUAL(5, ioopm_linked_list_get(ls, 0, &success).i);
    CU_ASSERT_TRUE(success);
    
    ioopm_linked_list_destroy(ls);
}

void ll_prepend() {
    ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);

    ioopm_linked_list_append(ls, int_elem(5));
    ioopm_linked_list_prepend(ls, int_elem(10));

    bool success;
    CU_ASSERT_EQUAL(10, ioopm_linked_list_get(ls, 0, &success).i);
    CU_ASSERT_TRUE(success);
    
    ioopm_linked_list_destroy(ls);
}

void ll_prepend_empty() {
    ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);

    ioopm_linked_list_prepend(ls, int_elem(5));

    bool success;
    CU_ASSERT_EQUAL(5, ioopm_linked_list_get(ls, 0, &success).i);
    CU_ASSERT_TRUE(success);

    ioopm_linked_list_destroy(ls);
}

void ll_insert() {
    ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);

    ioopm_linked_list_prepend(ls, int_elem(5));
    bool success;
    ioopm_linked_list_insert(ls, 1, int_elem(10), &success);
    CU_ASSERT_TRUE(success);

    CU_ASSERT_EQUAL(10, ioopm_linked_list_get(ls, 1, &success).i);
    CU_ASSERT_TRUE(success);

    ioopm_linked_list_destroy(ls);
}

void ll_insert_empty() {
    ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);

    bool success;
    ioopm_linked_list_insert(ls, 0, int_elem(10), &success);
    CU_ASSERT_TRUE(success);

    CU_ASSERT_EQUAL(10, ioopm_linked_list_get(ls, 0, &success).i);
    CU_ASSERT_TRUE(success);

    ioopm_linked_list_destroy(ls);
}

void ll_insert_head() {
    ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);

    ioopm_linked_list_prepend(ls, int_elem(5));
    bool success;
    ioopm_linked_list_insert(ls, 0, int_elem(10), &success);
    CU_ASSERT_TRUE(success);

    CU_ASSERT_EQUAL(10, ioopm_linked_list_get(ls, 0, &success).i);
    CU_ASSERT_TRUE(success);

    ioopm_linked_list_destroy(ls);
}

void ll_insert_invalid_index() {
    ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);

    bool success;
    ioopm_linked_list_insert(ls, 5, int_elem(10), &success);
    CU_ASSERT_FALSE(success);

    ioopm_linked_list_destroy(ls);
}

void ll_remove() {
    ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);

    ioopm_linked_list_prepend(ls, int_elem(5));
    bool success;
    CU_ASSERT_EQUAL(5, ioopm_linked_list_remove(ls, 0, &success).i);
    CU_ASSERT_TRUE(success);

    ioopm_linked_list_destroy(ls);
}

void ll_remove_invalid_index() {
    ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);

    bool success;
    ioopm_linked_list_prepend(ls, int_elem(10));
    ioopm_linked_list_remove(ls, 5, &success);
    CU_ASSERT_FALSE(success);

    ioopm_linked_list_destroy(ls);   
}

void ll_get_invalid_index() {
    ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);

    ioopm_linked_list_prepend(ls, int_elem(10));
    bool success;
    CU_ASSERT_PTR_NULL(ioopm_linked_list_get(ls, 100, &success).p);
    CU_ASSERT_FALSE(success);

    ioopm_linked_list_destroy(ls);
}

void ll_contains() {
    ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);

    ioopm_linked_list_prepend(ls, int_elem(10));

    CU_ASSERT_FALSE(ioopm_linked_list_contains(ls, int_elem(5)));
    CU_ASSERT_TRUE(ioopm_linked_list_contains(ls, int_elem(10)));

    ioopm_linked_list_destroy(ls);
}

void ll_size() {
    ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);

    CU_ASSERT_EQUAL(ioopm_linked_list_size(ls), 0);
    ioopm_linked_list_prepend(ls, int_elem(10));
    CU_ASSERT_EQUAL(ioopm_linked_list_size(ls), 1);

    ioopm_linked_list_destroy(ls);
}

void ll_size_stress() {
    ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);

    for (int i=0; i<5; i++) {
        ioopm_linked_list_append(ls, int_elem(i));
    }
    bool success;
    ioopm_linked_list_remove(ls,1, &success);
    ioopm_linked_list_remove(ls,2, &success);
    CU_ASSERT_EQUAL(ioopm_linked_list_size(ls), 3);

    ioopm_linked_list_destroy(ls);
}

void ll_clear() {
    ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);

    for (int i=0; i<5; i++) {
        ioopm_linked_list_append(ls, int_elem(i));
    }
    CU_ASSERT_EQUAL(ioopm_linked_list_size(ls), 5);

    ioopm_linked_list_clear(ls);
    CU_ASSERT_TRUE(ioopm_linked_list_is_empty(ls));

    ioopm_linked_list_destroy(ls);
}

void ll_clear_empty() {
    ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);

    ioopm_linked_list_clear(ls);

    CU_ASSERT_PTR_NOT_NULL(ls);
    ioopm_linked_list_destroy(ls);
}

void ll_all() {
    ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);

    for (int i=0; i<5; i++) {
        ioopm_linked_list_append(ls, int_elem(i));
    }
    bool value_less_than_extra(elem_t ignore, elem_t value, void *extra) {
        return value.i < *((int *) extra);
    }
    int num = 4;
    CU_ASSERT_FALSE(ioopm_linked_list_all(ls, value_less_than_extra, &num));
    num = 5;
    CU_ASSERT_TRUE(ioopm_linked_list_all(ls, value_less_than_extra, &num));

    ioopm_linked_list_destroy(ls);
}

void ll_all_empty() {
    ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);

    bool ignored(elem_t ignore, elem_t value, void *extra) {
        return true;
    }
    CU_ASSERT_FALSE(ioopm_linked_list_all(ls, ignored, NULL));

    ioopm_linked_list_destroy(ls);
}

void ll_any() {
    ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);

    for (int i=0; i<5; i++) {
        ioopm_linked_list_append(ls, int_elem(i));
    }

    int num = -125;
    CU_ASSERT_FALSE(ioopm_linked_list_any(ls, compare_int_elements_with_void, &num));
    num = 3;
    CU_ASSERT_TRUE(ioopm_linked_list_any(ls, compare_int_elements_with_void, &num));

    ioopm_linked_list_destroy(ls);
}

void ll_any_empty() {
    ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);

    bool ignored(elem_t ignore, elem_t value, void *extra) {
        return true;
    }
    CU_ASSERT_FALSE(ioopm_linked_list_any(ls, ignored, NULL));

    ioopm_linked_list_destroy(ls);
}

void ll_apply_to_all() {
    ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);

    for (int i=0; i<5; i++) {
        ioopm_linked_list_append(ls, int_elem(i));
    }

    void value_minus_extra(elem_t ignore, elem_t *value, void *extra) { // ioopm_apply_function
        (*value).i -= *((int *) extra);
    }

    int num = 1;
    ioopm_linked_list_apply_to_all(ls, value_minus_extra, &num);

    for (int i=-1; i<4; i++) {
        CU_ASSERT_TRUE(ioopm_linked_list_contains(ls, int_elem(i)));
    }

    ioopm_linked_list_destroy(ls);
}

void ll_apply_to_all_empty() {
    ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);

    void ignored(elem_t ignore, elem_t *value, void *extra) {}
    ioopm_linked_list_apply_to_all(ls, ignored, NULL);
    CU_ASSERT_TRUE(ioopm_linked_list_is_empty(ls));

    ioopm_linked_list_destroy(ls);
}

int main() {
    // First we try to set up CUnit, and exit if we fail
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();
    // We then create an empty test suite and specify the name and
    // the init and cleanup functions
    CU_pSuite linked_list = CU_add_suite("Linked list hash table", init_suite,
                                           clean_suite);
    if (linked_list == NULL) {
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
        (CU_add_test(linked_list, "ioopm_linked_list_create & ioopm_linked_list_destroy", ll_create_destroy) == NULL) ||
        (CU_add_test(linked_list, "ioopm_linked_list_append", ll_append) == NULL) ||
        (CU_add_test(linked_list, "ioopm_linked_list_append on empty ll", ll_append_empty) == NULL) ||
        (CU_add_test(linked_list, "ioopm_linked_list_prepend", ll_prepend) == NULL) ||
        (CU_add_test(linked_list, "ioopm_linked_list_prepend on empty ll", ll_prepend_empty) == NULL) ||
        (CU_add_test(linked_list, "ioopm_linked_list_insert", ll_insert) == NULL) ||
        (CU_add_test(linked_list, "ioopm_linked_list_insert on empty ll", ll_insert_empty) == NULL) ||
        (CU_add_test(linked_list, "ioopm_linked_list_insert with index 0", ll_insert_head) == NULL) ||
        (CU_add_test(linked_list, "ioopm_linked_list_insert with invalid index", ll_insert_invalid_index) == NULL) ||
        (CU_add_test(linked_list, "ioopm_linked_list_remove", ll_remove) == NULL) ||
        (CU_add_test(linked_list, "ioopm_linked_list_remove with invalid index", ll_remove_invalid_index) == NULL) ||
        (CU_add_test(linked_list, "ioopm_linked_list_get with invalid index", ll_get_invalid_index) == NULL) ||
        (CU_add_test(linked_list, "ioopm_linked_list_contains", ll_contains) == NULL) ||
        (CU_add_test(linked_list, "ioopm_linked_list_size", ll_size) == NULL) ||
        (CU_add_test(linked_list, "ioopm_linked_list_size after multiple append/remove", ll_size_stress) == NULL) ||
        (CU_add_test(linked_list, "ioopm_linked_list_clear", ll_clear) == NULL) ||
        (CU_add_test(linked_list, "ioopm_linked_list_clear on empty ll", ll_clear_empty) == NULL) ||
        (CU_add_test(linked_list, "ioopm_linked_list_all", ll_all) == NULL) ||
        (CU_add_test(linked_list, "ioopm_linked_list_all on empty ll", ll_all_empty) == NULL) ||
        (CU_add_test(linked_list, "ioopm_linked_list_any", ll_any) == NULL) ||
        (CU_add_test(linked_list, "ioopm_linked_list_any on empty ll", ll_any_empty) == NULL) ||
        (CU_add_test(linked_list, "ioopm_linked_list_apply_to_all", ll_apply_to_all) == NULL) ||
        (CU_add_test(linked_list, "ioopm_linked_list_apply_to_all on empty ll", ll_apply_to_all_empty) == NULL) ||
        0)
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