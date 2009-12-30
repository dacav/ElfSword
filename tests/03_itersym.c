#include <assert.h>
#include <elfsword.h>
#include <stdio.h>
#include <dacav.h>

int main (int argc, char **argv)
{
    elf_t *elf;

    assert(elf_map_file(argv[0], &elf) == ELF_SUCCESS);

    diter_t *iter;
    iter = elf_symb_iter_new(elf);
    while (diter_hasnext(iter)) {
        elf_symb_desc_t *descr = (elf_symb_desc_t *) diter_next(iter);
        printf("Symbol name: '%s'\n", elf_symb_name(elf, descr));
    }
    elf_symb_iter_free(iter);
    exit(0);
}

