#include <assert.h>
#include <elfsword.h>
#include <stdio.h>
#include <dacav.h>
#include <elf.h>

static
void compare (elf_t *elf, elf_symb_desc_t *s0, elf_symb_desc_t *s1)
{
    const char *n0 = elf_symb_name(elf, s0);
    const char *n1 = elf_symb_name(elf, s1);
    if (n0 == NULL) assert(n1 == NULL);
    else assert(strcmp(n0, n1) == 0);
}

static
void check (elf_t *elf, Elf32_Word section)
{
    diter_t *iter;
    unsigned n = 0;
    elf_symb_desc_t desc;
    elf_symb_desc_t *fromiter;

    iter = elf_symb_iter_new(elf, section);
    while (diter_hasnext(iter)) {
        fromiter = (elf_symb_desc_t *) diter_next(iter);
        assert(elf_symb_seek(elf, section, n, &desc) == ELF_SUCCESS);
        n ++;
        compare(elf, fromiter, &desc);
    }
    assert(elf_symb_seek(elf, section, n + 1, &desc) == ELF_NOSYMBOL);
    elf_symb_iter_free(iter);
}

int main (int argc, char **argv)
{
    elf_t *elf;

    assert(elf_map_file(argv[0], &elf) == ELF_SUCCESS);
    check(elf, SHT_SYMTAB);
    check(elf, SHT_DYNSYM);
    elf_release_file(elf);

    exit(0);
}

