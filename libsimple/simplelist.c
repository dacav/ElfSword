#include <simple.h>

#include <stdlib.h>
#include <assert.h>

#include <stdio.h>

struct slist {
    void *object;
    struct slist *next;
    struct slist *prev;
};

slist_t slist_new()
{
    return NULL;
}

void slist_delete(slist_t l, sfree_mem_t f)
{
    slist_t e;

    l->prev->next = NULL;
    while (l) {
        e = l;
        l = l->next;
        if (f != NULL) {
            f(e->object);
        }
        free(e);
    }
}

slist_t slist_append(slist_t l, void *o)
{
    slist_t n;

    assert(n = malloc(sizeof(struct slist)));
    n->object = o;
    if (l == NULL) {    // Empty list
        n->next = n->prev = n;
        return n;
    } else {
        n->next = l;
        n->prev = l->prev;
        l->prev->next = n;
        l->prev = n;
        return l;
    }
}

void slist_map(slist_t l, siter_t f, void *ud)
{
    slist_t cur;

    if (l == NULL) return;
    cur = l;
    do {
        cur->object = f(ud, cur->object);
        cur = cur->next;
    } while (cur != l);
}

