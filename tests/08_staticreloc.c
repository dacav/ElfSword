#include <stdio.h>
#include <elfsword.h>
#include <dacav.h>
#include <assert.h>

int main (int argc, char **argv)
{
    elf_t *elf;

    assert(elf_map_file(argv[0], &elf) == ELF_SUCCESS);

    diter_t *iter;
    Elf32_Shdr *section, *target;
    Elf32_Rela rela;
    elf_symb_desc_t symbol;

    int n = 0;
    iter = elf_statrel_iter_new(elf);
    while (diter_hasnext(iter)) {
        printf("Reloc entry %d\n", n ++);
        elf_statrel_t *descr = (elf_statrel_t *) diter_next(iter);

        elf_statrel_section(descr, &section);
        elf_statrel_target(descr, &target);
        elf_statrel_rela(descr, &rela);
        elf_statrel_symbol(descr, &symbol);

        printf("\tSections: name='%s' target='%s'\n",
               elf_sect_name(elf, section),
               elf_sect_name(elf, target));
        printf("\tReloc: r_offset=%p r_info=%p r_addend=%p\n",
               (void *)rela.r_offset, (void *)rela.r_info,
               (void *)rela.r_addend);
        printf("\tCorresponding symbol: name='%s'\n",
               elf_symb_name(elf, &symbol));
    }
    elf_statrel_iter_free(iter);
    elf_release_file(elf);
    exit(0);
}
