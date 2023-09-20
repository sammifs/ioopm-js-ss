#include "hash_table.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
typedef struct entry entry_t;
struct entry
{
 int key;  // holds the key
 char *value; //holds the value
 entry_t *next; // points to the next entry
};
struct hash_table
{
 entry_t *buckets[17];
};
entry_t *entry_create(int key, char *value, entry_t *next) {
 entry_t *entr = calloc(1, sizeof(entry_t));
 entr->key=key;
 entr->value=value;
 entr->next=next;
 return entr;
}
ioopm_hash_table_t *ioopm_hash_table_create(void) 
{
 ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
 for (int i = 0; i < 17; ++i) {
  result->buckets[i]=entry_create(0, NULL, NULL);
 }
 return result;
}
entry_t *find_previous_entry_for_key(entry_t *entry, int key);
void entry_destroy (entry_t *head) {
 while (head != NULL)
 {
  entry_t *current = head;
  head = head->next;
  free(current);
 }
}
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) {
 for (int i = 0; i < 17; ++i) {
  entry_destroy(ht->buckets[i]);
 }
 free(ht);
 return;
}
entry_t *find_previous_entry_for_key(entry_t *entry, int key) {
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
   if (next->key >= key) {
    return cursor;
   }
   cursor=cursor->next;
   next=next->next;
  }
  return cursor;
 }
}
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value)
{
 ///calculate the bucket for this entry
 int bucket = key % 17;
 ///search for an existing entry for a key
 entry_t *entry = find_previous_entry_for_key(ht->buckets[bucket], key);
 entry_t *next = entry->next;
 /// Check if the next entry should be updated or not
 if (next != NULL && next->key == key )
 {
  next->value = value;
 }
 else
 {
  entry->next = entry_create(key, value, next);
 }
}
bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key, char **result) {
 /// find the previous entry for key
 entry_t *tmp = find_previous_entry_for_key(ht->buckets[abs(key%17)], key);
 entry_t *next = tmp->next;
 if (next && next->key==key)
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
