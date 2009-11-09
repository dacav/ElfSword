#include <simple.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void * times2(void *ud, void *obj)
{
    int val = (int)obj;
    return (void *)(2 * val);
}

void * test(void *ud, void *obj)
{
    int current = *((int *)ud);
    int read = (int)obj;
    assert(2 * current == read);
    *((int *)ud) = current + 1;
    return obj;
}

int main(int argc, char **argv)
{
    slist_t l = slist_new();
    int n = 1;

    l = slist_append(l, (void *)1);
    l = slist_append(l, (void *)2);
    l = slist_append(l, (void *)3);

    slist_foreach(l, times2, NULL);
    slist_foreach(l, test, (void *)&n);
    slist_free(l, NULL);

    exit(0);
}

