#include <assert.h>
#include <elfsword.h>
#include <stdio.h>
#include <dacav.h>
#include <elf.h>

static
int count (elf_t *elf, Elf32_Word section)
{
    diter_t *iter;
    int n = 0;
    iter = elf_symb_iter_new(elf, section);
    while (diter_hasnext(iter)) {
        diter_next(iter);
        n ++;
    }
    elf_symb_iter_free(iter);
    return n;
}

int main (int argc, char **argv)
{
    elf_t *elf;
    int n = 0;

    assert(elf_map_file(argv[0], &elf) == ELF_SUCCESS);
    n += count(elf, SHT_NULL);
    n -= count(elf, SHT_SYMTAB);
    n -= count(elf, SHT_DYNSYM);
    elf_release_file(elf);
    assert(n == 0);

    exit(0);
}

