#include <simple.h>
#include <assert.h>
#include <stdlib.h>

#include <stdio.h>

slist_t populate(int n)
{
    slist_t l = slist_new();
    int i;

    for (i = 0; i < n; i++) {
        l = slist_push(l, (void *)i);
    }

    return l;
}

void test_push_pop()
{
    slist_t l = populate(30);
    int i, j;

    j = 29;
    while (!slist_empty(l)) {
        l = slist_pop(l, (void **)&i);
        assert(i == j--);
    }

    slist_free(l, NULL);
}

void * check_slice(void *ud, void *val)
{
    int cmp = *(int *)ud;
    assert(cmp == (int)val);
    *(int *)ud = cmp - 1;
    return val;
}

void test_slice()
{
    slist_t l = populate(30);
    slist_t sl = slist_slice(l, 0, 1000);
    int j;

    j = 29;
    sl = slist_foreach(sl, check_slice, (void *)&j);
    slist_free(sl, NULL);
    slist_free(l, NULL);
}

int main(int argc, char ** argv)
{
    test_push_pop();
    test_slice();

    exit(0);
}

