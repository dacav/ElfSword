#ifndef __defined_simple_simplelist_h
#define __defined_simple_simplelist_h

#include <simple.h>

typedef struct slist * slist_t;

slist_t slist_new();
slist_t slist_append(slist_t l, void *o);
void slist_map(slist_t l, siter_t f, void *ud);

typedef struct slist_iter * slist_iter_t;


#endif // __defined_simple_simplelist_h
