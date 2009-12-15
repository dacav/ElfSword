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
    struct {
        dhash_t *symtab;        /**< Symbols from symtab; */
        dhash_t *dynsym;        /**< Symbols from dynsym; */
    } syms;                     /**< Symbols hash by name; */

} elf_t;

#endif // __defined_elfsword_descriptor_h
