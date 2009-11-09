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

static
slist_t join_elem(slist_t l, slist_t n)
{
    if (l == NULL) {
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

static
slist_t new_elem(void *o)
{
    slist_t n;

    assert(n = malloc(sizeof(struct slist)));
    n->object = o;
    return n;
}

slist_t slist_append(slist_t l, void *o)
{
    slist_t n = new_elem(o);
    l = join_elem(l, n);
    return l;
}

slist_t slist_push(slist_t l, void *o)
{
    slist_t n = new_elem(o);
    l = join_elem(l, n);
    return n;
}

slist_t slist_foreach(slist_t l, siter_t f, void *ud)
{
    slist_t cur;

    if (l == NULL) return NULL;
    cur = l;
    do {
        cur->object = f(ud, cur->object);
        cur = cur->next;
    } while (cur != l);
    return l;
}

slist_t slist_filter(slist_t l, sfilter_t f, void *ud)
{
    slist_t ret, cur, tmp;

    if (l == NULL) return NULL;
    l->prev->next = ret = NULL;
    cur = l;
    do {
        tmp = cur;
        cur = cur->next;
        if (f(ud, tmp->object)) {
            ret = join_elem(ret, tmp);
        } else {
            free(tmp);
        }
    } while (cur);

    return ret;
}

void slist_free(slist_t l, sfree_mem_t f)
{
    slist_t e;

    if (l == NULL) return;
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

