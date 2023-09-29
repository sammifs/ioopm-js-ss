#include "iterator.h"
#include <stdlib.h>

ioopm_list_iterator_t *ioopm_list_iterator(ioopm_list_t *list) {
    ioopm_list_iterator_t *result = malloc(sizeof(ioopm_list_iterator_t));

    result->current = list->head;

    result->list = list;

    return result;
}

bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter) {
    return iter->current->next != NULL;
}

int ioopm_iterator_next(ioopm_list_iterator_t *iter) {
    iter->current = iter->current->next;

    return iter->current->value;
}

int ioopm_iterator_remove(ioopm_list_iterator_t *iter) {
 ioopm_link_t *to_remove = iter->current->next;
 iter->current->next=to_remove->next;
 int value = to_remove->value;
 free(to_remove);
 return value;
}

void ioopm_iterator_reset(ioopm_list_iterator_t *iter) {
    iter->current = iter->list->head;
}

int ioopm_iterator_current(ioopm_list_iterator_t *iter) {
    return iter->current->next->value;
}

void ioopm_iterator_destroy(ioopm_list_iterator_t *iter) {
    free(iter);
}
