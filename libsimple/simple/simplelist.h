#ifndef __defined_simple_simplelist_h
#define __defined_simple_simplelist_h

#include <simple.h>

typedef struct slist * slist_t;

slist_t list_new();
slist_t list_append(slist_t l, void *o);

#endif // __defined_simple_simplelist_h
