#pragma once
#include <stdbool.h>
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
    int size;
    ioopm_eq_function eq_fn;
};
bool compare_int_elements(elem_t a, elem_t b);
bool compare_values(elem_t a, elem_t b);
typedef struct list ioopm_list_t;
