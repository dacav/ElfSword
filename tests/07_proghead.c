#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <elfsword.h>
#include <dacav.h>

int main (int argc, char **argv)
{
    elf_t *elf;
    int n = 0;

    assert(elf_map_file(argv[0], &elf) == ELF_SUCCESS);
    diter_t *it = elf_proghead_iter_new(elf);
    printf("Printout of PROGHEAD entries\n");
    while (diter_hasnext(it)) {
        Elf32_Phdr *ph = (Elf32_Phdr *) diter_next(it);
        printf("\tEntry %d, virtual=%p\n", n ++, (void *)(ph->p_vaddr));
    }
    elf_proghead_iter_free(it);
    elf_release_file(elf);

    exit(0);
}

