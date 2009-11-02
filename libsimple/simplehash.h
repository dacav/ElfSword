#ifndef __SIMPLE_HASH_H__
#define __SIMPLE_HASH_H__

typedef struct hash *hash_t;

void hash_new(hash_t *htab, unsigned nbuckets);
void hash_free(hash_t htab);

#endif /* __SIMPLE_HASH_H__ */
