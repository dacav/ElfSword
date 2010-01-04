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

/** @file symbols.h
 *
 * ELF symbols management routines.
 */

#ifndef __defined_elfsword_symbols_h
#define __defined_elfsword_symbols_h

#include <elfsword.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Symbol descriptor.
 *
 * This structure is not declared as opaque since must be instantiated by
 * any function using the elf_symb_seek function. A pointer to this
 * function is also returned by symbols iterators.
 *
 * @see elf_symb_iter_new;
 * @see elf_symb_seek;
 * @see elf_symb_name;
 */
typedef struct {
    Elf32_Sym *yhdr;    /**< The symbol header */
    Elf32_Shdr *shdr;   /**< The section in which elf_symb_desc_t::yhdr is
                         *   stored */
} elf_symb_desc_t;

/** Retrieve a symbol descriptor.
 *
 * The retrieved pointer (last parameter) makes sense only if
 * ELF_SUCCESS is returned.
 *
 * @param elf The ELF object descriptor;
 * @param sh_type The section type corresponding to the kind of symbols to
 *                seek (SHT_SYMTAB or SHT_DYNSYM);
 * @param index The index of the required symbol;
 * @param desc The retrieved symbol descriptor.
 * @return ELF_SUCCESS on success; ELF_NOSYMBOL if the given index is
 *         greater than the number of elements in the symbol table;
 *         ELF_INVALID if the file is not well formed (this should never
 *         happen).
 */
elf_err_t elf_symb_seek (elf_t *elf, Elf32_Word sh_type, unsigned index,
                         elf_symb_desc_t *desc);

/** Get the required symbol name.
 *
 * @param desc The symbol descriptor;
 * @param name A pointer where the string address will be stored;
 * @return The name of the given section, or the starting address of the
 *         section names table if NULL is given as second parameter.
 */
const char *elf_symb_name (elf_t *elf, elf_symb_desc_t *desc);

/** Build a libdacav iterator on symbols.
 *
 * Only SHT_NULL, SHT_SYMTAB and SHT_DYNSYM make sense as second
 * parameter. If SHT_NULL is provided every symbol will be considered. If
 * SHT_SYMTAB or SHT_DYNSYM is provided only .symtab and .dynsym symbols
 * will be considered respectively.
 *
 * The diter_next function will return a the address of a descriptor from
 * which derive the symbol name and the symbol header.
 *
 * @see elf_symb_desc_t;
 *
 * @param sh_type The section type corresponding to the kind of symbols to
 *                iterate on;
 * @param elf The ELF object descriptor;
 * @return An iterator among ELF object's symbols.
 */
diter_t *elf_symb_iter_new (elf_t *elf, Elf32_Word sh_type);

/** Free the given symbols iterator.
 *
 * @param iter The iterator to be freed.
 */
void elf_symb_iter_free (diter_t *iter);

#ifdef __cplusplus
}
#endif

#endif // __defined_elfsword_symbols_h
