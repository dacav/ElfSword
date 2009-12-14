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

#include <elfsword.h>

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

/* ELF mapping type */
struct elf {

    /* Allocated data */
    union {
        void *data;             // Memory mapped file;
        uint8_t *data8b;        // 8 bit pointer;
        Elf32_Ehdr *header; // ELF header;
    } file;
    size_t len;                 // File size;
    int fd;                     // File descriptor;

    /* Auxiliary data */
    //Elf32_Shdr *names;      
    dhash_t *secs;              // Sections hash by name;
    struct {
        dhash_t *symtab;        // Symbols from symtab;
        dhash_t *dynsym;        // Symbols from dynsym;
    };

};

void elf_release_file(elf_t * elf)
{
    assert(elf != NULL);

    if (elf->file.data != NULL) {
        munmap(elf->file.data, elf->len);
    }
    if (elf->fd != -1) {
        close(elf->fd);
    }
    free(elf);
}

elf_err_t elf_map_file(const char *filename, elf_t **elf)
{
    int fd;
    struct stat buf;
    size_t len;
    void *data;
    elf_t *ret;

    /* Control structure allocation */
    assert(ret = malloc(sizeof(elf_t)));
    memset((void *)elf, 0, sizeof(elf_t));

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
    *elf = ret;
    return ELF_SUCCESS;
}

