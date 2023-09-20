#pragma once
#include <stdbool.h>
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
