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

/** @file descriptor.h
 *
 * Checks on ELF descriptor;
 */

#ifndef __defined_elfsword_descriptor_h
#define __defined_elfsword_descriptor_h

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <elf.h>
#include <dacav.h>

#ifdef __cplusplus
extern "C" {
#endif

/** ELF mapping type */
typedef struct {

    union {
        void *data;             /**< Memory mapped file; */
        uint8_t *data8b;        /**< 8 bit pointer; */
        Elf32_Ehdr *header;     /**< ELF header; */
    } file;                     /**< Allocated data */
    size_t len;                 /**< File size; */
    int fd;                     /**< File descriptor; */

    Elf32_Shdr *names;          /**< Pointer to the name section */
    dhash_t *secs;              /**< Sections hash by name; */

    Elf32_Shdr *dynsym;         /**< Dynamic symbols table */
    Elf32_Shdr *symtab;         /**< Standard symbols table (".symtab") */
    Elf32_Shdr *dynamic;        /**< Dynamic linking information */

} elf_t;

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

#ifdef __cplusplus
}
#endif

#endif // __defined_elfsword_descriptor_h
