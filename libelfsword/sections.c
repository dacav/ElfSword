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

#include <elf.h>
#include <dacav.h>
#include <string.h>

#include <elfsword.h>
#include "algorithms.h"

/* ------ Basic section access routine -------------------------------- */

Elf32_Shdr *elf_sects_seek (elf_t *elf, unsigned index)
{
    Elf32_Ehdr *header = elf->file.header;
    uint8_t *pos = (uint8_t *)header;
    pos += header->e_shoff;             // first section;
    pos += header->e_shentsize * index; // move to selected section;
    return (Elf32_Shdr *) pos;
}

/* ------ Iterators among sections------------------------------------- */

struct iterable {
    uint8_t *cursor;        // Current address;
    uint8_t *end;           // Last section address;
    Elf32_Half shentsize;   // Pointer increment;
};

static
void *iter_next (struct iterable *it)
{
    uint8_t *pos = (void *) it->cursor;
    it->cursor = pos + it->shentsize;
    return (void *) pos;
}

static
int iter_hasnext (struct iterable *it)
{
    return it->cursor < it->end;
}

diter_t *elf_sects_iter_new (elf_t *elf)
{
    diter_t *ret = diter_new((dnext_t)iter_next, (dhasnext_t)iter_hasnext,
                             NULL, NULL, sizeof(struct iterable));

    struct iterable *it = (struct iterable *) diter_get_iterable(ret);

    Elf32_Ehdr *header = elf->file.header;
    Elf32_Half shentsize = header->e_shentsize;

    // Cursor. Initially points the address of the file beginning;
    uint8_t *pos = (uint8_t *)header;

    // Now we are positioned on the first section;
    pos += header->e_shoff;
    it->cursor = pos;

    // Last section;
    pos += shentsize * header->e_shnum;
    it->end = pos;

    // Step increment;
    it->shentsize = shentsize;

    return ret;
}

void elf_sects_iter_free (diter_t *iter)
{
    diter_free(iter);
}

/* ------ Optimization with hash tables ------------------------------- */

#include <stdio.h>

static inline
void fill_hash (elf_t *elf, dhash_t *table)
{
    const char *map = (char *)elf->file.data8b +
                      elf->names->sh_offset;

    diter_t *iter = elf_sects_iter_new(elf);
    while (diter_hasnext(iter)) {
        Elf32_Shdr *sec = diter_next(iter);
        const char *name = map + sec->sh_name;
        dhash_insert(table, (void *)name, (void *)sec);
    }
    elf_sects_iter_free(iter);
}

dhash_t *elf_sects_get_hash (elf_t *elf)
{
    if (elf->names == NULL) {
        return NULL;    // There's no string table;
    }
    dhash_t *secs = elf->secs;
    if (secs == NULL) {
        secs = dhash_new(ELF_SECHASH_SIZE, (dhash_func_t)elf_hash,
                         (dcmp_func_t)strcmp);
        fill_hash(elf, secs);
        elf->secs = secs;
    }
    return secs;
}

