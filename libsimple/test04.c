#include <simple.h>
#include <assert.h>
#include <stdlib.h>

#include <stdio.h>

int even(void *ud, void *val)
{
    int n = (int)val;
    return (n % 2) == 0;
}

void *check(void *ud, void *val)
{
    int n0 = (int)val;
    int n1 = *((int *)ud);
    assert(n0 == n1);
    *((int *)ud) = n1 - 2;
    return val;
}

void run_test(unsigned n)
{
    slist_t list;
    int cval = n - 1;

    list = slist_new();
    while (n--) {
        list = slist_append(list, (void *)n);
    }
    list = slist_filter(list, even, NULL);
    slist_foreach(list, check, (void *)&cval);
    slist_free(list, NULL);

    exit(0);
}

int main(int argc, char ** argv)
{
    run_test(0);    // with empty list
    run_test(1);    // one single values
    run_test(30);   // long run
}
