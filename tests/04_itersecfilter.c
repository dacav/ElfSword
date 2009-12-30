#include <stdio.h>
#include <elfsword.h>
#include <dacav.h>
#include <elf.h>
#include <assert.h>

unsigned count_filter (elf_t *descr, Elf32_Word sh_type)
{
    unsigned cnt = 0;

    diter_t *iter = elf_sect_iter_new(descr, sh_type);
    while (diter_hasnext(iter)) {
        diter_next(iter);
        cnt ++;
    }
    elf_sect_iter_free(iter);

    return cnt;
}

int main (int argc, char **argv)
{
    elf_t *descr;
    int i, n;

    assert(elf_map_file(argv[0], &descr) == ELF_SUCCESS);

    /*
     * Numbers from 0 to 11 are mapped to section types. 0 is the type of
     * the section indexed with 0, so libelfsword treats it as dummy
     * filter. Therefore n will contain the total number of sections.
     */
    n = count_filter(descr, SHT_NULL);

    /* We subtract the number of sections for each section type */
    for (i = 1; i <= 11; i ++) {
        n -= count_filter(descr, i);
    }

    /*
     * We expect to end up with only four sections, which are the SHT_NULL
     * one and the three ".gnu*" ones.
     *
     * Unfortunately I can assert this to be true only for my specific
     * architecture/compiler, therefore this test may fail on other
     * contexts.
     */
    assert(n == 4);
    exit(0);
}
