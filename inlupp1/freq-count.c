#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table.h"
#include "linked_list.h"
#include "common.h"
#include "iterator.h"

#define Delimiters "+-#@()[]{}.,:;!? \t\n\r"

static int cmpstringp(const void *p1, const void *p2)
{
  return strcmp(*(char *const *)p1, *(char *const *)p2);
}

void sort_keys(char *keys[], size_t no_keys)
{
  qsort(keys, no_keys, sizeof(char *), cmpstringp);
}

void process_word(char *word, ioopm_hash_table_t *ht)
{
  // FIXME: Rewrite to match your own interface, error-handling, etc.
  elem_t result;
  int freq =
  ioopm_hash_table_lookup(ht, (elem_t) {.p = word}, &result) ? result.i : 0;
  ioopm_hash_table_insert(ht, (elem_t) {.p = strdup(word)}, (elem_t) {.i = freq + 1});
}

void process_file(char *filename, ioopm_hash_table_t *ht)
{
  FILE *f = fopen(filename, "r");

  while (true)
  {
    char *buf = NULL;
    size_t len = 0;
    getline(&buf, &len, f);

    if (feof(f))
    {
      free(buf);
      break;
    }

    for (char *word = strtok(buf, Delimiters);
         word && *word;
         word = strtok(NULL, Delimiters))
    {
      process_word(word, ht);
    }

    free(buf);
  }

  fclose(f);
}

int string_sum_hash(elem_t e)
{
  char *str = e.p;
  int result = 0;
  do
    {
      result += *str;
    }
  while (*++str != '\0');
  return result;
}

bool string_eq(elem_t e1, elem_t e2)
{
  return (strcmp(e1.p, e2.p) == 0);
}

int main(int argc, char *argv[])
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create((ioopm_hash_function) string_sum_hash, string_eq);

  if (argc > 1)
  {
    for (int i = 1; i < argc; ++i)
    {
      process_file(argv[i], ht);
    }

    ioopm_list_t *keys_ll = ioopm_hash_table_keys(ht);
    ioopm_list_iterator_t *iter = ioopm_list_iterator(keys_ll);
    char **keys = calloc(ioopm_linked_list_size(keys_ll), sizeof(elem_t));
    int index=0;
    while (ioopm_iterator_has_next(iter)) {
     elem_t current = ioopm_iterator_current(iter);
     keys[index ] = (char *) current.p;
     ioopm_iterator_next(iter);
     index+=1;
    }

    int size = ioopm_hash_table_size(ht);
    sort_keys(keys, size);

    for (int i = 0; i < size; ++i)
    {
      elem_t result = int_elem(0);
      ioopm_hash_table_lookup(ht, (elem_t) {.p = keys[i]}, &result);
      int freq = result.i;
      printf("%s: %d\n", keys[i], freq);
    }
  }
  else
  {
    puts("Usage: freq-count file1 ... filen");
  }

  // FIXME: Leaks memory! Use valgrind to find out where that memory is 
  // being allocated, and then insert code here to free it.
  ioopm_hash_table_destroy(ht);
}

