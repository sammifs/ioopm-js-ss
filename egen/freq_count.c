#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table.h"
#include "linked_list.h"
#include "common.h"
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
    bool success;
    int freq = ioopm_hash_table_has_key(ht, ptr_elem(word)) ? (ioopm_hash_table_lookup(ht, ptr_elem(word), &success)).i : 0;
    ioopm_hash_table_insert(ht, (elem_t){.p = strdup(word)}, (elem_t){.i = freq + 1});
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
    } while (*++str != '\0');
    return result;
}
bool string_eq(elem_t e1, elem_t e2)
{
    return (strcmp(e1.p, e2.p) == 0);
}
int main(int argc, char *argv[])
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create((ioopm_hash_function)
                                                         string_sum_hash,
                                                     string_eq, string_eq);
    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
        {
            process_file(argv[i], ht);
        }
        // FIXME: If the keys are returned as a list, transfer them into
        // an array to use `sort_keys` (perhaps using an iterator?)
        ioopm_list_t *ls = ioopm_hash_table_keys(ht);
        ioopm_list_iterator_t *iter = ioopm_list_iterator(ls);
        int size = ioopm_hash_table_size(ht);
        char *keys[size];
        for (int i=0; ioopm_iterator_has_next(iter); i++) {
            keys[i] = ioopm_iterator_next(iter).p;
        }
        ioopm_iterator_destroy(iter);
        ioopm_linked_list_destroy(ls);
        sort_keys(keys, size);
        for (int i = 0; i < size; ++i)
        {
            // FIXME: Update to match your own interface, error handling, etc.
            bool success;
            int freq = (ioopm_hash_table_lookup(ht, (elem_t){.p = keys[i]}, &success)).i;
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