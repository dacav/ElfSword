#include <assert.h>
#include <elfsword.h>
#include <stdio.h>
#include <dacav.h>
#include <elf.h>

int main (int argc, char **argv)
{
    elf_t *elf;

    assert(elf_map_file(argv[0], &elf) == ELF_SUCCESS);

    diter_t *iter;
    iter = elf_symb_iter_new(elf, SHT_NULL);
    printf("Printout of symbols\n");
    while (diter_hasnext(iter)) {
        elf_symb_desc_t *descr = (elf_symb_desc_t *) diter_next(iter);
        printf("\tSymbol name: '%s'\n", elf_symb_name(elf, descr));
    }
    elf_symb_iter_free(iter);
    elf_release_file(elf);
    exit(0);
}

