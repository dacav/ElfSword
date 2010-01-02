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
#include <stdint.h>
#include <stdbool.h>

#include <elfsword.h>

/* ------ Iterators among program header entries ---------------------- */

struct iterable {
    Elf32_Phdr *cursor;
    size_t size;
    unsigned nents;
};

static
void *iter_next (struct iterable *it)
{
    uint8_t *ret = (uint8_t *) it->cursor;
    it->cursor = (Elf32_Phdr *)(ret + it->size);
    it->nents --;
    return (void *) ret;
}

static
int iter_hasnext (struct iterable *it)
{
    return it->nents;
}

diter_t *elf_proghead_iter_new (elf_t *elf)
{
    diter_t *ret = diter_new((dnext_t)iter_next, (dhasnext_t)iter_hasnext,
                             NULL, NULL, sizeof(struct iterable));

    struct iterable *it = (struct iterable *) diter_get_iterable(ret);
    Elf32_Ehdr *header = elf->file.header;

    it->cursor = (Elf32_Phdr *)(elf->file.data8b + header->e_phoff);
    it->size = header->e_phentsize;
    it->nents = header->e_phnum;

    return ret;
}

void elf_proghead_iter_free (diter_t *iter)
{
    diter_free(iter);
}

