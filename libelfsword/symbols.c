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
#include <string.h>

#include <stdio.h>

/* ------ Basic symbols access routines ------------------------------- */

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

elf_err_t elf_symb_seek (elf_t *elf, Elf32_Word sh_type, unsigned index,
                         elf_symb_desc_t *desc)
{
    Elf32_Shdr *select;
    switch (sh_type) {
        case SHT_DYNSYM:
            select = elf->dynsym;
            break;
        case SHT_SYMTAB:
            select = elf->symtab;
            break;
        default:
            return ELF_WRONGPARAM;
    }

    size_t size;
    uint8_t *start;
    Elf32_Sym *sym;
    if (elf_sect_content(elf, select, (void **)&start, &size) !=
            ELF_SUCCESS) {
        return ELF_INVALID;
    }
    sym = (Elf32_Sym *) start + index;
    if ((uint8_t *)sym > start + size) {
        return ELF_NOSYMBOL;
    }
    desc->yhdr = sym;
    desc->shdr = select;
    return ELF_SUCCESS;
}

/* ------ Iterators among symbols -------------------------------------- */

struct iterable {
    elf_t *elf;
    uint8_t *cursor;
    uint8_t *end;
    Elf32_Shdr *symtabs[2];     // we have at most two symbol tabs.
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
    uint8_t *cursor = it->cursor;

    if (cursor == NULL || cursor >= it->end) {

        // Check if there's at least one symbol table available:
        Elf32_Shdr *next = it->symtabs[0];
        if (next != NULL) {
            it->symtabs[0] = NULL;  // Section 0 consumed.
        } else if ((next = it->symtabs[1]) == NULL) {
            return 0;               // No more sections.
        } else {
            it->symtabs[1] = NULL;      // Section 1 consumed.
        }

        size_t size;
        if (elf_sect_content(it->elf, next, (void **)&cursor, &size)
                == ELF_NOSECTION) {
            // nobits, no content. This should never happen anyway.
            // ...well, if the ELF file is sane, at least.
            return 0;
        }
        it->cursor = cursor;        // begin of the section;
        it->end = cursor + size;    // end of the section;
        it->outdesc.shdr = next;    // current section header;
    }
    return 1;   // there's still something in this section.
}

diter_t *elf_symb_iter_new (elf_t *elf, Elf32_Word sh_type)
{
    diter_t *ret = diter_new((dnext_t)iter_next, (dhasnext_t)iter_hasnext,
                             NULL, NULL, sizeof(struct iterable));

    struct iterable *it = (struct iterable *) diter_get_iterable(ret);
    memset((void *)it->symtabs, (int)NULL, sizeof(Elf32_Shdr *) * 2);
    switch (sh_type) {
        case SHT_SYMTAB:
            it->symtabs[0] = elf->symtab;
            break;
        case SHT_NULL:  // Optimized code.
            it->symtabs[0] = elf->symtab;
        case SHT_DYNSYM:
            it->symtabs[1] = elf->dynsym;
    }
    it->cursor = NULL;
    it->elf = elf;

    return ret;
}

void elf_symb_iter_free (diter_t *iter)
{
    diter_free(iter);
}

