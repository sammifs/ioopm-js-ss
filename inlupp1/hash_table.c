#include "hash_table.h"
#include "common.h"
#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define No_Buckets 17

typedef struct entry entry_t;
struct entry
{
 elem_t key;  // holds the key
 elem_t value; //holds the value
 entry_t *next; // points to the next entry
};
struct hash_table
{
 entry_t *buckets[No_Buckets];
 size_t size;
 ioopm_hash_function hash_fun;
 ioopm_eq_function key_eq_fun;
};
static entry_t *entry_create(elem_t key, elem_t value, entry_t *next) {
 entry_t *entr = calloc(1, sizeof(entry_t));
 entr->key=key;
 entr->value=value;
 entr->next=next;
 return entr;
}
ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function hash_fun, ioopm_eq_function key_eq_fun) 
{
 ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
 for (int i = 0; i < No_Buckets; ++i) {
  result->buckets[i]=entry_create(int_elem(0), ptr_elem(NULL), NULL);
 }
 result->size=0;
 result->hash_fun = hash_fun;
 result->key_eq_fun = key_eq_fun;
 return result;
}
static void entry_destroy (entry_t *head) {
 while (head != NULL)
 {
  entry_t *current = head;
  head = head->next;
  free(current);
 }
}
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) {
 for (int i = 0; i < No_Buckets; ++i) {
  entry_destroy(ht->buckets[i]);
 }
 free(ht);
 return;
}
static entry_t *find_previous_entry_for_key(entry_t *entry, elem_t key) {
 entry_t *next=entry->next;
 if (next==NULL)
 {
  return entry;
 }
 else
 {
  entry_t *cursor = entry;
  while (next != NULL)
  {
   if (next->key.i >= key.i) {
    return cursor;
   }
   cursor=cursor->next;
   next=next->next;
  }
  return cursor;
 }
}
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value)
{
 ///calculate the bucket for this entry
 int bucket = ht->hash_fun(key) % No_Buckets;
 ///search for an existing entry for a key
 entry_t *entry = find_previous_entry_for_key(ht->buckets[bucket], key);
 entry_t *next = entry->next;
 /// Check if the next entry should be updated or not
 if (next != NULL && ht->key_eq_fun(next->key,key))
 {
  next->value = value;
 }
 else
 {
  entry->next = entry_create(key, value, next);
  ht->size+=1;
 }
}
bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key, elem_t *result) {
 /// find the previous entry for key
 entry_t *tmp = find_previous_entry_for_key(ht->buckets[abs(ht->hash_fun(key)%No_Buckets)], key);
 entry_t *next = tmp->next;
 if (next && ht->key_eq_fun(next->key,key))
 {
  /// update result and return true
  *result = next->value;
  return true;
 }
 else
 {
  /// else return false
  return false;
 }
}
bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key, elem_t *result) {
 ///calculate the bucket for this entry
 int bucket = ht->hash_fun(key) % No_Buckets;
 ///search for an existing entry for a key
 entry_t *entry = find_previous_entry_for_key(ht->buckets[bucket], key);
 entry_t *next = entry->next;
 if (entry->next != NULL && ht->key_eq_fun(next->key,key)) 
 {
  *result = next->value;
  entry_t *new_next=next->next;
  entry->next = new_next;
  free(next);
  ht->size-=1;
  return true;
 }
 else
 {
  return false;
 }
}
size_t ioopm_hash_table_size(ioopm_hash_table_t *ht) {
 return ht->size;
}
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht) {
 return ht->size == 0;
}
void ioopm_hash_table_clear(ioopm_hash_table_t *ht)
{
 for (int i = 0; i < No_Buckets; ++i)
 {
  entry_t *head = ht->buckets[i]->next;
  while (head != NULL)
  {
   entry_t *current = head;
   head = head->next;
   free(current);
   ht->size -=1;
  }
 }
}

ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht) {
    int siz = ioopm_hash_table_size(ht);
    if (siz == 0) { return NULL; }

    ioopm_list_t *ls = ioopm_linked_list_create(compare_int_elements);
    for (int i=0; i<No_Buckets; i++) {
        entry_t *cursor = ht->buckets[i]->next;
        while (cursor != NULL) {
            ioopm_linked_list_append(ls, cursor->key);
            cursor = cursor->next;
        }
    }
    return ls;
}
ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht) {
    int siz = ioopm_hash_table_size(ht);
    if (siz == 0) return NULL;
    ioopm_list_t *ls = ioopm_linked_list_create( (ioopm_eq_function) compare_int_elements);
    for (int i=0; i<No_Buckets; i++) {
        entry_t *cursor = ht->buckets[i]->next;
        while (cursor != NULL) {
            ioopm_linked_list_append(ls, cursor->value);
            cursor = cursor->next;
        }
    }
    return ls;
}
bool key_equiv(elem_t key, elem_t value_ignored, void *x)
{
 elem_t *other_key_ptr = x;
 return compare_int_elements(key, *other_key_ptr);
}
bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate P, void *x);
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key)
{
 return ioopm_hash_table_any(ht, key_equiv, &key);
}
bool value_equiv(elem_t key, elem_t value, void *x) {
 elem_t *other_value = x;
 return strcmp(value.p, (*other_value).p)==0;
}
bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t v) {
 return ioopm_hash_table_any(ht, value_equiv, &v);
}
bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate P, void *x) {
    ioopm_list_t *keys = ioopm_hash_table_keys(ht);
    ioopm_list_t *values = ioopm_hash_table_values(ht);
    
    ioopm_link_t *cursor_key = keys->head->next;
    ioopm_link_t *cursor_value = values->head->next;
    bool result = true;
    for (int i=0; i<No_Buckets; i++) {
        result = P(cursor_key->value, cursor_value->value, x);
        cursor_key = cursor_key->next;
        cursor_value = cursor_value->next;
        if (result == false) {
            ioopm_linked_list_destroy(keys);
            ioopm_linked_list_destroy(values);
            free(values);
            return false;
        }
    }
    ioopm_linked_list_destroy(keys);
    ioopm_linked_list_destroy(values);
    free(values);
    return true;
}
// bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate P, void *x) {
//  int size = ioopm_hash_table_size(ht);
//  ioopm_list_t *keys = ioopm_hash_table_keys(ht);
//  char **values = ioopm_hash_table_values(ht);
//  bool result = true;
//  for (int i = 0; i < size; ++i)
//  {
//   result = P(keys[i], values[i], x);
//   if (result == false) {
//    free(values);
//    free(keys);
//    return false;
//   }
//  }
//  free(values);
//  free(keys);
//  return true;
// }
bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate P, void *x) {
    ioopm_list_t *keys = ioopm_hash_table_keys(ht);
    ioopm_list_t *values = ioopm_hash_table_values(ht);
    
    ioopm_link_t *cursor_key = keys->head->next;
    ioopm_link_t *cursor_value = values->head->next;
    bool result = true;
    for (int i=0; i<10; i++) {
        result = P(cursor_key->value, cursor_value->value, x);
        cursor_key = cursor_key->next;
        cursor_value = cursor_value->next;
        if (result == false) {
            ioopm_linked_list_destroy(keys);
            ioopm_linked_list_destroy(values);
            free(values);
            return true;
        }
    }
    ioopm_linked_list_destroy(keys);
    ioopm_linked_list_destroy(values);
    free(values);
    return false;
}
// bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate P, void *x) {
//  int size = ioopm_hash_table_size(ht);
//  int *keys = ioopm_hash_table_keys(ht);
//  char **values = ioopm_hash_table_values(ht);
//  bool result = false;
//  for (int i = 0; i < size; ++i)
//  {
//   result = P(keys[i], values[i], x);
//   if (result == true) {
//    free(values);
//    free(keys);
//    return true;
//   }
//  }
//  free(values);
//  free(keys);
//  return false;
// }
void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function f, void *x) {
 for (int i = 0; i < No_Buckets; ++i) {
  entry_t *current = ht->buckets[i]->next;
  while (current !=NULL) {
   f(current->key, &current->value, x);
   current = current->next;
  }
 }
}
