#include <elfsword.h>
#include <elf.h>

#include "descriptor.h"

#include <stdio.h>

bool elf_check_magic(elf_t * elf)
{
    unsigned char *magic;

    magic = elf->file.header->e_ident;
    bool ret = magic[EI_MAG0] == ELFMAG0 &&
           magic[EI_MAG1] == ELFMAG1 &&
           magic[EI_MAG2] == ELFMAG2 &&
           magic[EI_MAG3] == ELFMAG3;
    return ret;
}


