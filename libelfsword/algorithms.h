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

/** @file algorithms.h
 *
 * Algorithms defined by ELF specification
 */

#ifndef __defined_algorithms_h
#define __defined_algorithms_h

#include <elfsword.h>

/** Hashing function for strings.
 *
 * Typically used for symbol names.
 *
 * @param name The name to be hashed;
 * @return The hash value.
 */
unsigned long elf_hash (const unsigned char *name);

#endif // __defined_algorithms_h
