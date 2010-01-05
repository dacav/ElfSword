#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <elfsword.h>
#include <dacav.h>
#include <elf.h>

int main (int argc, char **argv)
{
    elf_t *elf;
    int n = 0;

    assert(elf_map_file(argv[0], &elf) == ELF_SUCCESS);
    diter_t *it = elf_dynrel_iter_new(elf);
    printf("Printout of .dynamic entries\n");
    while (diter_hasnext(it)) {
        Elf32_Dyn *dyn = (Elf32_Dyn *) diter_next(it);
        printf("\tEntry %d, d_tag=%p d_val=%d d_ptr=%p\n", n ++,
               (void *)dyn->d_tag, dyn->d_un.d_val,
               (void *)dyn->d_un.d_ptr);
    }
    elf_dynrel_iter_free(it);
    elf_release_file(elf);

    exit(0);
}

