#pragma once
#include <stdbool.h>

/**
 * @file common.h
 * @author Johannes Segersten, Samuel Sverker
 * @date 12 Okt 2021
 * @brief Common utils for the inlupp1 project. Shared structs and definitions.
 */

#define int_elem(x) (elem_t) {.i = (x) }
#define ptr_elem(x) (elem_t) {.p = (x) }
typedef union elem elem_t;
union elem
{
int i;
unsigned int u;
bool b;
float f;
void *p;
};
typedef bool (*ioopm_predicate)(elem_t key, elem_t value, void *extra);
typedef void (ioopm_apply_function)(elem_t key, elem_t *value, void *extra);
/// compares two elements and returns true if they are equal
typedef bool(*ioopm_eq_function)(elem_t a, elem_t b);
struct link
{
    elem_t value;
    struct link *next;
};
typedef struct link ioopm_link_t;
// The list contains a pointer to its first link, and its size
struct list
{
    ioopm_link_t *head;
    ioopm_link_t *last;
    int size;
    ioopm_eq_function eq_fn;
};

/// @brief Compares two elem_t with i fields
/// @param a elem_t
/// @param b elem_t
/// @return true if a's i field is equal to b's i field, false otherwise
bool compare_int_elements(elem_t a, elem_t b);

/// @brief Compares two elem_t with string inside p field
/// @param a elem_t
/// @param b elem_t
/// @return true if string in a's p field is equal to string in b's p field, false otherwise
bool compare_values(elem_t a, elem_t b);


typedef struct list ioopm_list_t;
