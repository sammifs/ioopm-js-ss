#include "hash_table.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define No_Buckets 17

typedef struct entry entry_t;
struct entry
{
 int key;  // holds the key
 char *value; //holds the value
 entry_t *next; // points to the next entry
};
struct hash_table
{
 entry_t *buckets[No_Buckets];
int size;
};
static entry_t *entry_create(int key, char *value, entry_t *next) {
 entry_t *entr = calloc(1, sizeof(entry_t));
 entr->key=key;
 entr->value=value;
 entr->next=next;
 return entr;
}
ioopm_hash_table_t *ioopm_hash_table_create(void) 
{
 ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
 for (int i = 0; i < No_Buckets; ++i) {
  result->buckets[i]=entry_create(0, NULL, NULL);
 }
 result->size=0;
 return result;
}
static entry_t *find_previous_entry_for_key(entry_t *entry, int key);
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
static entry_t *find_previous_entry_for_key(entry_t *entry, int key) {
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
 int bucket = key % No_Buckets;
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
  ht->size+=1;
 }
}
bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key, char **result) {
 /// find the previous entry for key
 entry_t *tmp = find_previous_entry_for_key(ht->buckets[abs(key%No_Buckets)], key);
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
bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key, char **result) {
 ///calculate the bucket for this entry
 int bucket = key % No_Buckets;
 ///search for an existing entry for a key
 entry_t *entry = find_previous_entry_for_key(ht->buckets[bucket], key);
 entry_t *next = entry->next;
 if (entry->next != NULL && next->key == key) 
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
int ioopm_hash_table_size(ioopm_hash_table_t *ht) {
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
int *ioopm_hash_table_keys(ioopm_hash_table_t *ht) {
 int siz = ioopm_hash_table_size(ht);
 int *result=calloc(siz+1, sizeof(int));
 int index=0;
 for (int i = 0; i < No_Buckets; ++i) 
 {
  entry_t *cursor = ht->buckets[i]->next;
  while (cursor != NULL)
  {
   result[index] = cursor->key;
   index +=1;
   cursor = cursor->next;
  }
 }
 return result;
}
char **ioopm_hash_table_values(ioopm_hash_table_t *ht) {
 int siz = ioopm_hash_table_size(ht);
 char **result=calloc(siz+1, 64*sizeof(char));
 int index=0;
 for (int i = 0; i < No_Buckets; ++i) 
 {
  entry_t *cursor = ht->buckets[i]->next;
  while (cursor != NULL)
  {
   result[index] = cursor->value;
   index +=1;
   cursor = cursor->next;
  }
 }
 result[index]='\0';
 return result;
}
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, int key) {
char *result = NULL;
return ioopm_hash_table_lookup(ht, key, &result);
}
