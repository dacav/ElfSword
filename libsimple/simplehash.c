#include <simple.h>

#include <string.h>
#include <assert.h>
#include <stdlib.h>

struct elem {
    void *key;
    void *value;

    struct elem *next;
};

struct bucket {
    unsigned nelem;
    struct elem *first;
};

struct hash {
    unsigned nbuckets;
    struct bucket *buckets;    
    hash_func_t hash_func;          // key hashing function
    cmp_func_t cmp_func;            // key comparing function
    free_mem_t val_free;            // object freeing function
    free_mem_t key_free;            // keys freeing function
};

hash_t hash_new(hash_func_t hf, unsigned nbuckets, cmp_func_t cp,
                free_mem_t key_free, free_mem_t val_free)
{
    size_t total;
    void *chunk;
    hash_t table;
    void *bks;

    if (nbuckets == 0)
        return NULL;
   
    total = sizeof(struct hash) + nbuckets * sizeof(struct bucket);
    assert(chunk = malloc(total));
    table = (hash_t) chunk;
    table->buckets = bks = (struct bucket *)
                           (((char *)chunk) + sizeof(struct hash));
    table->hash_func = hf;
    table->cmp_func = cp;
    table->val_free = val_free;
    table->key_free = key_free;
    table->nbuckets = nbuckets;
    memset(bks, 0, sizeof(struct bucket) * nbuckets);

	return table;
}

void hash_free(hash_t htab)
{
    int i;
    struct elem *cur, *tmp;
    struct bucket *bks = htab->buckets;
    free_mem_t val_free = htab->val_free,
               key_free = htab->key_free;

    for (i = 0; i < htab->nbuckets; i ++) {
        cur = bks[i].first;
        while (cur) {
            tmp = cur;
            cur = cur->next;

            // free element
            if (val_free != NULL) val_free(tmp->value);
            if (key_free != NULL) key_free(tmp->key);
            free(tmp);
        }
    }
}

static inline
struct bucket * get_bucket(hash_t htab, const void *key)
{
    int hv = htab->hash_func(key) % htab->nbuckets; 
    return htab->buckets + hv;
}

void hash_insert(hash_t htab, const void *key, const void *value)
{
    struct bucket *bkt = get_bucket(htab, key);
    struct elem *new_entry;

    assert(new_entry = malloc(sizeof(struct elem)));
    new_entry->next = bkt->first;
    bkt->first = new_entry;
    bkt->nelem ++;

    new_entry->key = (void *)key;
    new_entry->value = (void *)value;
}

void *hash_search(hash_t htab, const void *key)
{
    struct bucket *bkt = get_bucket(htab, key);
    struct elem *cursor = bkt->first;
    cmp_func_t compare = htab->cmp_func;

    while (cursor) {
        if (compare(cursor->key, key) == 0) {
            return (void *)cursor->value;
        }
        cursor = cursor->next;
    }
    return NULL;
}

