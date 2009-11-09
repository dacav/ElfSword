#ifndef __defined_simple_simplelist_h
#define __defined_simple_simplelist_h

#include <simple.h>

typedef struct slist * slist_t;

slist_t slist_new();

slist_t slist_append(slist_t l, void *o);
slist_t slist_push(slist_t l, void *o);

slist_t slist_foreach(slist_t l, siter_t f, void *ud);
slist_t slist_filter(slist_t l, sfilter_t f, void *ud);

void slist_free(slist_t l, sfree_mem_t f);

#endif // __defined_simple_simplelist_h
