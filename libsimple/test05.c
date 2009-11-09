#include <simple.h>
#include <assert.h>
#include <stdlib.h>

#include <stdio.h>

// check ordering (see main)
void *check0(void *ud, void *val)
{
    int n = (int)val;
    int test = *(int *)ud;

    if (test % 2) {
        assert(test == n);
    } else {
        assert(test == -n);
    }
    if (test == 1) {
        test = 0;
    } else {
        test -= 2;
    }
    *((int *)ud) = test;
    return val;
}

// return 1 if the value is even
int even(void *ud, void *val)
{
    return (((int)val) % 2) == 0;
}

// used in filter, cancels everything
int nothing(void *ud, void *val)
{
    return 0;
}

// check the value to be even
void *check1(void *ud, void *val)
{
    assert((int)val % 2 == 0);
    return val;
}

// fails
void *check2(void *ud, void *val)
{
    exit(1);    // this should never be called
}

int main(int argc, char ** argv)
{
    slist_t l = slist_new();
    int i, test;

    for (i = 0; i < 30; i++) {

        // something like:
        // 29 ... 5 3 1 0 2 4 6 ... 30

        if (i % 2) {
            l = slist_push(l, (void *)i);
        } else {
            l = slist_append(l, (void *)i);
        }
    }
    test = 29;

    // checks the correct ordering
    l = slist_foreach(l, check0, (void *)&test);

    // filters odd values (the first block, from 29 to 1)
    l = slist_filter(l, even, (void *)&test);

    // checks the presence of even values only
    l = slist_foreach(l, check1, NULL);

    // removes all values
    l = slist_filter(l, nothing, NULL);

    // now the list should be empty, so we can run check2 without getting
    // program failure.
    l = slist_foreach(l, check2, NULL);

    // ...and the list should be simply NULL
    assert(l == NULL);
    slist_free(l, NULL);

    exit(0);
}
