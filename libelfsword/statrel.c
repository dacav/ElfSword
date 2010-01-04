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
#include <assert.h>
#include <elfsword.h>
#include <string.h>

/** Static relocation related data */
struct statrel {
    Elf32_Word sh_type;     /* Type of the section containing the value,
                             *   may contain SHT_REL or SHT_RELA */
    union {
        Elf32_Rel *rel;     /* To be used if elf_statrel_t::sh_type is
                             *   SHT_REL */
        Elf32_Rela *rela;   /* To used if elf_statrel_t::sh_type is
                             *   SHT_RELA */
        uint8_t *ptr8;
    } data;                 /* Contained data */
    Elf32_Shdr *contsec;    // Container section;
    elf_t *elf;
};

struct iterable {
    diter_t *sects_iter;        // Iterator among selected sections;
    elf_statrel_t statrel;      // Static allocation descriptor;
    size_t size;
    size_t step;
    void *secdata;
};

#include <stdio.h>

static
void *iter_next (struct iterable *it)
{
    uint8_t *cur = (uint8_t *)it->secdata;
    size_t step = it->step;
    it->statrel.data.ptr8 = cur;
    it->size -= step;
    cur += step;
    it->secdata = (void *)cur;

    return &it->statrel;
}

static
int iter_hasnext (struct iterable *it)
{
    size_t size = it->size;
    if (size >= it->step)
        return 1;   // Section not consumed yet;

    diter_t *iter = it->sects_iter;
    Elf32_Shdr *contsec;
    elf_t *elf = it->statrel.elf;
    Elf32_Word sh_type;

    // Jump to next SHT_REL or SHT_RELA section
    do {
        if (!diter_hasnext(iter)) {
            return 0;   // No more stuff;
        }
        contsec = (Elf32_Shdr *) diter_next(iter);
        sh_type = contsec->sh_type;
    } while ((sh_type != SHT_REL && sh_type != SHT_RELA)
             || elf_sect_content(elf, contsec, &(it->secdata), &size) !=
             ELF_SUCCESS);

    it->size = size;
    it->step = sh_type == SHT_REL ? sizeof(Elf32_Rel) :
                                    sizeof(Elf32_Rela);
    it->statrel.contsec = contsec;
    it->statrel.sh_type = sh_type;
    return 1;
}

diter_t *elf_statrel_iter_new (elf_t *elf)
{
    diter_t *ret = diter_new((dnext_t)iter_next, (dhasnext_t)iter_hasnext,
                             NULL, NULL, sizeof(struct iterable));

    struct iterable *it = (struct iterable *) diter_get_iterable(ret);
    it->statrel.elf = elf;
    it->sects_iter = elf_sect_iter_new(elf, SHT_NULL);
    it->size = 0;
    it->step = sizeof(Elf32_Rela);  // dummy step for the first hasnext 

    return ret;
}

void elf_statrel_iter_free (diter_t *iter)
{
    diter_free(iter);
}

elf_err_t elf_statrel_symtab (elf_statrel_t *desc, Elf32_Shdr **sec)
{
    Elf32_Shdr *contsec = desc->contsec;
    if (elf_sect_seek(desc->elf, contsec->sh_link, sec)
            == ELF_NOSECTION)
        return ELF_INVALID;
    return ELF_SUCCESS;
}

elf_err_t elf_statrel_target (elf_statrel_t *desc, Elf32_Shdr **sec)
{
    if (elf_sect_seek(desc->elf, desc->contsec->sh_info, sec)
            == ELF_NOSECTION) {
        return ELF_INVALID;
    }
    return ELF_SUCCESS;
}

void elf_statrel_rela (elf_statrel_t *desc, Elf32_Rela *rela)
{
    if (desc->sh_type == SHT_RELA) {
        memcpy(rela, desc->data.rela, sizeof(Elf32_Rela));
    } else {
        rela->r_offset = desc->data.rel->r_offset;
        rela->r_info = desc->data.rel->r_info;
        rela->r_addend = 0;
    }
}

elf_err_t elf_statrel_symbol (elf_statrel_t *desc, elf_symb_desc_t *symb)
{
    Elf32_Shdr *symtab;
    if (elf_statrel_symtab(desc, &symtab) == ELF_INVALID)
        return ELF_INVALID;
    Elf32_Addr offset = ELF32_R_SYM(desc->data.rel->r_info);
    return elf_symb_seek(desc->elf, symtab->sh_type, offset, symb)
           == ELF_SUCCESS ? ELF_SUCCESS : ELF_INVALID;
}

void elf_statrel_section (elf_statrel_t *desc, Elf32_Shdr **sec)
{
    *sec = desc->contsec;
}
