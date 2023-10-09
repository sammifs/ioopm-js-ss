#include "linked_list.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

static link_t *link_create(elem_t value, link_t *next) {
    link_t *link = calloc(1, sizeof(link_t));
    link->value = value;
    link->next = next;
    return link;
}

static void link_destroy(link_t *link) {
    free(link);
}

ioopm_list_t *ioopm_linked_list_create(ioopm_eq_function f) {

    ioopm_list_t *result =calloc(1, sizeof(struct list));
    result->head = NULL;
    result->last = NULL;
    result->size = 0;
    result->eq_fn = f;
    return result;
}

void ioopm_linked_list_destroy(ioopm_list_t *list) {
    assert(list);
    link_t *current = list->head;
    while (current != NULL) {
        link_t *tmp = current;
        current = current->next;
        link_destroy(tmp);
    }
    free(list);
}

void ioopm_linked_list_append(ioopm_list_t *list, elem_t value) {
    // list->last is allowed to be null (empty list) so we dont assert
    assert(list);
    if (ioopm_linked_list_is_empty(list)) {
        list->last = link_create(value, NULL);
        list->head = list->last;
        list->size++;
    }
    else {
        // If list isnt empty we make last element point to our new element
        // and make list->last our new element.
        list->last->next = link_create(value, NULL);
        list->last = list->last->next;
        list->size++;
    }
}

void ioopm_linked_list_prepend(ioopm_list_t *list, elem_t value) {
    // list->head is allowed to be null (empty list) so we dont assert
    assert(list);
    if (ioopm_linked_list_is_empty(list)) {
        list->head = link_create(value, NULL);
        list->last = list->head;
        list->size++;
    }
    else {
        list->head = link_create(value, list->head);
        list->size++;
    }
}

void ioopm_linked_list_insert(ioopm_list_t *list, int index, elem_t value, bool *success) {
    assert(list);
    if (index == 0) {
        ioopm_linked_list_prepend(list, value);
        *success = true;
        return;
    }
    else if (index == ioopm_linked_list_size(list)) {
        ioopm_linked_list_append(list,value);
        *success = true;
        return;
    }
    link_t *prev = list->head;
    if (prev == NULL) { 
        // If prev == NULL then index extends beyond
        // size of linked list. Throw error. Return.
        printf("\nInvalid index! - in ioopm_linked_list_insert\n");
        *success = false;
        return;
    }
    link_t *current = prev->next;
    // i=1 so that when loop is done current is 
    for (int i=1; i<index; i++) {
        if (current == NULL) {
            // If current == NULL then index extends beyond
            // size of linked list. Throw error. Return.
            printf("\nInvalid index! - in ioopm_linked_list_insert\n");
            *success = false;
            return;
        }
        prev = current;
        current = current->next;
    }
    prev->next = link_create(value, current);
    list->size++;
    *success = true;
}

static elem_t linked_list_remove_head(ioopm_list_t *list) {
    link_t *tmp = list->head;
    elem_t value = tmp->value;

    // If list size is 1 (we are removing the last element) tmp->next will be NULL.
    // So we only check if list->last needs to be NULL.
    list->head = tmp->next;
    if (ioopm_linked_list_size(list) == 1) { list->last = NULL; }
    link_destroy(tmp);
    list->size--;
    return value;
}
static elem_t linked_list_remove_last(ioopm_list_t *list) {
    link_t *last = list->last;
    elem_t value = last->value;
    link_t *cursor = list->head;

    while (cursor->next != last) {
        cursor = cursor->next;
    }
    cursor->next = NULL;

    // If list size is 2 (we are removing the second-to-last element), list->head and
    // list->last should point to same thing (last element).
    list->last = cursor;
    if (ioopm_linked_list_size(list) == 2) { list->head = list->last; }
    link_destroy(last);
    list->size--;
    return value;
}
elem_t ioopm_linked_list_remove(ioopm_list_t *list, int index, bool *success) {
    assert(list);
    assert(list->head);
    // If we are removing head
    if (index == 0) {
        elem_t value = linked_list_remove_head(list);
        *success = true;
        return value;
    }
    // If we are removing last
    else if (index == ioopm_linked_list_size(list)) {
        elem_t value = linked_list_remove_last(list);
        *success = true;
        return value;
    }

    // General case
    link_t *prev = list->head;
    link_t *current = prev->next;
    for (int i=1; i<index; i++) {
        if (current == NULL) { 
            // If current == NULL then index extends beyond
            // size of linked list. Throw error. Return 0.
            printf("\nInvalid index! - in ioopm_linked_list_remove\n");
            *success = false;
            return ptr_elem(NULL);
        }
        prev = current;
        current = current->next;
    }

    prev->next = current->next;
    elem_t value = current->value;
    link_destroy(current);
    list->size--;
    *success = true;
    return value;
}

elem_t ioopm_linked_list_get(ioopm_list_t *list, int index, bool *success) {
    assert(list);
    assert(list->head);
    link_t *current = list->head;
    for (int i=0; i < index; i++) {
        if (current == NULL) { 
            // If current NULL index is larger than linked_list size. Throw error. Return 0.
            printf("\nInvalid index! - in ioopm_linked_list_get\n");
            *success = false;
            return ptr_elem(NULL);
        }
        current = current->next;
    }
    *success = true;
    return current->value;
}

bool ioopm_linked_list_contains(ioopm_list_t *list, elem_t element) {
    assert(list);
    assert(list->eq_fn);
    for (link_t *cursor = list->head; cursor; cursor = cursor->next) {
        if (list->eq_fn(cursor->value, element)) return true;
    }

    return false;
}

size_t ioopm_linked_list_size(ioopm_list_t *list) {
    assert(list);
    return list->size;
}

bool ioopm_linked_list_is_empty(ioopm_list_t *list) {
    return ioopm_linked_list_size(list) == 0;
}

void ioopm_linked_list_clear(ioopm_list_t *list) {
    assert(list);
    // If list is empty do nothing.
    if (ioopm_linked_list_is_empty(list)) { return; }
    link_t *current = list->head;
    while (current != NULL) {
        link_t *tmp = current;
        current = current->next;
        link_destroy(tmp);
        list->size--;
    }
    list->head = NULL;
    list->last = NULL;
}

bool ioopm_linked_list_all(ioopm_list_t *list, ioopm_predicate prop, void *extra) {
    assert(list);
    // Empty list is always false.
    if (ioopm_linked_list_is_empty(list)) { return false; }
    link_t *cursor = list->head;
    bool result = true;
    while (cursor != NULL && result) {
        result = prop(ptr_elem(NULL), cursor->value, extra);
        cursor = cursor->next;
    }
    return result;
}

bool ioopm_linked_list_any(ioopm_list_t *list, ioopm_predicate prop, void *extra) {
    assert(list);
    // Empty list is always false.
    if (ioopm_linked_list_is_empty(list)) { return false; }
    link_t *cursor = list->head;
    bool result = false;
    while (cursor != NULL && !result) {
        result = prop(ptr_elem(NULL), cursor->value, extra);
        cursor = cursor->next;
    }
    return result;
}

void ioopm_linked_list_apply_to_all(ioopm_list_t *list, ioopm_apply_function fun, void *extra) {
    assert(list);
    // If list is empty do nothing.
    if (ioopm_linked_list_is_empty(list)) { return; }
    link_t *cursor = list->head;
    while (cursor != NULL) {
        fun(ptr_elem(NULL), &cursor->value, extra);
        cursor = cursor->next;
    }
}

ioopm_list_iterator_t *ioopm_list_iterator(ioopm_list_t *list) {
    assert(list);
    ioopm_list_iterator_t *iter = calloc(1, sizeof(ioopm_list_iterator_t));

    // MAYBE ??
    ioopm_linked_list_prepend(list, ptr_elem(NULL));

    iter->current = list->head;
    iter->list = list;
    return iter;
}