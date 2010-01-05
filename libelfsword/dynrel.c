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
#include <stdlib.h>
#include <stdbool.h>

#include <elfsword.h>

/* ------ Iterators among dynamic linking entries --------------------- */

struct iterable {
    Elf32_Dyn *cursor;
    unsigned nents;
};

static
void *iter_next (struct iterable *it)
{
    Elf32_Dyn *ret = it->cursor;
    it->cursor = ret + 1;
    it->nents --;
    return (void *) ret;
}

static
int iter_hasnext (struct iterable *it)
{
    return it->nents;
}

diter_t *elf_dynrel_iter_new (elf_t *elf)
{
    diter_t *ret = diter_new((dnext_t)iter_next, (dhasnext_t)iter_hasnext,
                             NULL, NULL, sizeof(struct iterable));

    struct iterable *it = (struct iterable *) diter_get_iterable(ret);
    div_t q;

    Elf32_Shdr *dynamic = elf->dynamic;
    q.quot = 0;
    if (dynamic != NULL) {
        size_t len;
        if (elf_sect_content(elf, dynamic, (void **)&it->cursor, &len) ==
                ELF_SUCCESS) {
            q = div(len, sizeof(Elf32_Dyn));
        }
    }
    it->nents = q.quot;
    return ret;
}

void elf_dynrel_iter_free (diter_t *iter)
{
    diter_free(iter);
}

