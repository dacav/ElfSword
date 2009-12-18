#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <elfsword.h>
#include <dacav.h>

int main (int argc, char **argv)
{
    elf_t *me;
    assert(elf_map_file(argv[0], &me) == ELF_SUCCESS);

    dhash_t *table = elf_sect_get_hash(me);
    diter_t *iter = dhash_iter_new(table);
    while (diter_hasnext(iter)) {
        dhash_pair_t *pair = (dhash_pair_t *) diter_next(iter);
        printf("name='%s' address=%p\n",
               (const char *) dhash_key(pair), dhash_val(pair));
    }
    dhash_iter_free(table);

    exit(0);
}

