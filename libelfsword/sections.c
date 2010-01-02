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

/* ------ Basic section access routines ------------------------------- */

elf_err_t elf_sect_content (elf_t *elf, Elf32_Shdr *sec,
                            uint8_t **content, size_t *size)
{
    if (sec->sh_type == SHT_NOBITS)
        return ELF_NOSECTION;
    *content = elf->file.data8b + sec->sh_offset;
    *size = sec->sh_size;
    return ELF_SUCCESS;
}

elf_err_t elf_sect_seek (elf_t *elf, unsigned index, Elf32_Shdr **sec)
{
    Elf32_Ehdr *header = elf->file.header;
    if (index >= header->e_shnum)
        return ELF_NOSECTION;
    uint8_t *pos = (uint8_t *)header;
    pos += header->e_shoff;             // first section;
    pos += header->e_shentsize * index; // move to selected section;
    *sec = (Elf32_Shdr *) pos;
    return ELF_SUCCESS;
}

const char *elf_sect_name (elf_t *elf, Elf32_Shdr *sec)
{
    const char *map = (char *)elf->file.data8b +
                      elf->names->sh_offset;
    if (sec == NULL) {
        return map;
    } else {
        return map + sec->sh_name;
    }
}

/* ------ Iterators among sections ------------------------------------ */

struct iterable {
    uint8_t *cursor;        // Current address;
    uint8_t *end;           // Last section address;
    Elf32_Half shentsize;   // Pointer increment;
    Elf32_Word sh_type;     // Filtering section type;
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
    union {
        Elf32_Shdr *hdr;
        uint8_t *cursor;
    } ptr;
    uint8_t *end = it->end;
    Elf32_Word sh_type = it->sh_type;

    ptr.cursor = it->cursor;
    if (sh_type == SHT_NULL) {
        // There's no filter. Just check position.
        return ptr.cursor < end;
    }
    while (ptr.cursor < end) {
        if (ptr.hdr->sh_type == sh_type) {
            it->cursor = ptr.cursor;    // update cursor.
            return 1;
        }
        ptr.cursor += it->shentsize;
    }
    return 0;   // End of list has been reached.
}

diter_t *elf_sect_iter_new (elf_t *elf, Elf32_Word sh_type)
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

    it->shentsize = shentsize; // Step increment;
    it->sh_type = sh_type;     // Filter.

    return ret;
}

void elf_sect_iter_free (diter_t *iter)
{
    diter_free(iter);
}

/* ------ Optimization with hash tables ------------------------------- */

elf_err_t elf_sect_get_hash (elf_t *elf, const dhash_t **table)
{
    if (elf->names == NULL) {
        return ELF_NOSECTION;       // There's no string table;
    }
    *table = elf->secs;
    return ELF_SUCCESS;
}

