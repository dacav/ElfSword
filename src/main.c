#include "elf_specification.h"
#include "elf.h"

#include <stdio.h>
#include <assert.h>

bool scanner (void *udata, elf_t elf, Elf32_Shdr *shdr)
{
    unsigned *counter = (unsigned *)udata;
    
    printf("Section id: %03d:\n", *counter);
    printf("    Name:  [%s]\n", elf_section_name(elf, shdr));
    printf("    Flags: [%c%c%c]\n\n", 
                    shdr->sh_flags & SHF_WRITE     ? 'w' : '-',
                    shdr->sh_flags & SHF_ALLOC     ? 'a' : '-',
                    shdr->sh_flags & SHF_EXECINSTR ? 'x' : '-');
    (*counter)++;
    return true;
}

int main(int argc, char **argv)
{
    elf_t elf;
    unsigned counter;
    Elf32_Shdr *sec;

    assert(argc > 1);
    counter = 0;
    elf = elf_map_file(argv[1]);
    assert(elf != NULL);
    if (elf_check_magic(elf)) {
        elf_sections_scan(elf, scanner, (void *)&counter);
        sec = elf_section_get(elf, ".bss");
        printf("\n\n.bss name is: %s\n", elf_section_name(elf, sec));
    } else
        printf("Invalid magic!\n");
    elf_release_file(elf);

    return 0;
}

