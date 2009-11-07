#include <simple.h>

#include <stdlib.h>
#include <assert.h>
#include <string.h>

static
int hash(const void *val)
{
    if (val == NULL) {
        return 0;
    } else {
        const char *str = (const char *)val;
        int ret = 0;
        while (*str) {
            ret >>= 1;
            ret += *str++;
        }
        return ret;
    }
}

static
int cmp(const void *v0, const void *v1)
{
    if (v0 == NULL) {
        if (v1 == NULL) {
            return 0;
        }
    } else {
        return strcmp((const char *)v0, (const char *)v1);
    }
}

static
const void *build_str(const char *s)
{
    char *ret;

    if (s == NULL) {
        return NULL;
    }
    size_t len = strlen(s) + 1;

    assert(ret = malloc(len));
    memcpy((void *)ret, (void *)s, len);
    return (const void *)ret;
}

static
void add(shash_t ht, const char *k, const char *v)
{
    const void *v1 = (const void *)build_str(k),
               *v2 = (const void *)build_str(v);

    shash_insert(ht, v1, v2);
}

int main(int argc, char **argv)
{
    shash_t ht;
    int value, i;
    char *key;

    assert(ht = shash_new(hash, 2, cmp, free, NULL));
    shash_insert(ht, build_str("Hello"), (const void *)100);
    for (i = 0; i < 20; i++) {
        key = (char *)build_str("My name is foo\n");
        key[4] ++;
        shash_insert(ht, key, (const void *)i);
    }
    assert(shash_search(ht, (const void *)"Hello",
                            (void *)&value) == SHASH_FOUND);
    assert(value == 100);
    assert(shash_delete(ht, (const void *)"Hello",
                            (void *)&value) == SHASH_FOUND);
    assert(value == 100);
    assert(shash_search(ht, (const void *)"Hello",
                            (void *)&value) == SHASH_NOTFOUND);
    shash_free(ht);

    exit(0);
}
