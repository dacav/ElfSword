#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <elfsword.h>
#include <dacav.h>

int main (int argc, char **argv)
{
    elf_t *me;
    dhash_t *table;
    int count;

    assert(elf_map_file(argv[0], &me) == ELF_SUCCESS);
    assert(elf_sect_get_hash(me, &table) == ELF_SUCCESS);

    diter_t *iter = dhash_iter_new(table);
    count = -1;
    while (diter_hasnext(iter)) {
        dhash_pair_t *pair = (dhash_pair_t *) diter_next(iter);
        //printf("name='%s' address=%p\n",
        //       (const char *) dhash_key(pair), dhash_val(pair));
        count ++;
    }
    dhash_iter_free(iter);

    Elf32_Shdr *sh;
    assert(elf_sect_seek(me, count, &sh) == ELF_SUCCESS);
    assert(elf_sect_seek(me, count + 1, &sh) == ELF_NOSECTION);

    elf_release_file(me);
    exit(0);
}

