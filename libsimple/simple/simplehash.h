#ifndef __defined_simple_hash_h
#define __defined_simple_hash_h

#include <simple.h>

typedef struct hash *hash_t;

typedef int (*hash_func_t) (const void *key);
typedef int (*cmp_func_t) (const void *v0, const void *v1);

hash_t hash_new(hash_func_t hf, cmp_func_t cp, unsigned nbuckets);
void hash_free(hash_t htab);
void hash_insert(hash_t htab, const void *key, const void *value);
void *hash_search(hash_t htab, const void *key);

#endif // __defined_simple_hash_h
