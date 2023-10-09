#include "hash_table.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define No_Buckets 17

typedef struct entry entry_t;


struct entry
{
  elem_t key;       // holds the key
  elem_t value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

static entry_t *entry_create(elem_t key, elem_t value, entry_t *next) {
  entry_t *entry = calloc(1, sizeof(entry_t));
  entry->key = key;
  entry->value = value;
  entry->next = next;
  return entry;
}

static void entry_destroy(entry_t *entry) {
  free(entry);
}

struct hash_table
{
  entry_t *buckets[No_Buckets];
  size_t size;
  ioopm_hash_function hash_function;
  ioopm_eq_function key_eq_function;
  ioopm_eq_function value_eq_function;
};

ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function f, ioopm_eq_function key_eq, ioopm_eq_function value_eq) {
  /// Allocate space for a ioopm_hash_table_t = No_Buckets pointers to
  /// entry_t's, which will be set to NULL
  ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
  for (int i=0; i<No_Buckets; i++) { 
    result->buckets[i] = entry_create(ptr_elem(NULL), ptr_elem(NULL), NULL);
  }
  // Initialize size to 0.
  result->size = 0;
  result->hash_function = f;
  result->key_eq_function = key_eq;
  result->value_eq_function = value_eq;
  return result;
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) {
  for (int i=0; i<No_Buckets; i++) {
    entry_t *cursor = ht->buckets[i]->next;
    entry_destroy(ht->buckets[i]);
    while (cursor != NULL) {
      entry_t *tmp = cursor->next;
      entry_destroy(cursor);
      cursor = tmp;

      ht->size--;
    }
  }
  free(ht);
}

static entry_t *find_previous_entry_for_key(entry_t *head_entry, elem_t key, ioopm_eq_function eq) {
  entry_t *cursor = head_entry;
  // If cursor->next reaches null then key is not in this entry-chain, so we return last
  // one before null.
  while (cursor->next != NULL) {
    // If cursor->next contains key, we return current cursor (find *previous*).
    if (eq(cursor->next->key, key)) { break; }
    cursor = cursor->next;
  }
  return cursor;
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value) {
  /// Calculate the bucket for this entry

  int bucket = ht->hash_function(key) % No_Buckets; 
  if (bucket < 0 || bucket > No_Buckets ) { 
    printf("\nInvalid key! - in ioopm_hash_table_insert\n");
    return;
  }

  /// Search for an existing entry for a key
  entry_t *entry = find_previous_entry_for_key(ht->buckets[bucket], key, ht->key_eq_function);
  entry_t *next = entry->next; // If find_previous_entry_for_key fails to find anything,
  // next will be NULL.

  /// Check if the next entry should be updated or not
  if (next != NULL) {
    // We dont increase ht->size since we are overwriting.
    next->value = value;
  }
  else {
    entry->next = entry_create(key, value, next);
    ht->size++;
  }
}

elem_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key, bool *success) {
  int bucket = ht->hash_function(key) % No_Buckets;
  if (bucket < 0 || bucket > No_Buckets ) { 
    printf("\nInvalid key! - in ioopm_hash_table_lookup\n");
    *success = false;
    return ptr_elem(NULL);
  }

  // Find previous entry for key
  entry_t *entry = find_previous_entry_for_key(ht->buckets[bucket], key, ht->key_eq_function);
  entry_t *next  = entry->next;

  // If next isnt null we have what we were looking for.
  if (next != NULL) {
    *success = true;
    return next->value;
  }
  else {
    *success = false;
    return ptr_elem(NULL);
  }
}

elem_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key, bool *success) {
  int bucket = ht->hash_function(key) % No_Buckets; 
  if (bucket < 0 || bucket > No_Buckets ) { 
    printf("\nInvalid key! - in ioopm_hash_table_remove\n");
    *success = false;
    return ptr_elem(NULL);
  }

  entry_t *entry = find_previous_entry_for_key(ht->buckets[bucket], key, ht->key_eq_function);
  entry_t *next  = entry->next;  

  // If next isnt null we have what we were looking for.
  if (next != NULL) {
    // Decrease ht->size, unlink entry to be removed, save removed value, free its memory and 
    // return with success = true.
    ht->size--;
    entry->next = next->next;
    elem_t result = next->value;
    entry_destroy(next);
    *success = true;
    return result;
  }
  else {
    *success = false;
    return ptr_elem(NULL);
  }
}

size_t ioopm_hash_table_size(ioopm_hash_table_t *ht) {
  return ht->size;
}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht) {
  return ht->size == 0;
}

void ioopm_hash_table_clear(ioopm_hash_table_t *ht) {
  for (int i=0; i<No_Buckets; i++) {
    // Avoid removing dummy node at start of each bucket.
    entry_t *cursor = ht->buckets[i]->next;
    ht->buckets[i]->next = NULL;
    while (cursor != NULL) {
      entry_t *tmp = cursor->next;
      entry_destroy(cursor);
      cursor = tmp;

      ht->size--;
    }
  }
}

ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht) {
  // For now the list equality function doesnt matter, although it could be
  // interesting to work with...
  ioopm_list_t *ls = ioopm_linked_list_create(NULL);

  for (int i=0; i<No_Buckets;i++) {
    entry_t *cursor = ht->buckets[i]->next;
    while (cursor != NULL) {
      ioopm_linked_list_append(ls, cursor->key);
      cursor = cursor->next;
    }
  }
  return ls;
}

ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht) {
  // For now the list equality function doesnt matter, although it could be
  // interesting to work with...
  ioopm_list_t *ls = ioopm_linked_list_create(NULL);

  for (int i=0; i<No_Buckets;i++) {
    entry_t *cursor = ht->buckets[i]->next;
    while (cursor != NULL) {
      ioopm_linked_list_append(ls, cursor->value);
      cursor = cursor->next;
    }
  }
  return ls;
}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key) {
  bool success;
  ioopm_hash_table_lookup(ht, key, &success);
  return success;
}

bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value) {
  for (int i=0; i<No_Buckets; i++) {
    entry_t *cursor = ht->buckets[i]->next;
    while (cursor != NULL) {
      if (ht->value_eq_function(cursor->value, value)) { return true; }
      cursor = cursor->next;
    }
  }
  return false;
}

bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg) {
  int size = ioopm_hash_table_size(ht);
  ioopm_list_t *keys = ioopm_hash_table_keys(ht);
  ioopm_list_t *values = ioopm_hash_table_values(ht);

  ioopm_list_iterator_t *key_iter = ioopm_list_iterator(keys);
  ioopm_list_iterator_t *value_iter = ioopm_list_iterator(values);
  bool result = size == 0 ? false : true;
  for (int i = 0; i < size && result; ++i) {
      result = result && pred(ioopm_iterator_next(key_iter), ioopm_iterator_next(value_iter), arg);
  }
  ioopm_linked_list_destroy(keys);
  ioopm_linked_list_destroy(values);
  ioopm_iterator_destroy(key_iter);
  ioopm_iterator_destroy(value_iter);
  return result;
}

bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg) {
  int size = ioopm_hash_table_size(ht);
  ioopm_list_t *keys = ioopm_hash_table_keys(ht);
  ioopm_list_t *values = ioopm_hash_table_values(ht);

  ioopm_list_iterator_t *key_iter = ioopm_list_iterator(keys);
  ioopm_list_iterator_t *value_iter = ioopm_list_iterator(values);
  bool result = false;
  for (int i = 0; i < size && (!result); ++i) {
      result = pred(ioopm_iterator_next(key_iter), ioopm_iterator_next(value_iter), arg);
  }
  ioopm_linked_list_destroy(keys);
  ioopm_linked_list_destroy(values);
  ioopm_iterator_destroy(key_iter);
  ioopm_iterator_destroy(value_iter);
  return result;
}

void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function apply_fun, void *arg) {
  for (int i=0; i<No_Buckets; i++) {
    entry_t *cursor = ht->buckets[i]->next;
    while (cursor != NULL) {
      apply_fun(cursor->key, &cursor->value, arg);
      cursor = cursor->next;
    }
  }
}