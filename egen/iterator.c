#include "iterator.h"
#include <stdlib.h>
#include <assert.h>

bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter) {
  if (iter->current == NULL) { return false; }
  return iter->current->next != NULL;
}

elem_t ioopm_iterator_next(ioopm_list_iterator_t *iter) {
  assert(iter->current);
  assert(iter->current->next);
  iter->current = iter->current->next;
  return iter->current->value;
}

void ioopm_iterator_reset(ioopm_list_iterator_t *iter) {
  iter->current = iter->list->head;
}

elem_t ioopm_iterator_current(ioopm_list_iterator_t *iter) {
  return iter->current->value;
}

void ioopm_iterator_destroy(ioopm_list_iterator_t *iter) {
  free(iter);
}