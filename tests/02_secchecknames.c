#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <elfsword.h>
#include <dacav.h>

int main (int argc, char **argv)
{
    elf_t *elf;

    assert(elf_map_file(argv[0], &elf) == ELF_SUCCESS);

    diter_t *iter;
    iter = elf_sect_iter_new(elf, SHT_NULL);
    Elf32_Shdr *gotbyname;
    while (diter_hasnext(iter)) {
        Elf32_Shdr *hdr = (Elf32_Shdr *) diter_next(iter);
        const char *name = elf_sect_name(elf, hdr);
        assert(elf_sect_get(elf, name, &gotbyname) == ELF_SUCCESS);
        assert(gotbyname == hdr);
    }
    elf_sect_iter_free(iter);
    elf_release_file(elf);
    exit(0);
}

