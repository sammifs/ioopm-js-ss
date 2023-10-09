#include <CUnit/Basic.h>
#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>

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

int extract_int_hash_key(elem_t key)
{
  return key.i;
}
bool stringcomp(elem_t one, elem_t two) {
    return strcmp((char *) one.p, (char *) two.p) == 0;
}
void ht_create_destroy() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    CU_ASSERT_PTR_NOT_NULL(ht);
    ioopm_hash_table_destroy(ht);
}

void ht_insert_lookup() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    // Test looking for nonexistant key
    bool success = false;
    ioopm_hash_table_lookup(ht, int_elem(5), &success);
    CU_ASSERT_FALSE(success);

    ioopm_hash_table_insert(ht, int_elem(5), ptr_elem("hello"));
    CU_ASSERT_STRING_EQUAL("hello", ioopm_hash_table_lookup(ht, int_elem(5), &success).p);
    CU_ASSERT_TRUE(success);

    ioopm_hash_table_destroy(ht);
}

void ht_insert_already_in_use_key() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);
    ioopm_hash_table_insert(ht, int_elem(2), ptr_elem("test"));
    ioopm_hash_table_insert(ht, int_elem(2), ptr_elem("overwritten"));

    bool success;
    CU_ASSERT_STRING_EQUAL("overwritten", ioopm_hash_table_lookup(ht, int_elem(2), &success).p);
    CU_ASSERT_TRUE(success);

    ioopm_hash_table_destroy(ht);
}

void ht_insert_lookup_invalid_key() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);
    ioopm_hash_table_insert(ht, int_elem(-125), ptr_elem("test"));

    bool success;
    CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, int_elem(-125), &success).p);
    CU_ASSERT_FALSE(success);

    ioopm_hash_table_destroy(ht);
}

void ht_remove() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);
    ioopm_hash_table_insert(ht, int_elem(5), ptr_elem("hello"));

    bool success;
    CU_ASSERT_STRING_EQUAL("hello", ioopm_hash_table_remove(ht, int_elem(5), &success).p);
    CU_ASSERT_TRUE(success);

    ioopm_hash_table_destroy(ht);
}

void ht_remove_non_existing() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    bool success;
    CU_ASSERT_PTR_NULL(ioopm_hash_table_remove(ht, int_elem(5), &success).p);
    CU_ASSERT_FALSE(success);

    ioopm_hash_table_destroy(ht);
}

void ht_remove_invalid_key() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    bool success;
    CU_ASSERT_PTR_NULL(ioopm_hash_table_remove(ht, int_elem(-6005), &success).p);
    CU_ASSERT_FALSE(success);

    ioopm_hash_table_destroy(ht);
}

void ht_size_empty_ht() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    CU_ASSERT_EQUAL(0, ioopm_hash_table_size(ht));

    ioopm_hash_table_destroy(ht);
}

void ht_size_after_overwrite() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    ioopm_hash_table_insert(ht, int_elem(5), ptr_elem("Foo"));
    ioopm_hash_table_insert(ht, int_elem(5), ptr_elem("Bar"));
    CU_ASSERT_EQUAL(1, ioopm_hash_table_size(ht));

    ioopm_hash_table_destroy(ht);
}

void ht_size_stress() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    ioopm_hash_table_insert(ht, int_elem(16), ptr_elem("Foo"));
    ioopm_hash_table_insert(ht, int_elem(5), ptr_elem("Bar"));
    ioopm_hash_table_insert(ht, int_elem(0), ptr_elem("Baz"));
    ioopm_hash_table_insert(ht, int_elem(22), ptr_elem("Foo"));
    ioopm_hash_table_insert(ht, int_elem(34), ptr_elem("Bar"));

    bool success;
    ioopm_hash_table_remove(ht, int_elem(5), &success);
    ioopm_hash_table_remove(ht, int_elem(34), &success);

    CU_ASSERT_EQUAL(3, ioopm_hash_table_size(ht));

    ioopm_hash_table_destroy(ht);
}

void ht_clear() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    ioopm_hash_table_insert(ht, int_elem(16), ptr_elem("Foo"));
    ioopm_hash_table_insert(ht, int_elem(5), ptr_elem("Bar"));
    ioopm_hash_table_insert(ht, int_elem(0), ptr_elem("Baz"));
    ioopm_hash_table_insert(ht, int_elem(22), ptr_elem("Foo"));
    ioopm_hash_table_insert(ht, int_elem(34), ptr_elem("Bar"));

    ioopm_hash_table_clear(ht);
    CU_ASSERT_EQUAL(0, ioopm_hash_table_size(ht));

    bool success;
    CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, int_elem(22), &success).p);
    CU_ASSERT_FALSE(success);

    ioopm_hash_table_destroy(ht);
}

void ht_keys() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    int keys[5] = { 3, 10, 42, 0, 99 };
    bool found[5] = { false };
    
    ioopm_hash_table_insert(ht, int_elem(99), ptr_elem("Foo"));
    ioopm_hash_table_insert(ht, int_elem(0), ptr_elem("Bar"));
    ioopm_hash_table_insert(ht, int_elem(42), ptr_elem("Baz"));
    ioopm_hash_table_insert(ht, int_elem(10), ptr_elem("Foo"));
    ioopm_hash_table_insert(ht, int_elem(3), ptr_elem("Bar"));

    ioopm_list_t *returned_keys = ioopm_hash_table_keys(ht);
    ioopm_list_iterator_t *iter = ioopm_list_iterator(returned_keys);
    for (int i=0; i<5; i++) {
        // If ioopm_hash_table_size(ht) isnt 5 something is very wrong
        ioopm_iterator_reset(iter);
        for (int j=0; j<ioopm_hash_table_size(ht); j++) {
            if (compare_int_elements(int_elem(keys[i]),ioopm_iterator_next(iter))) { found[i] = true; break; } 
        }
    }
    
    for (int i=0; i<5; i++) {
        CU_ASSERT_TRUE(found[i]);
    }
    ioopm_linked_list_destroy(returned_keys);
    ioopm_iterator_destroy(iter);
    ioopm_hash_table_destroy(ht);
}

void ht_keys_empty() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);
    ioopm_list_t *returned_keys = ioopm_hash_table_keys(ht);
    CU_ASSERT_PTR_NULL(returned_keys->head);

    ioopm_linked_list_destroy(returned_keys);
    ioopm_hash_table_destroy(ht);
}

void ht_values() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    char *values[5] = { "Foo", "Bar", "Baz", "Boo", "Dar" };
    bool found[5] = { false };

    ioopm_hash_table_insert(ht, int_elem(99), ptr_elem("Foo"));
    ioopm_hash_table_insert(ht, int_elem(0), ptr_elem("Bar"));
    ioopm_hash_table_insert(ht, int_elem(42), ptr_elem("Baz"));
    ioopm_hash_table_insert(ht, int_elem(10), ptr_elem("Boo"));
    ioopm_hash_table_insert(ht, int_elem(3),ptr_elem( "Dar"));

    ioopm_list_t *returned_values = ioopm_hash_table_values(ht);
    ioopm_list_iterator_t *value_iter = ioopm_list_iterator(returned_values);
    for (int i=0; i<5; i++) {
        // If ioopm_hash_table_size(ht) isnt 5 something is very wrong
        ioopm_iterator_reset(value_iter);
        for (int j=0; j<ioopm_hash_table_size(ht); j++) {
            if (stringcomp(ptr_elem(values[i]),ioopm_iterator_next(value_iter))) { found[i] = true; break; } 
        }
    }
    
    for (int i=0; i<5; i++) {
        CU_ASSERT_TRUE(found[i]);
    }
    ioopm_linked_list_destroy(returned_values);
    ioopm_iterator_destroy(value_iter);
    ioopm_hash_table_destroy(ht);
}

void ht_values_empty() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);
    ioopm_list_t *returned_values = ioopm_hash_table_values(ht);
    CU_ASSERT_PTR_NULL(returned_values->head);

    ioopm_linked_list_destroy(returned_values);
    ioopm_hash_table_destroy(ht);
}

void ht_keysvalues() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    int keys[5] = { 3, 10, 42, 0, 99 };
    char *values[5] = { "three", "ten", "fortytwo", "zero", "ninetynine" };
    bool found[5] = { false };

    for (int i=0; i<5; i++) {
        ioopm_hash_table_insert(ht, int_elem(keys[i]), ptr_elem(values[i]));
    }

    ioopm_list_t *returned_keys = ioopm_hash_table_keys(ht);
    ioopm_list_t *returned_values = ioopm_hash_table_values(ht);

    ioopm_list_iterator_t *key_iter = ioopm_list_iterator(returned_keys);
    ioopm_list_iterator_t *value_iter = ioopm_list_iterator(returned_values);

    for (int i=0; i<5; i++) {
        // If ioopm_hash_table_size(ht) isnt 5 something is very wrong
        ioopm_iterator_reset(key_iter);
        ioopm_iterator_reset(value_iter);
        for (int j=0; j<ioopm_hash_table_size(ht); j++) {
            // Index j in the returned list has to return the same as index i in the original.
            // Logical & to MAKE SURE BOTH ioopm_iterator_next() execute.
            if (compare_int_elements(int_elem(keys[i]),ioopm_iterator_next(key_iter)) &
             stringcomp(ptr_elem(values[i]),ioopm_iterator_next(value_iter))) { 
                found[i] = true; 
                break; 
            }
        }
    }

    for (int i=0; i<5; i++) {
        CU_ASSERT_TRUE(found[i]);
    }
    ioopm_linked_list_destroy(returned_keys);
    ioopm_linked_list_destroy(returned_values);
    ioopm_iterator_destroy(key_iter);
    ioopm_iterator_destroy(value_iter);
    ioopm_hash_table_destroy(ht);
}

void ht_has_key() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    ioopm_hash_table_insert(ht, int_elem(5), ptr_elem("Foo"));

    CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, int_elem(5)));
    ioopm_hash_table_destroy(ht);
}

void ht_has_key_nonexistant() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, int_elem(5)));
    ioopm_hash_table_destroy(ht);
}

void ht_has_key_invalid_search() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, int_elem(-1244)));
    ioopm_hash_table_destroy(ht);
}

void ht_has_value() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    ioopm_hash_table_insert(ht, int_elem(5), ptr_elem("Foo"));

    CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, ptr_elem("Foo")));
    ioopm_hash_table_destroy(ht);
}

void ht_has_value_aliasing() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    elem_t word = ptr_elem("Foo");
    ioopm_hash_table_insert(ht, int_elem(5), word);
    CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, word));

    ioopm_hash_table_destroy(ht);
}

bool string_contains(elem_t key_ignore, elem_t value, void *arg) { // ioopm_predicate
    char *lookup = arg;

    for (int i=0; i<strlen(value.p); i++) {
        if (((char *)value.p)[i] == *lookup) { return true; }
    }
    return false;
}
void ht_all() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    int keys[5] = { 3, 10, 42, 0, 99 };
    char *values[5] = { "three", "ten", "fortytwo", "zerot", "ninetynine" };

    for (int i=0; i<5; i++) {
        ioopm_hash_table_insert(ht, int_elem(keys[i]), ptr_elem(values[i]));
    }

    char equal = 'e';
    CU_ASSERT_FALSE(ioopm_hash_table_all(ht, string_contains, &equal));

    equal = 't';
    CU_ASSERT_TRUE(ioopm_hash_table_all(ht, string_contains, &equal));

    ioopm_hash_table_destroy(ht);
}

void ht_all_empty() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    char equal = 'e';
    CU_ASSERT_FALSE(ioopm_hash_table_all(ht, string_contains, &equal));

    ioopm_hash_table_destroy(ht);
}

bool key_equal(elem_t key, elem_t value_ignore, void *arg) { // ioopm_predicate
    int *other_ptr = arg;
    return key.i == *other_ptr;
}
void ht_any() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    int keys[5] = { 3, 10, 42, 0, 99 };
    char *values[5] = { "three", "ten", "fortytwo", "zero", "ninetynine" };

    for (int i=0; i<5; i++) {
        ioopm_hash_table_insert(ht, int_elem(keys[i]), ptr_elem(values[i]));
    }
    int equal = 10;
    CU_ASSERT_FALSE(ioopm_hash_table_any(ht, key_equal, &equal));

    equal = 99;
    CU_ASSERT_TRUE(ioopm_hash_table_any(ht, key_equal, &equal));

    ioopm_hash_table_destroy(ht);
}

void ht_any_empty() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    int equal = 10;
    CU_ASSERT_FALSE(ioopm_hash_table_any(ht, key_equal, &equal));

    ioopm_hash_table_destroy(ht);
}

void pointer_move(elem_t key_ignore, elem_t *value, void *arg) { // ioopm_apply_function
    value->p = value->p + 1;
}
void ht_apply_all() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);

    int keys[5] = { 3, 10, 42, 0, 99 };
    char *values[5] = { "three", "ten", "fortytwo", "tzero", "tnineynine" };

    for (int i=0; i<5; i++) {
        ioopm_hash_table_insert(ht, int_elem(keys[i]), ptr_elem(values[i]));
    }

    char t = 't';
    CU_ASSERT_TRUE(ioopm_hash_table_all(ht, string_contains, &t));
    ioopm_hash_table_apply_to_all(ht, pointer_move, &t);
    CU_ASSERT_FALSE(ioopm_hash_table_all(ht, string_contains, &t));

    ioopm_hash_table_destroy(ht);
}

void ht_apply_all_empty() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create(extract_int_hash_key, compare_int_elements, stringcomp);
    char t = 't';
    CU_ASSERT_FALSE(ioopm_hash_table_all(ht, string_contains, &t));
    ioopm_hash_table_apply_to_all(ht, pointer_move, &t);
    CU_ASSERT_FALSE(ioopm_hash_table_all(ht, string_contains, &t));

    ioopm_hash_table_destroy(ht);
}

int main()
{
    // First we try to set up CUnit, and exit if we fail
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();
    // We then create an empty test suite and specify the name and
    // the init and cleanup functions
    CU_pSuite hash_table = CU_add_suite("Hash table tests", init_suite,
                                           clean_suite);
    if (hash_table == NULL)
    {
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
        (CU_add_test(hash_table, "ioopm_hash_table_create & ioopm_hash_table_destroy", ht_create_destroy) == NULL) ||
        (CU_add_test(hash_table, "ioopm_hash_table_insert & ioopm_hash_table_lookup", ht_insert_lookup) == NULL) ||
        (CU_add_test(hash_table, "ioopm_hash_table_insert with already in use key", ht_insert_already_in_use_key) == NULL) ||
        (CU_add_test(hash_table, "ioopm_hash_table_insert & ioopm_hash_table_lookup with negative value", ht_insert_lookup_invalid_key) == NULL) ||
        (CU_add_test(hash_table, "ioopm_hash_table_remove", ht_remove) == NULL) ||
        (CU_add_test(hash_table, "ioopm_hash_table_remove with negative value", ht_remove_invalid_key) == NULL) ||
        (CU_add_test(hash_table, "ioopm_hash_table_remove before any insert", ht_remove_non_existing) == NULL) ||
        (CU_add_test(hash_table, "ioopm_hash_table_size on empty ht", ht_size_empty_ht) == NULL) ||
        (CU_add_test(hash_table, "ioopm_hash_table_size after overwritten entry", ht_size_after_overwrite) == NULL) ||
        (CU_add_test(hash_table, "ioopm_hash_table_size stress test", ht_size_stress) == NULL) ||
        (CU_add_test(hash_table, "ioopm_hash_table_clear", ht_clear) == NULL) ||
        (CU_add_test(hash_table, "ioopm_hash_table_keys", ht_keys) == NULL) ||
        (CU_add_test(hash_table, "ioopm_hash_table_keys on empty ht", ht_keys_empty) == NULL) ||
        (CU_add_test(hash_table, "ioopm_hash_table_values", ht_values) == NULL) || 
        (CU_add_test(hash_table, "ioopm_hash_table_values on empty ht", ht_values_empty) == NULL) || 
        (CU_add_test(hash_table, "ioopm_hash_table_keys & ioopm_hash_table_values, check if order is maintained between", ht_keysvalues) == NULL) ||
        (CU_add_test(hash_table, "ioopm_hash_table_has_key", ht_has_key) == NULL) ||
        (CU_add_test(hash_table, "ioopm_hash_table_has_key on empty ht", ht_has_key_nonexistant) == NULL) ||
        (CU_add_test(hash_table, "ioopm_hash_table_has_key, with invalid negative search term", ht_has_key_invalid_search) == NULL) ||
        (CU_add_test(hash_table, "ioopm_hash_table_has_value", ht_has_value) == NULL) ||
        (CU_add_test(hash_table, "ioopm_hash_table_has_value with alias", ht_has_value_aliasing) == NULL) ||
        (CU_add_test(hash_table, "ioopm_hash_table_apply_to_all", ht_apply_all) == NULL) ||
        (CU_add_test(hash_table, "ioopm_hash_table_apply_to_all on empty ht", ht_apply_all_empty) == NULL) ||
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