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

/** @file sections.h
 *
 * ELF sections management routines.
 */

#ifndef __defined_elfsword_sections_h
#define __defined_elfsword_sections_h

#include <elfsword.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ELF_SYMHASH_SIZE 40
#define ELF_SECHASH_SIZE 20

/** Build a libdacav iterator on sections.
 *
 * Iteration will be achieved only among sections whose type matches the
 * one given as second parameter.
 *
 * @param elf The ELF object descriptor;
 * @param sh_type Matching type: by providing SHT_NULL filtering will be
 *                disabled;
 * @return An iterator among ELF object's sections.
 */
diter_t *elf_sect_iter_new (elf_t *elf, Elf32_Word sh_type);

/** Free the given sections iterator.
 *
 * @param iter The iterator to be freed.
 */
void elf_sect_iter_free (diter_t *iter);

/** Get the hash table for section names.
 *
 * @param elf The ELF object descriptor.
 * @return The hash table if the object file has a string table, NULL
 *         otherwise.
 */
dhash_t *elf_sect_get_hash (elf_t *elf);

/** Get the required section header
 *
 * @param elf The ELF object descriptor;
 * @param index The index of the required section;
 * @return A pointer to the section, or NULL if there's no such section.
 */
Elf32_Shdr *elf_sect_seek (elf_t *elf, unsigned index);

/** Get the required section name.
 *
 * @param elf The ELF object descriptor;
 * @param sec The section whose name must be read or NULL;
 * @return The name of the given section, or the starting address of the
 *         section names table if NULL is given as second parameter.
 */
const char *elf_sect_name (elf_t *elf, Elf32_Shdr *sec);

/** Retrieve information about the content of a section
 *
 * @param elf The ELF object descriptor;
 * @param sec The section whose content info will be retrieved;
 * @param content The address of the location where the section content
 *                address will be stored;
 * @param size The address of the location where the size will be stored;
 * @return true if the section contains data, false if the section type is
 *         SHT_NOBITS.
 */
bool elf_sect_content (elf_t *elf, Elf32_Shdr *sec,
                       uint8_t **content, size_t *size);

#ifdef __cplusplus
}
#endif

#endif // __defined_elfsword_sections_h
