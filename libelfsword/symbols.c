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
#include <elfsword.h>
#include <stdint.h>

#include <stdio.h>

/* ------ Basic symbols access routines ------------------------------- */

struct symbol_desc {
    Elf32_Sym *yhdr;    // The symbol header;
    Elf32_Shdr *shdr;   // The symbol belongs to this section.
};

const char *elf_symb_name (elf_t *elf, elf_symb_desc_t *desc)
{
    const Elf32_Ehdr *header = elf->file.header;
    Elf32_Shdr *shdr = desc->shdr;
    Elf32_Word st_name = desc->yhdr->st_name;

    if (st_name == 0)
        return NULL;

    /* shdr->sh_link contains the index of the associated string table.
     * Moving on the correct table */
    shdr = (Elf32_Shdr *) ((elf->file.data8b + header->e_shoff)
                           + (header->e_shentsize * shdr->sh_link));
    return (const char *)elf->file.data + shdr->sh_offset + st_name;
}

/* ------ Iterators among symbols -------------------------------------- */

struct iterable {
    elf_t *elf;
    diter_t *sec_iter;
    uint8_t *cursor;
    uint8_t *end;
    elf_symb_desc_t outdesc;
};

static
void *iter_next (struct iterable *it)
{
    Elf32_Sym *tmp = (Elf32_Sym *) it->cursor;

    it->outdesc.yhdr = tmp;
    it->cursor = (uint8_t *)(tmp + 1);
    return (void *) &it->outdesc;
}

static
int iter_hasnext (struct iterable *it)
{
    Elf32_Shdr *next;
    size_t size;
    uint8_t *cursor = it->cursor;
    diter_t *sec_iter = it->sec_iter;

    if (cursor == NULL || cursor >= it->end) {
        while (diter_hasnext(sec_iter)) {
            next = (Elf32_Shdr *) diter_next(sec_iter);
            if (elf_sect_content(it->elf, next, &cursor, &size)
                    == ELF_NOSECTION) {
                // nobits, no content. This should never happen, anyway.
                continue;
            }
            printf("Jukebox call\n");
            it->cursor = cursor;        // begin of the section;
            it->end = cursor + size;    // end of the section;
            it->outdesc.shdr = next;    // current section header;
            return 1;   // continue with next section.
        }
        printf("End of sections having symbols\n");
        return 0;   // all sections have been checked.
    }
    return 1;   // there's still something in this section.
}

diter_t *elf_symb_iter_new (elf_t *elf)
{
    diter_t *ret = diter_new((dnext_t)iter_next, (dhasnext_t)iter_hasnext,
                             NULL, NULL, sizeof(struct iterable));

    struct iterable *it = (struct iterable *) diter_get_iterable(ret);

    // Selecting symtab sections.
    it->sec_iter = elf_sect_iter_new(elf, SHT_SYMTAB);
    it->cursor = NULL;
    it->elf = elf;

    return ret;
}

void elf_symb_iter_free (diter_t *iter)
{
    diter_free(iter);
}

