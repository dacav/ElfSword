/*
 * Copyright 2009 Giovanni Simoni
 *
 * This file is part of ElfSword.
 *
 * ElfSword is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ElfSword is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ElfSword.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include "elf_specification.h"
#include "elf.h"

#include <stdio.h>
#include <assert.h>

bool rel_scanner(void *udata, Elf elf, const char *sname,
                 struct RelocData *rd, Elf32_Shdr *symtab,
                 Elf32_Shdr *toapply)
{
    int n;
    int offset = ELF32_R_SYM(rd->data.rel->r_info);

    n = *((int *)udata);
    *((int *)udata) = n + 1;

    printf("%03d) name: %s\n", n, sname);
    printf("\tSymbol table required: %s\n", elf_section_name(elf, symtab));
    if (rd->sh_type == SHT_REL) {
        printf("\tThe section %s must be modified at offset %u\n",
               elf_section_name(elf, toapply),
               rd->data.rel->r_offset);
    } else {
        printf("\tThe virtual address to be modified is %p\n",
               (void *)(rd->data.rela->r_offset + rd->data.rela->r_addend));
    }
    printf("\tCorresponding symbol has name \"%s\"\n",
           elf_symbol_name(elf, symtab,
                           elf_symbol_seek(elf, symtab->sh_type, offset))
          );
    putchar(10);

    return true;
}

int main(int argc, char **argv)
{
    Elf elf;
    int n = 0;

    assert(argc > 1);
    elf = elf_map_file(argv[1]);
    assert(elf != NULL);
    elf_relocation_scan(elf, rel_scanner, (void *)&n);
    elf_release_file(elf);

    return 0;
}

