#include "elf.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>

/* Elf mapping type */
struct elf_struct {

    /* Allocated data */
    union {
        void *data;             /* Memory mapped file */
        uint8_t *data8b;        /* 8 bit pointer */
        Elf32_Ehdr *header;     /* Elf header */
    } file;
    size_t len;                 /* File size */
    int fd;                     /* File descriptor */

    /* Auxiliary data */
    Elf32_Shdr *names;          /* Section for name resolving */

};

const char *elf_section_name(elf_t elf, Elf32_Shdr *shdr)
{
    return (const char *)elf->file.data +
                         elf->names->sh_offset +
                         shdr->sh_name;
}

void elf_sections_scan(elf_t elf, sec_scan_t callback, void *udata)
{
    Elf32_Ehdr *header;
    Elf32_Shdr *cursor;
    uint32_t sec_count;
    size_t sec_size;

    header = elf->file.header;
    cursor = (Elf32_Shdr *)(elf->file.data8b + header->e_shoff);
    sec_count = header->e_shnum;
    sec_size = header->e_sheentsize;

    while(sec_count--) {
        if (!callback(udata, elf, cursor))
            break;
        cursor = (Elf32_Shdr *)((uint8_t *)cursor + sec_size);
    }
}

bool elf_check_magic(elf_t elf)
{
    unsigned char *magic;

    magic = ((Elf32_Ehdr *)elf->file.data)->e_ident;
    return magic[EI_MAG0] == ELFMAG0 &&
           magic[EI_MAG1] == ELFMAG1 &&
           magic[EI_MAG2] == ELFMAG2 &&
           magic[EI_MAG3] == ELFMAG3;
}

bool elf_release_file(elf_t elf)
{
    int ret;

    ret  = munmap(elf->file.data, elf->len);
    ret += close(elf->fd);
    free(elf);
    return ret >= 0;
}

elf_t elf_map_file(const char *filename)
{
    int fd;
    struct stat buf;
    size_t len;
    uint8_t *secarray;
    elf_t elf;
    Elf32_Ehdr *header;

    elf = malloc(sizeof(struct elf_struct));
    assert(elf != NULL);

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return NULL;
    if (fstat(fd, &buf) == -1) {
        close(fd);
        return NULL;
    }
    elf->len = len = buf.st_size;
    elf->file.data = mmap(NULL, len, PROT_READ, MAP_SHARED, fd, 0);
    elf->fd = fd;

    header = elf->file.header;
    secarray = (elf->file.data8b + header->e_shoff);
    elf->names = (Elf32_Shdr *) (secarray +
                 header->e_shstrndx * header->e_sheentsize);
    
    return elf;
}

