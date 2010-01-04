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

/** @file statrel.h
 *
 * ELF static relocation management routines.
 */

#ifndef __defined_elfsword_statrel_h
#define __defined_elfsword_statrel_h

#include <elfsword.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Opaque type for static relocation entries.
 *
 * A pointer to this data type is returned by the diter_next function
 * applied to a static relocation iterator.
 *
 * @see elf_statrel_iter_new;
 */
typedef struct statrel elf_statrel_t;

/** Getter for the symbol table associated to a static relocation entry
 *
 * The retrieved pointer (second parameter) makes sense only if
 * ELF_SUCCESS is returned.
 *
 * @param desc The descriptor of the relocation entry;
 * @param sec The address of a section header pointer;
 * @return ELF_SUCCESS on success, ELF_INVALID if there's something wrong
 *         with the ELF object.
 */
elf_err_t elf_statrel_symtab (elf_statrel_t *desc, Elf32_Shdr **sec);

/** Getter for the target section associated to a static relocation entry
 *
 * The retrieved pointer (second parameter) makes sense only if
 * ELF_SUCCESS is returned.
 *
 * @param desc The descriptor of the relocation entry;
 * @param sec The address of a section header pointer;
 * @return ELF_SUCCESS on success, ELF_INVALID if there's something wrong
 *         with the ELF object.
 */
elf_err_t elf_statrel_target (elf_statrel_t *desc, Elf32_Shdr **sec);

/** Build a libdacav iterator on static relocation entries.
 *
 * The diter_next function will return a the address of a descriptor from
 * which derive information about the relocation entry.
 *
 * @see elf_statrel_t;
 *
 * @param elf The ELF object descriptor;
 * @param sh_type The section type corresponding to the kind of symbols to
 *                seek (SHT_REL or SHT_RELA);
 * @return An iterator among ELF object's static relocation entries.
 */
diter_t *elf_statrel_iter_new (elf_t *elf, Elf32_Word sh_type);

/** Free the given sections iterator.
 *
 * @param iter The iterator to be freed.
 */
void elf_statrel_iter_free (diter_t *iter);

#ifdef __cplusplus
}
#endif

#endif // __defined_elfsword_statrel_h
