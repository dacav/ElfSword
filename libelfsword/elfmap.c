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
 * along with elf_t *Sword.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/* System libraries */
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>

#include <dacav.h>
#include <elfsword.h>
#include "algorithms.h"

void elf_release_file (elf_t * elf)
{
    assert(elf != NULL);

    if (elf->file.data != NULL) {
        munmap(elf->file.data, elf->len);
    }
    if (elf->fd != -1) {
        close(elf->fd);
    }
    if (elf->secs != NULL) {
        dhash_free(elf->secs, NULL, NULL);
    }
    free(elf);
}

static
Elf32_Shdr *seek_strtab_section (elf_t *elf)
{
    Elf32_Half strndx = elf->file.header->e_shstrndx;
    if (strndx == SHN_UNDEF) {
        return NULL;
    }
    Elf32_Shdr *ret;
    return elf_sect_seek(elf, strndx, &ret) == ELF_SUCCESS ?
           ret : NULL;
}

static inline
void init_sections (elf_t *elf, dhash_t *table,
                    Elf32_Shdr **symtab, Elf32_Shdr **dynsym)
{
    const char *map;
    if (table != NULL) {
        map = elf_sect_name(elf, NULL); 
    }
    diter_t *iter = elf_sect_iter_new(elf, SHT_NULL);
    while (diter_hasnext(iter)) {
        Elf32_Shdr *sec = diter_next(iter);
        if (table != NULL) {
            const char *name = map + sec->sh_name;
            dhash_insert(table, (void *)name, (void *)sec);
        }
        switch (sec->sh_type) {
            case SHT_SYMTAB:
                elf->symtab = sec;
                break;
            case SHT_DYNSYM:
                elf->dynsym = sec;
                break;
        }
    }
    elf_sect_iter_free(iter);
}

elf_err_t elf_map_file (const char *filename, elf_t **elf)
{
    int fd;
    struct stat buf;
    size_t len;
    void *data;
    elf_t *ret;

    /* Control structure allocation */
    assert(ret = malloc(sizeof(elf_t))); memset((void *)elf, 0,
           sizeof(elf_t));

    /* File mapping */
    ret->fd = fd = open(filename, O_RDONLY);
    if (fd == -1 || fstat(fd, &buf) == -1) {
        elf_release_file(ret);
        return ELF_OPENING;
    }
    ret->len = len = buf.st_size;
    data = mmap(NULL, len, PROT_READ, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) {
        elf_release_file(ret);
        return ELF_MAPPING;
    }
    ret->file.data = data;
    Elf32_Shdr *names = ret->names = seek_strtab_section(ret);

    dhash_t *secs;
    if (names != NULL) {
        secs = dhash_new(ELF_SECHASH_SIZE, (dhash_func_t) elf_hash,
                         (dcmp_func_t) strcmp);
    } else {
        secs = NULL;
    }
    init_sections(ret, secs, &ret->symtab, &ret->dynsym);
    ret->secs = secs;
 
    *elf = ret;
    return ELF_SUCCESS;
}

