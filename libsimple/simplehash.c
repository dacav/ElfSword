#include <simplehash.h>

#include <string.h>
#include <assert.h>
#include <stdlib.h>

struct elem {
    void *object;
    struct elem *next;
};

struct bucket {
    unsigned nelem;
    struct elem *first;
};

struct hash {
    unsigned nbuckets;
    struct bucket *buckets;    
};

void hash_new(hash_t *htab, unsigned nbuckets)
{
    size_t total;
    void *chunk;
    hash_t table;
    void *bks;
   
    total = sizeof(struct hash) + nbuckets * sizeof(struct bucket);
    assert(chunk = malloc(total));
    *htab = table = (hash_t) chunk;
    table->buckets = bks = (struct bucket *)
                           (((char *)chunk) + sizeof(struct hash));
    memset(bks, 0, sizeof(struct bucket) * nbuckets);
}

void hash_free(hash_t htab)
{
    int i;
    struct elem *cur, *tmp;
    struct bucket *bks = htab->buckets;

    for (i = 0; i < htab->nbuckets; i ++) {
        cur = bks[i].first;
        while (cur) {
            tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
}

