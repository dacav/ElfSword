#include <simple.h>

#include <string.h>
#include <assert.h>
#include <stdlib.h>

// For debug purpose
#include <stdio.h>

struct elem {
    void *key;
    void *value;

    struct elem *next;
};

struct bucket {
    struct elem *first;
};

struct shash {
    unsigned nbuckets;
    struct bucket *buckets;    
    shash_func_t shash_func;          // key hashing function
    scmp_func_t cmp_func;             // key comparing function
};

shash_t shash_new(unsigned nbuckets, shash_func_t hf, scmp_func_t cp)
{
    size_t total;
    void *chunk;
    shash_t table;
    void *bks;

    if (nbuckets == 0)
        return NULL;
   
    total = sizeof(struct shash) + nbuckets * sizeof(struct bucket);
    assert(chunk = malloc(total));
    table = (shash_t) chunk;
    table->buckets = bks = (struct bucket *)
                           (((char *)chunk) + sizeof(struct shash));
    table->shash_func = hf;
    table->cmp_func = cp;
    table->nbuckets = nbuckets;
    memset(bks, 0, sizeof(struct bucket) * nbuckets);

	return table;
}

void shash_free(shash_t htab, sfree_mem_t key_free, sfree_mem_t val_free)
{
    int i;
    struct elem *cur, *tmp;
    struct bucket *bks = htab->buckets;

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
    free(htab);
}

static inline
struct bucket * get_bucket(shash_t htab, const void *key)
{
    int hv = htab->shash_func(key) % htab->nbuckets; 
    return htab->buckets + hv;
}

void shash_insert(shash_t htab, const void *key, const void *value)
{
    struct bucket *bkt = get_bucket(htab, key);
    scmp_func_t compare = htab->cmp_func;
    struct elem *cursor;

    cursor = bkt->first;
    while (cursor) {
        if (compare(cursor->key, key) == 0) {
            cursor->value = (void *)value;
            return;
        }
        cursor = cursor->next;
    }
    assert(cursor = malloc(sizeof(struct elem)));
    cursor->next = bkt->first;
    bkt->first = cursor;
    cursor->key = (void *)key;
    cursor->value = (void *)value;
}

int shash_search(shash_t htab, const void *key, void **found)
{
    struct bucket *bkt = get_bucket(htab, key);
    struct elem *cursor = bkt->first;
    scmp_func_t compare = htab->cmp_func;

    while (cursor) {
        if (compare(cursor->key, key) == 0) {
            *found = (void *)cursor->value;
            return SHASH_FOUND;
        }
        cursor = cursor->next;
    }
    return SHASH_NOTFOUND;
}

int shash_delete(shash_t htab, const void *key, void **found)
{
    struct bucket *bkt = get_bucket(htab, key);
    if (bkt->first == NULL)
        return SHASH_NOTFOUND;
    scmp_func_t compare = htab->cmp_func;
    struct elem *cursor = bkt->first;
    struct elem **prev = &bkt->first;
    while (cursor) {
        if (compare(cursor->key, key) == 0) {
            (*prev) = cursor->next;
            if (found != NULL) {
                *found = cursor->value;
            }
            free(cursor);
            return SHASH_FOUND;
        }
        cursor = cursor->next;
        prev = &((*prev)->next);
    }
    return SHASH_NOTFOUND;
}

