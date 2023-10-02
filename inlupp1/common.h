#pragma once

#define int_elem(x) (elem_t) { .i=(x) }
#define ptr_elem(x) (elem_t) { .p=(x) }

typedef union elem elem_t;

union elem
{
  /// TODO: update the names of the fields to something better? 
  int i;
  unsigned int u;
  bool b;
  float f;
  void *p;
  /// other choices certainly possible
};

struct link
{
    elem_t value;
    struct link *next;
};
typedef struct link ioopm_link_t;

typedef bool(*ioopm_eq_function)(elem_t a, elem_t b);
// The list contains a pointer to its first link, and its size
struct list
{
    ioopm_link_t *head;
    int size;
    ioopm_eq_function eq_fn;
};

typedef struct list ioopm_list_t; /// Meta: struct definition goes in C file
typedef bool (*ioopm_predicate)(elem_t key, elem_t value, void *extra);
typedef void (*ioopm_apply_function)(elem_t key, elem_t *value, void *extra);