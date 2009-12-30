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

/** @file check.h
 *
 * Checks on ELF descriptor;
 */

#ifndef __defined_elfsword_check_h
#define __defined_elfsword_check_h

#include <stdbool.h>
#include <elfsword.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Checks the ELF magic number to be correct
 *
 * @param elf The ELF object descriptor;
 * @return true if the object has a valid magic number, false otherwise.
 */
elf_err_t elf_check_magic (elf_t * elf);

#ifdef __cplusplus
}
#endif

#endif // __defined_elfsword_check_h
