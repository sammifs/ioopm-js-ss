#include <CUnit/Basic.h>
#include "hash_table.h"
#include "linked_list.h"
#include "iterator.h"
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
// -------------------------------------- LINKED LIST -----------------------------------
void test_create_destroy_ll()
{
  ioopm_list_t *xs = ioopm_linked_list_create(compare_int_elements);

  ioopm_linked_list_prepend(xs, int_elem(3));
  ioopm_linked_list_prepend(xs, int_elem(3));
  ioopm_linked_list_prepend(xs, int_elem(3));
  ioopm_linked_list_prepend(xs, int_elem(3));
  ioopm_linked_list_prepend(xs, int_elem(3));
  ioopm_linked_list_prepend(xs, int_elem(3));
  ioopm_linked_list_prepend(xs, int_elem(3));
  CU_ASSERT_PTR_NOT_NULL(xs);
  ioopm_linked_list_destroy(xs);
}
void test_linked_list_prepend_contains()
{
  ioopm_list_t *list = ioopm_linked_list_create(compare_int_elements);
  CU_ASSERT_FALSE(ioopm_linked_list_contains(list, int_elem(3)));
  ioopm_linked_list_prepend(list, int_elem(3));
  CU_ASSERT_TRUE(ioopm_linked_list_contains(list, int_elem(3)));
  ioopm_linked_list_destroy(list);
}
void test_is_empty_ll()
{
  ioopm_list_t *xs = ioopm_linked_list_create(compare_int_elements);
  CU_ASSERT_TRUE(ioopm_linked_list_is_empty(xs));
  ioopm_linked_list_append(xs, int_elem(8));
  CU_ASSERT_FALSE(ioopm_linked_list_is_empty(xs));
  ioopm_linked_list_destroy(xs);
}
void test_size_ll()
{
  ioopm_list_t *xs = ioopm_linked_list_create(compare_int_elements);
  int values[5] = {3, 5, 2, 1, 8};
  for (int i = 0; i < 5; ++i)
  {
    ioopm_linked_list_append(xs, int_elem(values[i]));
    CU_ASSERT_TRUE(ioopm_linked_list_size(xs) == i + 1);
  }
  ioopm_linked_list_destroy(xs);
}

void test_get_ll()
{
  ioopm_list_t *xs = ioopm_linked_list_create(compare_int_elements);
  int values[5] = {3, 5, 2, 1, 8};
  elem_t new_values[5];
  for (int i = 0; i < 5; ++i)
  {
    ioopm_linked_list_append(xs, int_elem(values[i]));
  }
  for (int i = 0; i < 5; ++i)
  {
    new_values[i] = ioopm_linked_list_get(xs, i);
  }
  for (int i = 0; i < 5; ++i)
  {
    CU_ASSERT_TRUE(compare_int_elements(int_elem(values[i]), new_values[i]));
  }
  ioopm_linked_list_destroy(xs);
}
void test_remove_ll()
{
  ioopm_list_t *xs = ioopm_linked_list_create(compare_int_elements);
  int value = 3;
  ioopm_linked_list_append(xs, int_elem(value));
  CU_ASSERT_TRUE(ioopm_linked_list_contains(xs, int_elem(3)));
  elem_t removed_value = ioopm_linked_list_remove(xs, 0);
  CU_ASSERT_FALSE(ioopm_linked_list_contains(xs, int_elem(3)));
  CU_ASSERT_TRUE(removed_value.i == 3);
  ioopm_linked_list_destroy(xs);
}
void test_clear_ll()
{
  ioopm_list_t *xs = ioopm_linked_list_create(compare_int_elements);
  ioopm_linked_list_insert(xs, 0, int_elem(5));
  CU_ASSERT_FALSE(ioopm_linked_list_is_empty(xs));
  ioopm_linked_list_clear(xs);
  CU_ASSERT_TRUE(ioopm_linked_list_is_empty(xs));
  ioopm_linked_list_destroy(xs);
}
bool is_even_ll(elem_t key, elem_t value, void *x)
{
  return value.i%2==0;
}
void test_all_ll()
{
  ioopm_list_t *xs = ioopm_linked_list_create(compare_int_elements);
  int values[5] = {2, 4, 14, 8, 18};
  for (int i = 0; i < 5; ++i)
  {
    ioopm_linked_list_append(xs, int_elem(values[i]));
  }
  CU_ASSERT_TRUE(ioopm_linked_list_all(xs, is_even_ll, NULL));
  ioopm_linked_list_insert(xs, 2, int_elem(7));
  CU_ASSERT_FALSE(ioopm_linked_list_all(xs, is_even_ll, NULL));
  ioopm_linked_list_destroy(xs);
}
void test_any_ll()
{
  ioopm_list_t *xs = ioopm_linked_list_create(compare_int_elements);
  int values[5] = {3, 7, 15, 9, 17};
  for (int i = 0; i < 5; ++i)
  {
    ioopm_linked_list_append(xs, int_elem(values[i]));
  }
  CU_ASSERT_FALSE(ioopm_linked_list_any(xs, is_even_ll, NULL));
//  ioopm_linked_list_insert(xs, 2, int_elem(8));
//  CU_ASSERT_TRUE(ioopm_linked_list_any(xs, is_even_ll, NULL));
    ioopm_linked_list_destroy(xs);
}

// ---------------------------------- ITERATOR --------------------------------------
void test_create_iter_destroy()
{
  ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);
  ioopm_linked_list_append(ls, int_elem(1));
  ioopm_linked_list_append(ls, int_elem(13));
  ioopm_linked_list_append(ls, int_elem(2));
  ioopm_linked_list_append(ls, int_elem(14));

  ioopm_list_iterator_t *iter = ioopm_list_iterator(ls);
  CU_ASSERT_PTR_NOT_NULL(iter);
  for (int i = 0; i < 3; i++)
  {
    ioopm_iterator_next(iter);
  }
  CU_ASSERT_EQUAL(14, ioopm_iterator_current(iter).i);

  ioopm_iterator_reset(iter);
  CU_ASSERT_EQUAL(1, ioopm_iterator_current(iter).i);
  CU_ASSERT_TRUE(ioopm_iterator_has_next(iter));
  ioopm_iterator_next(iter);
  CU_ASSERT_EQUAL(13, ioopm_iterator_remove(iter).i);

  CU_ASSERT_FALSE(ioopm_linked_list_contains(ls, int_elem(13)));

  ioopm_iterator_destroy(iter);
  ioopm_linked_list_destroy(ls);
}

int hash_fun(elem_t key)
{
  return key.i;
}

// ------------------------------ HASH TABLE --------------------------------
void test_create_destroy()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_fun, compare_int_elements);
  CU_ASSERT_PTR_NOT_NULL(ht);
  ioopm_hash_table_destroy(ht);
}
void test_insert_once()
{
  ioopm_hash_table_t *h = ioopm_hash_table_create(hash_fun, compare_int_elements); // creating a new hash table
  int k = 0;
  char *v = "Hello, world!";
  elem_t result = ptr_elem(NULL);
  bool success = ioopm_hash_table_lookup(h, int_elem(k), &result); // key does not map to any value in h, thus false
  CU_ASSERT_PTR_NULL(result.p);
  CU_ASSERT_FALSE(success);
  ioopm_hash_table_insert(h, int_elem(k), ptr_elem(v));
  success = ioopm_hash_table_lookup(h, int_elem(k), &result);
  CU_ASSERT_PTR_NOT_NULL(&result);
  CU_ASSERT_TRUE(success);
  ioopm_hash_table_destroy(h);
}
void test_insert_three()
{
  ioopm_hash_table_t *h = ioopm_hash_table_create(hash_fun, compare_int_elements);
  int k[3] = {1, 18, 35};
  char *v[3] = {"bar", "foo", "baz"};
  elem_t results[3] = {ptr_elem(NULL), ptr_elem(NULL), ptr_elem(NULL)};
  bool v_lookup_1 = ioopm_hash_table_lookup(h, int_elem(k[0]), &results[0]);
  bool v_lookup_2 = ioopm_hash_table_lookup(h, int_elem(k[1]), &results[1]);
  bool v_lookup_3 = ioopm_hash_table_lookup(h, int_elem(k[2]), &results[2]);
  CU_ASSERT_FALSE(v_lookup_1);
  CU_ASSERT_FALSE(v_lookup_2);
  CU_ASSERT_FALSE(v_lookup_3);
  CU_ASSERT_PTR_NULL(results[0].p);
  CU_ASSERT_PTR_NULL(results[1].p);
  CU_ASSERT_PTR_NULL(results[2].p);
  ioopm_hash_table_insert(h, int_elem(k[0]), ptr_elem(v[0]));
  ioopm_hash_table_insert(h, int_elem(k[1]), ptr_elem(v[1]));
  ioopm_hash_table_insert(h, int_elem(k[2]), ptr_elem(v[2]));
  v_lookup_1 = ioopm_hash_table_lookup(h, int_elem(k[0]), &results[0]);
  v_lookup_2 = ioopm_hash_table_lookup(h, int_elem(k[1]), &results[1]);
  v_lookup_3 = ioopm_hash_table_lookup(h, int_elem(k[2]), &results[2]);
  CU_ASSERT(v_lookup_1 && v_lookup_2 && v_lookup_3);
  CU_ASSERT_PTR_NOT_NULL(&results[0]);
  CU_ASSERT_PTR_NOT_NULL(&results[1]);
  CU_ASSERT_PTR_NOT_NULL(&results[2]);
  ioopm_hash_table_destroy(h);
}
void test_lookup_empty()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_fun, compare_int_elements);
  elem_t result = ptr_elem(NULL);
  for (int i = 0; i < No_Buckets; ++i) /// 17 is a bit magical
  {
    CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, int_elem(i), &result));
  }
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, int_elem(-1), &result));
  ioopm_hash_table_destroy(ht);
}
void remove_once()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_fun, compare_int_elements);
  elem_t result_lookup = ptr_elem(NULL);
  elem_t removed = ptr_elem(NULL);
  int k = 2; // could be random
  elem_t v = ptr_elem("Hello, world!");
  ioopm_hash_table_insert(ht, int_elem(k), v);
  bool lookup_success = ioopm_hash_table_lookup(ht, int_elem(k), &result_lookup); // k is in ht
  CU_ASSERT_PTR_NOT_NULL(&result_lookup);                                         // result was updated
  CU_ASSERT_TRUE(lookup_success);                                                 // lookup was successfull
  bool remove_success = ioopm_hash_table_remove(ht, int_elem(k), &removed);
  CU_ASSERT_TRUE(remove_success);                                            // removal was successfull
  CU_ASSERT_PTR_NOT_NULL(&removed);                                          // removed was updated with the removed value
  lookup_success = ioopm_hash_table_lookup(ht, int_elem(k), &result_lookup); // k is no longer in ht
  CU_ASSERT_FALSE(lookup_success);                                           // lookup was unsuccessfull
  ioopm_hash_table_destroy(ht);
}

void counting_entries()
{
  char *v = "Hello, world!";
  ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_fun, compare_int_elements);
  CU_ASSERT_EQUAL(0, ioopm_hash_table_size(ht));
  ioopm_hash_table_insert(ht, int_elem(1), ptr_elem(v));
  CU_ASSERT_EQUAL(1, ioopm_hash_table_size(ht));
  ioopm_hash_table_insert(ht, int_elem(7), ptr_elem(v)); // 2 entries
  ioopm_hash_table_insert(ht, int_elem(4), ptr_elem(v)); // 3 entries
  CU_ASSERT_EQUAL(3, ioopm_hash_table_size(ht));
  ioopm_hash_table_destroy(ht);
}

void is_empty_ht()
{
  char *v = "Hello, world!";
  ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_fun, compare_int_elements);
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_insert(ht, int_elem(1), ptr_elem(v));
  ioopm_hash_table_insert(ht, int_elem(18), ptr_elem(v)); // 2 entries
  ioopm_hash_table_insert(ht, int_elem(7), ptr_elem(v));  // 3 entries
  ioopm_hash_table_insert(ht, int_elem(4), ptr_elem(v));  // 4 entries
  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_destroy(ht);
}
void clear_ht()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_fun, compare_int_elements);
  char *v = "test";
  for (int i = 0; i < No_Buckets; ++i)
  {
    ioopm_hash_table_insert(ht, int_elem(i), ptr_elem(v));
    ioopm_hash_table_insert(ht, int_elem(i + 1), ptr_elem(v));
  }
  ioopm_hash_table_clear(ht);
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_destroy(ht);
}
void get_keys()
{
 ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_fun, compare_int_elements);
 elem_t keys[5] = {int_elem(3), int_elem(10), int_elem(42), int_elem(0), int_elem(99)};
 bool found[5] = {false};
 char *value = "baz";
 for (int i = 0; i < 5; ++i)
 {
  ioopm_hash_table_insert(ht, keys[i], ptr_elem(value));
 }
 int length = ioopm_hash_table_size(ht);
 ioopm_list_t *keys_in_ht = ioopm_hash_table_keys(ht);
 bool is_found = false;
 ioopm_link_t *cursor = keys_in_ht->head->next;
 for (int i = 0; i < length; ++i)
 {
  for (int j = 0; j < 5; ++j)
  {
   if (keys_in_ht->eq_fn(keys[j], cursor->value))
   {
    found[i] = true;
    is_found = true;
   }
  }
  cursor = cursor->next;
  if (is_found == false)
  {
   CU_FAIL("Found a key that was never inserted!");
  }
  is_found = false;
 }
 for (int i = 0; i < 5; ++i)
 {
  CU_ASSERT_TRUE(found[i]);
 }
 ioopm_linked_list_destroy(keys_in_ht);
 ioopm_hash_table_destroy(ht);
}
void get_values()
{
 ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_fun, compare_int_elements);
 char *values[5] = {"three", "ten", "fortytwo", "zero", "ninetynine"};
 bool found[5] = {false};
 for (int i = 0; i < 5; ++i)
 {
  ioopm_hash_table_insert(ht, int_elem(i), ptr_elem(values[i]));
 }
 ioopm_list_t *resulting_values = ioopm_hash_table_values(ht);
 bool is_found = false;
 ioopm_link_t *cursor = resulting_values->head->next;
 int i = 0;
 while (cursor != NULL && !is_found)
 {
  for (int j = 0; j < 5; ++j)
  {
   if (compare_values(cursor->value, ptr_elem(values[j])))
   {
    found[i] = true;
    is_found = true;
   }
  }
  cursor = cursor->next;
  if (is_found == false)
  {
   CU_FAIL("Found a value that was never inserted!");
  }
  is_found = false;
  i=i+1;
 }
 for (int i = 0; i < 5; ++i)
 {
  CU_ASSERT_TRUE(found[i]);
 }
 ioopm_linked_list_destroy(resulting_values);
 ioopm_hash_table_destroy(ht);
}
void has_key()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_fun, compare_int_elements);
  elem_t key = int_elem(0);
  elem_t value = ptr_elem("Hello, world!");
  bool success = ioopm_hash_table_has_key(ht, key);
  CU_ASSERT_FALSE(success);
  ioopm_hash_table_insert(ht, key, value);
  success = ioopm_hash_table_has_key(ht, key);
  CU_ASSERT_TRUE(success);
  ioopm_hash_table_destroy(ht);
}
void has_value()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_fun, compare_int_elements); // creating a new hash table
  elem_t key = int_elem(0);
  elem_t value = ptr_elem("Hello, world!");
  bool success = ioopm_hash_table_has_value(ht, value);
  CU_ASSERT_FALSE(success);
  ioopm_hash_table_insert(ht, key, value);
  success = ioopm_hash_table_has_value(ht, value);
  CU_ASSERT_TRUE(success);
  ioopm_hash_table_destroy(ht);
}
bool is_even(elem_t key, elem_t value, void *x)
{
  return key.i % 2 == 0;
}
void for_all()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_fun, compare_int_elements);
  elem_t value = ptr_elem("ignore");
  ioopm_hash_table_insert(ht, int_elem(2), value);
  ioopm_hash_table_insert(ht, int_elem(6), value);
  ioopm_hash_table_insert(ht, int_elem(10), value);
  ioopm_hash_table_insert(ht, int_elem(16), value);
  ioopm_hash_table_insert(ht, int_elem(18), value);
  CU_ASSERT_TRUE(ioopm_hash_table_all(ht, is_even, NULL));
  ioopm_hash_table_insert(ht, int_elem(9), value);
  CU_ASSERT_FALSE(ioopm_hash_table_all(ht, is_even, NULL));
  ioopm_hash_table_destroy(ht);
}
void for_any()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_fun, compare_int_elements);
  elem_t value = ptr_elem("ignore");
  ioopm_hash_table_insert(ht, int_elem(3), value);
  ioopm_hash_table_insert(ht, int_elem(7), value);
  ioopm_hash_table_insert(ht, int_elem(11), value);
  ioopm_hash_table_insert(ht, int_elem(15), value);
  ioopm_hash_table_insert(ht, int_elem(17), value);
 CU_ASSERT_FALSE(ioopm_hash_table_any(ht, is_even, NULL));
  ioopm_hash_table_insert(ht, int_elem(8), value);
  CU_ASSERT_TRUE(ioopm_hash_table_any(ht, is_even, NULL));
  ioopm_hash_table_destroy(ht);
}
void update_str(elem_t key, elem_t *v, void *x)
{
  v->p = "Chokladboll";
}
void pointer_move(elem_t key, elem_t *v, void *empty)
{
  v->p = (v->p + 1);
}
void apply_func_test()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_fun, compare_int_elements);
  int keys[5] = {3, 10, 42, 0, 99};
  char *values[5] = {"three", "ten", "fortytwo", "zero", "ninetynine"};
  for (int i = 0; i < 5; ++i)
  {
    ioopm_hash_table_insert(ht, int_elem(keys[i]), ptr_elem(values[i]));
  }
  ioopm_hash_table_apply_to_all(ht, pointer_move, NULL);
  ioopm_list_t *new_values = ioopm_hash_table_values(ht);
  char *correct_values[5] = {"ero", "hree", "ortytwo", "en", "inetynine"};
  bool result = true;
  ioopm_link_t *cursor = new_values->head->next;
  for (int i = 0; i < 5; i++)
  {
    if (strcmp((char *) cursor->value.p, correct_values[i]) != 0) {result = false;}
    cursor = cursor->next;
  }
  CU_ASSERT_TRUE(result);

  ioopm_hash_table_apply_to_all(ht, update_str, NULL);
  ioopm_list_t *updated_values = ioopm_hash_table_values(ht);
  char *expected_str = "Chokladboll";
  int siz = ioopm_hash_table_size(ht);
  ioopm_link_t *new_cursor = updated_values->head->next;
  for (int i = 0; i < siz; ++i)
  {
    CU_ASSERT_TRUE(strcmp((char *) new_cursor->value.p, expected_str) == 0);
  }
  ioopm_linked_list_destroy(updated_values);
  ioopm_linked_list_destroy(new_values);
  ioopm_hash_table_destroy(ht);
}

// --------------------------- MAIN -----------------------------------
int main()
{
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite linked_list = CU_add_suite("Test of linked list functions", init_suite, clean_suite);
  if (linked_list == NULL)
  {
    // If the test suite could not be added, tear down CUnit and exit
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_pSuite iterator = CU_add_suite("Test of iterator functions", init_suite, clean_suite);
  if (linked_list == NULL)
  {
    // If the test suite could not be added, tear down CUnit and exit
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_pSuite hash_table = CU_add_suite("Test of hash table functions", init_suite, clean_suite);
  if (linked_list == NULL)
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
      (CU_add_test(linked_list, "create and destroy", test_create_destroy_ll) == NULL)
     || (CU_add_test(linked_list, "linked list test prepend and contains", test_linked_list_prepend_contains) == NULL) 
    ||  (CU_add_test(linked_list, "linked_list test is_empty", test_is_empty_ll) == NULL)
      ||(CU_add_test(linked_list, "linked list test size", test_size_ll) == NULL)
      ||(CU_add_test(linked_list, "linked_list test remove", test_remove_ll) == NULL)
      ||(CU_add_test(linked_list, "linked_list test clear", test_clear_ll) == NULL)
       ||(CU_add_test(linked_list, "linked_list test get at index", test_get_ll) == NULL)
      || (CU_add_test(linked_list, "linked_list test bool all links", test_all_ll) == NULL) 
        ||(CU_add_test(linked_list, "linked_list test bool any links", test_any_ll) == NULL)
           ||(CU_add_test(iterator, "iterator test all functions and destructor", test_create_iter_destroy) == NULL)
     ||   (CU_add_test(hash_table, "hash_table test creation and destruction", test_create_destroy) == NULL)
     ||   (CU_add_test(hash_table, "hash_table test inserting one element into ht", test_insert_once) == NULL)
     ||  (CU_add_test(hash_table, "hash_table test inserting three elements into ht", test_insert_three) == NULL)
     || (CU_add_test(hash_table, "hash_table test looking up empty hash table", test_lookup_empty) == NULL)
   ||   (CU_add_test(hash_table, "hash_table test inputing and removing once", remove_once) == NULL)
  ||    (CU_add_test(hash_table, "hash_table test inserting and checking size", counting_entries) == NULL)
 ||     (CU_add_test(hash_table, "hash_table test empty hash table", is_empty_ht) == NULL)
 ||     (CU_add_test(hash_table, "hash_table test clearing hash table", clear_ht) == NULL)
 ||     (CU_add_test(hash_table, "hash_table test list of keys", get_keys) == NULL) 
 ||     (CU_add_test(hash_table, "hash_table test list of values", get_values) == NULL)
      || (CU_add_test(hash_table, "hash_table test for_any", for_any) == NULL)
      || (CU_add_test(hash_table, "hash_table test for_all", for_all) == NULL)
      || (CU_add_test(hash_table, "hash_table test of apply", apply_func_test) == NULL)
      || (CU_add_test(hash_table, "hash_table test has key", has_key) == NULL) 
      || (CU_add_test(hash_table, "hash_table test has value", has_value) == NULL) 
      || 0)
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
