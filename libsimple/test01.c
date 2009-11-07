#include <simple.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
const char *build_str(const char *s)
{
    char *ret;

    if (s == NULL) {
        return NULL;
    }
    size_t len = strlen(s) + 1;

    assert(ret = malloc(len));
    memcpy((void *)ret, (void *)s, len);
    return ret;
}

static
void add(hash_t ht, const char *k, const char *v)
{
    const void *v1 = (const void *)build_str(k),
               *v2 = (const void *)build_str(v);

    hash_insert(ht, v1, v2);
}

static const char *messages[] = {
    "Hello", "World", "My name", "Is John", NULL
};

int main(int argc, char **argv)
{
    hash_t ht;
    const char **msg;

    // build hash table
    assert(ht = hash_new(hash, 4, cmp, free, free));

    // insert messages
    msg = messages;
    while (*msg) {
        const char *s1 = *msg++,
                   *s2 = *msg;
        add(ht, s1, s2);
    }

    // check corrispondence
    int i;
    for (i = 0; i < 4; i ++) {
        const char *key = messages[i];
        const char *good_value = messages[i+1];
        char *value;
        assert(hash_search(ht, (const void *)key, (void **)&value)
               == SHASH_FOUND);
        assert(((value == NULL) && (good_value == NULL))
               || strcmp(value, messages[i+1]) == 0);
    }
    hash_free(ht);

    exit(0);
}

