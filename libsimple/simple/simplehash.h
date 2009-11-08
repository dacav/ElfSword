#ifndef __defined_simple_simpleshash_h
#define __defined_simple_simpleshash_h

#include <simple.h>

#define SHASH_FOUND 0
#define SHASH_NOTFOUND 1

typedef struct shash *shash_t;

typedef int (*shash_func_t) (const void *key);
typedef int (*scmp_func_t) (const void *v0, const void *v1);

shash_t shash_new(unsigned nbuckets, shash_func_t hf, scmp_func_t cp);
void shash_free(shash_t htab, sfree_mem_t key_free, sfree_mem_t val_free);
void shash_insert(shash_t htab, const void *key, const void *value);
int shash_search(shash_t htab, const void *key, void **found);
int shash_delete(shash_t htab, const void *key, void **found);

#endif // __defined_simple_shash_h
