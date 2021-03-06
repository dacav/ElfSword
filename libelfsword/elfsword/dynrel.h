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

/** @file dynrel.h
 *
 * ELF dynamic relocation management routines.
 */

#ifndef __defined_elfsword_dynrel_h
#define __defined_elfsword_dynrel_h

#include <elfsword.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Build a libdacav iterator on dynamic relocation entries.
 *
 * The diter_next function will return an address of a Elf32_Dyn
 * structure.
 *
 * @param elf The ELF object descriptor;
 * @return An iterator among ELF object's proghead.
 */
diter_t *elf_dynrel_iter_new (elf_t *elf);

/** Free the given proghead iterator.
 *
 * @param iter The iterator to be freed.
 */
void elf_dynrel_iter_free (diter_t *iter);

#ifdef __cplusplus
}
#endif

#endif // __defined_elfsword_dynrel_h
