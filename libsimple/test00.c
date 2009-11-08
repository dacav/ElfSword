#include <simple.h>

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

static int hash(const void *val)
{
    const char *str = (const char *)val;
    int ret = 0;
    while (*str) {
        ret >>= 1;
        ret += *str++;
    }
    return ret;
}

static int cmp(const void *v0, const void *v1)
{
    return strcmp((const char *)v0, (const char *)v1);
}

int main(int argc, char **argv)
{
    shash_t ht;
    int result;

    assert(ht = shash_new(1, hash, cmp));
    shash_insert(ht, (const void *)"Hello", (const void *)100);
    shash_insert(ht, (const void *)"Hi there", (const void *)200);
    assert(shash_search(ht, (void *)"Hello", (void **)&result)
           == SHASH_FOUND);
    assert(result == 100);
    shash_free(ht, NULL, NULL);

    exit(0);
}

