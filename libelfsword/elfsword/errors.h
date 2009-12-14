/*
 * Copyright 2009 Giovanni Simoni
 *
 * This file is part of ElfSword.
 *
 * elf_t *Sword is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * elf_t *Sword is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with elf_t *Sword.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __defined_elfsword_errors_h
#define __defined_elfsword_errors_h

#ifdef __cplusplus
extern "C" {
#endif

/** Status flags, used as return value. */
typedef enum {
    ELF_SUCCESS = 0,    /**< No error. */
    ELF_OPENING = 1,    /**< Unable to open the file. */
    ELF_MAPPING = 2,    /**< Unable to map the file. */
    ELF_INVALID = 3     /**< Invalid ELF object. */
} elf_err_t;

#ifdef __cplusplus
}
#endif

#endif // __defined_elfsword_errors_h
