#ifndef __defined_simple_hash_h
#define __defined_simple_hash_h

#include <simple.h>

#define SHASH_FOUND 0
#define SHASH_NOTFOUND 1

typedef struct hash *hash_t;

typedef int (*hash_func_t) (const void *key);
typedef int (*cmp_func_t) (const void *v0, const void *v1);

hash_t hash_new(hash_func_t hf, unsigned nbuckets, cmp_func_t cp,
                free_mem_t key_free, free_mem_t val_free);
void hash_free(hash_t htab);
void hash_insert(hash_t htab, const void *key, const void *value);
int hash_search(hash_t htab, const void *key, void **found);

#endif // __defined_simple_hash_h
