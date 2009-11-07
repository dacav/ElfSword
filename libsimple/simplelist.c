#include <simple.h>

#include <stdlib.h>
#include <assert.h>

struct slist {
    void *object;
    struct slist *next;
    struct slist *prev;
};

slist_t slist_new()
{
    return NULL;
}

slist_t slist_append(slist_t l, void *o)
{
    slist_t n;

    assert(n = malloc(sizeof(struct slist)));
    if (l == NULL) {    // Empty list
        n->next = n->prev = n;
        n->object = o;
        return n;
    } else {
        n->next = l;
        n->prev = l->prev;
        l->prev->next = n;
        l->prev = n;
    }
}
