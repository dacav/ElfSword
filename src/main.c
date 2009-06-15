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

bool scan(void *udata, Elf elf, Elf32_Phdr *hdr)
{
    int32_t *cnt = (int32_t *)udata;
    const uint8_t *interp;
    int32_t permission;
    
    permission = hdr->p_flags;
    printf(" %3d | %9p | %4d (%4d) | %9p | %c%c%c |",
           (*cnt)++,
           (void *)hdr->p_vaddr,
           hdr->p_memsz,
           hdr->p_filesz,
           (void *)((int32_t)hdr->p_vaddr + hdr->p_memsz),
           permission & PF_R ? 'r' : '-',
           permission & PF_W ? 'w' : '-',
           permission & PF_X ? 'x' : '-');
    if (hdr->p_type == PT_INTERP) {
        interp = elf_get_content(elf) + hdr->p_offset;
        printf(" [interpreter: %s]", interp);
    }
    putchar(10);
    return true;
}

int main(int argc, char **argv)
{
    Elf elf;
    int32_t cnt = 0;

    assert(argc > 1);
    elf = elf_map_file(argv[1]);
    assert(elf != NULL);
    printf(" #   | VMA       | SIZE        | END       | PER | INTERP\n"
           "-----+-----------+-------------+-----------+-----+-------\n");
    if (!elf_progheader_scan(elf, scan, (void *)&cnt)) {
        printf("No.\n");
    }
    printf("PTR SYM: %p\n", elf_symbol_get(elf, "mmap"));
    printf("The ELF file is %swell formed\n",
           elf_check_format(elf) ? "" : "not ");
    elf_release_file(elf);

    return 0;
}

