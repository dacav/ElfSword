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
    hash_t ht;

    assert(ht = hash_new(hash, 1, cmp, NULL, NULL));
    hash_insert(ht, (const void *)"Hello", (const void *)100);
    hash_insert(ht, (const void *)"Hi there", (const void *)200);
    assert((int)hash_search(ht, (void *)"Hello") == 100);
    hash_free(ht);

    exit(0);
}

