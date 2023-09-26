#include "linked_list.h"
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
struct link
{
    int value;
    struct link *next;
};

typedef struct link link_t;

link_t *link_create(int value, link_t *next)
{
    link_t *link = calloc(1, sizeof(link_t));
    link->value = value;
    link->next = next;
    return link;
}

// The list contains a pointer to its first link, and its size
struct list
{
    link_t *head;
    int size;
};

ioopm_list_t *ioopm_linked_list_create()
{
    ioopm_list_t *result = calloc(1, sizeof(struct list));
    result->head=NULL;
    result->size=0;
    return result;
}

void ioopm_linked_list_destroy(ioopm_list_t *list)
{
    assert(list);
    link_t *current = list->head;
    while (current)
    {
        link_t *tmp = current;
        current = current->next;
        free(tmp);
    }
    free(list);
}

void ioopm_linked_list_append(ioopm_list_t *list, int value)
{
 if (ioopm_linked_list_is_empty(list))
 {
  list->head = link_create(value, NULL);
 }
 else 
 {
  link_t *current = list->head;
  while (current->next != NULL)
  {
   current = current->next;
  }
  current->next=link_create(value, NULL);
 }
 list->size++;
}
void ioopm_linked_list_prepend(ioopm_list_t *list, int value)
{
    assert(list);
    list->head = link_create(value, list->head);
    list->size++;
}
void ioopm_linked_list_insert(ioopm_list_t *list, int index, int value)
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
  link_t *prev= list->head;
  link_t *current = prev->next;
  for (int i = 1; i < index; ++i)
  {
   prev = prev->next;
   current= current->next;
  }
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

int ioopm_linked_list_remove(ioopm_list_t *list, int index)
{
    assert(list);
    assert(list->head);

    if (index == 0)
    {
        link_t *tmp = list->head;
        int value = tmp->value;
        list->head = tmp->next;
        free(tmp);
        list->size--;
        return value;
    }

    // index > 0
    assert(list->head);
    link_t *prev = list->head;
    link_t *current = prev->next;
    for (int i = 1; i < index; i++)
    {
        assert(current);
        prev = current;
        current = current->next;
    }

    prev->next = current->next;
    int value = current->value;
    free(current);
    list->size--;
    return value;
}

int ioopm_linked_list_get(ioopm_list_t *list, int index)
{
    assert(list);
    assert(list->head);
    link_t *current = list->head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
        assert(current);
    }
    return current->value;
}

bool ioopm_linked_list_contains(ioopm_list_t *list, int element)
{
    assert(list);
    link_t *cursor = list->head;
    while (cursor)
    {
        if(cursor->value == element)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

int ioopm_linked_list_size(ioopm_list_t *list)
{
    assert(list);
    return list->size;
}

bool ioopm_linked_list_is_empty(ioopm_list_t *list)
{
 return ioopm_linked_list_size(list) ==0;
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
bool ioopm_linked_list_all(ioopm_list_t *list, ioopm_int_predicate prop, void *extra)
{
 link_t * current = list->head;
 for (int i = 0; i < list->size; ++i) {
  if (prop(i, current->value, extra) == false)
  {
   return false;
  }
  current=current->next;
 }
 return true;
}
bool ioopm_linked_list_any(ioopm_list_t *list, ioopm_int_predicate prop, void *extra)
{
 link_t * current = list->head;
 for (int i = 0; i < list->size; ++i) {
  if (prop(i, current->value, extra))
  {
   return true;
  }
  current=current->next;
 }
 return false;
}
void ioopm_linked_list_apply_to_all(ioopm_list_t *list, ioopm_apply_int_function fun, void *extra)
{
 link_t * current = list->head;
 for (int i = 0; i < list->size; ++i) {
  fun(i, &current->value, extra);
  current = current->next;
 }
}
