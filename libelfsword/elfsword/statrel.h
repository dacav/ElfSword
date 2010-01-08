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

/** Getter for the section holding the static relocation entry.
 *
 * @param desc The descriptor of the relocation entry;
 * @param sec The address of a section header pointer;
 */
void elf_statrel_section (elf_statrel_t *desc, Elf32_Shdr **sec);

/** Getter for the symbol table associated to a static relocation entry.
 *
 * This isn't the most straightforward way to obtain information about the
 * symbol. If you need a symbol descriptor use elf_statrel_symbol instead.
 *
 * The retrieved pointer (last parameter) makes sense only if
 * ELF_SUCCESS is returned.
 *
 * @param desc The descriptor of the relocation entry;
 * @param sec The address of a section header pointer;
 * @return ELF_SUCCESS on success, ELF_INVALID if there's something wrong
 *         with the ELF object.
 */
elf_err_t elf_statrel_symtab (elf_statrel_t *desc, Elf32_Shdr **sec);

/** Getter for the symbol associated to a static relocation entry
 *
 * The retrieved pointer (last parameter) makes sense only if
 * ELF_SUCCESS is returned.
 *
 * @param desc The descriptor of the relocation entry;
 * @param symb The retrieved symbol descriptor.
 * @return ELF_SUCCESS on success, ELF_INVALID if there's something wrong
 *         with the ELF object.
 */
elf_err_t elf_statrel_symbol (elf_statrel_t *desc, elf_symb_desc_t *symb); 

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

/** Getter for the static relocation entry content.
 *
 * This function treats the relocation entry provided by desc as a
 * Elf32_Rela entry (i.e. as the section were of type ST_RELA).
 *
 * If the section type is ST_REL, then the rela::r_addend field is
 * set to 0.
 *
 * @param desc The descriptor of relocation entry;
 * @param rela Storage address for relocation entry data.
 */
void elf_statrel_rela (elf_statrel_t *desc, Elf32_Rela *rela);

/** Build a libdacav iterator on static relocation entries.
 *
 * The diter_next function will return a the address of a descriptor from
 * which derive information about the relocation entry.
 *
 * @see elf_statrel_t;
 *
 * @param elf The ELF object descriptor;
 * @return An iterator among ELF object's static relocation entries.
 */
diter_t *elf_statrel_iter_new (elf_t *elf);

/** Free the given sections iterator.
 *
 * @param iter The iterator to be freed.
 */
void elf_statrel_iter_free (diter_t *iter);

#ifdef __cplusplus
}
#endif

#endif // __defined_elfsword_statrel_h
