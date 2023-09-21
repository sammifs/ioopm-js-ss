#pragma once
#include <stdbool.h>
#include <stdlib.h>
#define No_Buckets 17
/**
 * @file hash_table.h
 * @author Johannes Segersten, Samuel Sverker
 * @date september 17 2023
 * @brief simple hash table that maps integer keys to string values
 */
typedef struct hash_table ioopm_hash_table_t;
/// @brief Create a new hash table
/// @return a new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create(void);
/// @brief delete a hash table and free its memory
/// @param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);
/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value);
/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key the key to lookup
/// @param result ** a pointer to a char * that is updated upon success
/// @return bool true if key maps to a value, false otherwise
bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key, char **result);
/// @Brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @param result uppdated with the removed value if key was removed successfully
/// @return true if key was removed successfully, false otherwise
bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key, char **result);
/// @brief returns the number of key => value entries in the hash table
/// @param h hash table operated upon
/// @return the number of key=> value entries in the hash table
int ioopm_hash_table_size(ioopm_hash_table_t *ht);
/// @brief checks if the hash table is empty
/// @param h hash table operated upon
/// @return true if size == 0, else false
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);
///@brief clear all the entries in a hash table

/// @param h hash table operated upon
void ioopm_hash_table_clear(ioopm_hash_table_t *ht);
/// @brief return all the keys for all entries in a hash map (in no particular order, but same as ioopm_hash_table_values)
/// @param h hash table operated upon
/// @return an array of keys for hash table h
int *ioopm_hash_table_keys(ioopm_hash_table_t *ht);
/// @brief return the values for all entries in a hash map (in no particular order, but same as ioopm_hash_table_keys)
/// @param h hash table operated upon
/// @return an NULL terminated array of values for hash table h
char **ioopm_hash_table_values(ioopm_hash_table_t *ht);
/// @brief check if a hash table has an entry with a given key
/// @param h hash table operated upon
/// @param key the key sought
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, int key);
/// @brief check if a hash table has an entry with a given value
/// @param h hash table operated upon
/// @param value the value sought
bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, char *value);
/// @brief check if a predicate is satisfied by all entries in a hash table
/// @param h hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred
///bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg);
/// @brief check if a predicate is satisfied by any entry in a hash table
/// @param h hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred
//bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg);
/// @brief apply a function to all entries in a hash table
/// @param h hash table operated upon
/// @param apply_fun the function to be applied to all elements
/// @param arg extra argument to apply_fun
//void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function apply_fun, void *arg);
