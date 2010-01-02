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

/** Opaque type describing a symbol.
 *
 * This is an internal wrapper for the Elf32_Sym data type.
 */
typedef struct symbol_desc elf_symb_desc_t;

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
 * The diter_next function will return a pointer to a descriptor from
 * which derive the symbol name and the symbol header.
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

#endif // __defined_elfsword_symbols_h
