#include "common.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
bool compare_values(elem_t a, elem_t b) {
 return strcmp(a.p, b.p) ==0;
}
bool compare_int_elements(elem_t a, elem_t b) {
    return b.i - a.i == 0;
}
