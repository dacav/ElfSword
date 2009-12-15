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

/** @file elf.h
 *
 * This module allows to extract pieces of information from an ELF file.
 */

#ifndef __defined_elfsword_elfmap_h
#define __defined_elfsword_elfmap_h

#include <stdbool.h>
#include <stdlib.h>
#include <elfsword.h>

#ifdef __cplusplus
extern "C" {
#endif

/** ELF file mapper.
 *
 * Maps the given ELF file in memory.
 *
 * @param filename The name of the ELF file to be mapped;
 * @param elf A pointer to the area where the map address will be stored;
 * @return ELF_SUCCESS on success, something else on error.
 * @see 
 */
elf_err_t elf_map_file (const char *filename, elf_t **elf);

/** ELF file releaser
 *
 * Frees the elf_t * object.
 *
 * @param elf The elf_t * object to be freed.
 */
void elf_release_file (elf_t * elf);

#ifdef __cplusplus
}
#endif

#endif // __defined_elfsword_elfmap_h
