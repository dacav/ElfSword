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

const char *types[] = {
    "None",
    "Object",
    "Function",
    "Section",
    "File", 
};

bool symscanner(void *udata, elf_t elf, Elf32_Shdr *shdr, Elf32_Sym *yhdr)
{
    unsigned *counter, c;
    unsigned t;
   
    counter = (unsigned *)udata;
    c = *counter;
    (*counter)++;

    if (c == 0)
        printf("    Symbols dump:\n");
    t = ELF32_ST_TYPE(yhdr->st_info);
    printf("        Symbol %03d type: %s(%d)\n", c, types[t], t);

    printf("                    name: %s\n", elf_symbol_name(elf, shdr, yhdr));
    
    return true;
}

bool scanner(void *udata, elf_t elf, Elf32_Shdr *shdr)
{
    unsigned *counter = (unsigned *)udata;
    unsigned sycnt = 0;
    
    printf("Section id: %03d:\n", *counter);
    printf("    Name:  [%s]\n", elf_section_name(elf, shdr));
    printf("    Flags: [%c%c%c]\n\n", 
                    shdr->sh_flags & SHF_WRITE     ? 'w' : '-',
                    shdr->sh_flags & SHF_ALLOC     ? 'a' : '-',
                    shdr->sh_flags & SHF_EXECINSTR ? 'x' : '-');
    elf_symbols_scan(elf, shdr, symscanner, (void *)&sycnt);
    (*counter)++;
    return true;
}

int main(int argc, char **argv)
{
    elf_t elf;
    unsigned counter;

    assert(argc > 1);
    counter = 0;
    elf = elf_map_file(argv[1]);
    assert(elf != NULL);
    elf_sections_scan(elf, scanner, (void *)&counter);
    elf_release_file(elf);

    return 0;
}

