#include <simple.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    slist_t l = slist_new();

    slist_append(l, (void *)1);
    slist_append(l, (void *)2);
    slist_append(l, (void *)3);

    exit(0);
}

