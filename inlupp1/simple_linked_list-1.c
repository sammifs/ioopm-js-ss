#include "linked_list.h"
#include "iterator.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * @file simple_linked_list.c
 * @author Elias Castegren
 * @date 1 Sep 2021
 * @brief A simple linked list that implements parts of the interface
 * of `linked_list.h`. The functions that are not implemented will fail
 * at runtime with an assertion error, printing a message to stderr.
 */

// This is a macro that is used in the functions that are not implemented,
// to have them fail at runtime. You do not have to understand it to use
// this file!
#define NOT_SUPPORTED()                                                            \
    do                                                                             \
    {                                                                              \
        fprintf(stderr, "The simple linked list does not support %s\n", __func__); \
        assert(false);                                                             \
    } while (0)

// The links of the linked list
ioopm_link_t *link_create(elem_t value, ioopm_link_t *next)
{
    ioopm_link_t *link = calloc(1, sizeof(ioopm_link_t));
    link->value = value;
    link->next = next;
    return link;
}
ioopm_list_t *ioopm_linked_list_create(ioopm_eq_function f)
{
    ioopm_list_t *result = calloc(1, sizeof(struct list));
    result->head=link_create(int_elem(0), NULL);
    
    result->size=0;
    result->eq_fn=f;
    return result;
}

void ioopm_linked_list_destroy(ioopm_list_t *list)
{
    assert(list);
    ioopm_link_t *current = list->head;
    while (current)
    {
        ioopm_link_t *tmp = current;
        current = current->next;
        free(tmp);
    }
current=NULL;
    free(list);
}
//bool ioopm_linked_list_is_empty(ioopm_linked_list_t *ht);
void ioopm_linked_list_append(ioopm_list_t *list, elem_t value)
{
if(ioopm_linked_list_is_empty(list)) {
 list->head->next=link_create(value, NULL);
 list->last=list->head->next;
}
else {
 list->last->next=link_create(value, NULL);
 list->last=list->last->next;
}
 list->size+=1;
}
void ioopm_linked_list_prepend(ioopm_list_t *list, elem_t value)
{
    assert(list);
    ioopm_link_t *first = list->head->next;
    list->head->next = link_create(value, first);
    list->size++;
}
void ioopm_linked_list_insert(ioopm_list_t *list, int index, elem_t value)
{
 if (index == 0)
 {
  ioopm_linked_list_prepend(list, value);
  return;
 }
 if (index == list->size)
 {
  ioopm_linked_list_append(list, value);
  return;
 }
 if (index >0 && index < list->size)
 {
  ioopm_link_t *prev= list->head->next; //initialy the element with index 0
  ioopm_link_t *current = prev->next; //the next element
  for (int i = 1; i < index; ++i)
  {
   prev = prev->next;
   current= current->next;
  }
  // current now points to the element with index index
  prev->next = link_create(value, current);
  list->size++;
  return;
 }
 else
 {
  printf("Index out of range\n");
  return;
 }
}

elem_t ioopm_linked_list_remove(ioopm_list_t *list, int index)
{
 assert(list);
 assert(list->head->next);
 elem_t value;
 if (index == 0)
 {
  ioopm_link_t *tmp = list->head->next;
  list->head->next = tmp->next;
  value = tmp->value;
  free(tmp);
  list->size--;
  return value;
}

    // index > 0
    assert(list->head->next->next);
   ioopm_link_t *prev = list->head->next;
   ioopm_link_t *current = prev->next;
    for (int i = 1; i < index; i++)
    {
        assert(current);
        prev = current;
        current = current->next;
    }
    //prev->next = current->next;
if(index==list->size) {
 list->last=prev;
}
	value = current->value;
    free(current);
    list->size--;
return value;
}

elem_t ioopm_linked_list_get(ioopm_list_t *list, int index)
{
    assert(list);
    assert(list->head->next);
    ioopm_link_t *current = list->head->next;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
        assert(current);
    }
    return current->value;
}

bool ioopm_linked_list_contains(ioopm_list_t *list, elem_t element)
{
    assert(list);
    ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
    
    while (ioopm_iterator_has_next(iter))
    {
        elem_t cursor = ioopm_iterator_current(iter);
        if(list->eq_fn(cursor, element))
        {
            return true;
        }
        ioopm_iterator_next(iter);
    }
    return false;
}
size_t ioopm_linked_list_size(ioopm_list_t *list)
{
    assert(list);
    return list->size;
}
bool ioopm_linked_list_is_empty(ioopm_list_t *list)
{
 return ioopm_linked_list_size(list) == 0;
}

void ioopm_linked_list_clear(ioopm_list_t *list)
{
    assert(list);
    int init_siz=list->size;
    for (int i = 0; i < init_siz; ++i)
    {
        ioopm_linked_list_remove(list, 0);
    }
}
bool ioopm_linked_list_all(ioopm_list_t *list, ioopm_predicate prop, void *extra)
{
 ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
 bool result = true;
 while (ioopm_iterator_has_next(iter) && result) {
  elem_t current = ioopm_iterator_current(iter);
  result = prop(int_elem(0), current, extra);
  ioopm_iterator_next(iter);
 }
 ioopm_iterator_destroy(iter);
 return result;
}
bool ioopm_linked_list_any(ioopm_list_t *list, ioopm_predicate prop, void *extra)
{
 ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
 bool result = false;
 while (ioopm_iterator_has_next(iter) && !result) {
  elem_t current = ioopm_iterator_current(iter);
  result = prop(int_elem(0), current, extra);
  ioopm_iterator_next(iter);
 }
 ioopm_iterator_destroy(iter);
 return result;
}
void ioopm_linked_list_apply_to_all(ioopm_list_t *list, ioopm_apply_function fun, void *extra)
{
 ioopm_link_t * current = list->head->next;
 for (int i = 0; i < list->size; ++i) {
  fun(int_elem(i), &current->value, extra);
  current = current->next;
 }
}
