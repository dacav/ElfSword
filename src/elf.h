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
#ifndef __ELF_H__
#define __ELF_H__

#include <stdbool.h>
#include "elf_specification.h"

typedef struct elf_struct * elf_t;

elf_t           elf_map_file        (const char *filename);
bool            elf_check_magic     (elf_t elf);
bool            elf_release_file    (elf_t elf);

const char *    elf_section_name    (elf_t elf, Elf32_Shdr *shdr);
Elf32_Shdr *    elf_section_get     (elf_t elf, const char *secname);

/* shdr is the symbol section, used for sh_link field */
const char *    elf_symbol_name     (elf_t elf, Elf32_Shdr *shdr, Elf32_Sym *yhdr);

/* Iteration function.
 * If the return value is true the iteration will be stopped */
typedef bool (*sec_scan_t)(void *udata, elf_t elf, Elf32_Shdr *shdr);
typedef bool (*sym_scan_t)(void *udata, elf_t elf, Elf32_Shdr *shdr, Elf32_Sym *yhdr);

void            elf_sections_scan   (elf_t elf, sec_scan_t callback, void *udata);;

/* cycle through the symbols of a section */
void            elf_symbols_scan    (elf_t elf, Elf32_Shdr *shdr,
                                     sym_scan_t callback, void *udata);

#endif /* __ELF_H__ */
