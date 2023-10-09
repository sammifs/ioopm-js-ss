#pragma once

#include <stdlib.h>

union elem
{
  int i;
  void *p;
};

typedef union elem elem_t;

#define int_elem(x) (elem_t) { .i=(x) }
#define ptr_elem(x) (elem_t) { .p=(x) }

typedef bool(*ioopm_eq_function)(elem_t a, elem_t b);
typedef bool(*ioopm_predicate)(elem_t key, elem_t value, void *extra);
typedef void(*ioopm_apply_function)(elem_t key, elem_t *value, void *extra);

struct link {
    elem_t value;
    struct link *next;
};

typedef struct link link_t;

struct list {
    link_t *head;
    link_t *last;
    size_t size;
    ioopm_eq_function eq_fn;
};

typedef struct list ioopm_list_t; 

struct iter 
{
  link_t *current;
  ioopm_list_t *list; 
};

typedef struct iter ioopm_list_iterator_t;