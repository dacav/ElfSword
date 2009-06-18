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
                 struct RelocData *rd)
{
    int n;

    n = *((int *)udata);
    printf("rel elem %02d: Section %s\n", n, sname);
    *((int *)udata) = n + 1;

    return true;
}

int main(int argc, char **argv)
{
    Elf elf;
    int n = 0;

    assert(argc > 1);
    elf = elf_map_file(argv[1]);
    assert(elf != NULL);
    printf("The ELF file is %swell formed\n",
           elf_check_format(elf) ? "" : "not ");

    elf_relocation_scan(elf, rel_scanner, (void *)&n);

    elf_release_file(elf);

    return 0;
}

