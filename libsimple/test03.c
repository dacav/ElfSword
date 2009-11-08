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

void run_test(unsigned nbuckets, unsigned nkeys)
{
    shash_t ht;
    int value, i;
    char *key;

    // Create the hash table
    assert(ht = shash_new(nbuckets, hash, cmp));

    // Insert hello plus a lot of similar garbage
    shash_insert(ht, build_str("Hello"), (const void *)100);
    key = (char *)build_str("My name is foo");
    for (i = 0; i < nkeys; i++) {
        key[4] ++;  // successive modification of the key
        shash_insert(ht, key, (const void *)i);
        key = (char *)build_str(key);
    }
    free(key);

    // Find "Hello"
    assert(shash_search(ht, (const void *)"Hello",
                        (void *)&value) == SHASH_FOUND);
    assert(value == 100);
    // Delete "Hello"
    assert(shash_delete(ht, (const void *)"Hello", NULL) == SHASH_FOUND);
    assert(value == 100);
    // Check deletion
    assert(shash_search(ht, (const void *)"Hello",
                        (void *)&value) == SHASH_NOTFOUND);

    // Check correct existance of other keys
    key = (char *)build_str("My name is foo");
    for (i = 0; i < nkeys; i++) {
        key[4] ++;
        // Other keys must exist
        assert(shash_search(ht, (const void *)key, (void *)&value)
               == SHASH_FOUND);
        assert(value == i); // and value must be correct
    }
    free(key);
    shash_free(ht, free, NULL);
}

int main(int argc, char **argv)
{
    unsigned m, n = 10;
    while (--n) {
        m = 50;
        while (--m) {
            run_test(n, m);
        }
    }
    exit(0);
}

