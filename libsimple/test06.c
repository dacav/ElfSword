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

void test_slice()
{
    slist_t l = populate(0);


    slist_free(l, NULL);
}

int main(int argc, char ** argv)
{
    test_push_pop();
    test_slice();

    exit(0);
}

