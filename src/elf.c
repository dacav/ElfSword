#include "elf.h"
#include "elf_specification.h"

#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>

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

/* Sections iteration function.
 * If the return value is true the iteration will be stopped */
typedef bool (*sec_scan_t)(void *udata, elf_t elf, Elf32_Shdr *shdr);

static
const char *section_name(elf_t elf, Elf32_Shdr *shdr)
{
    return (const char *)elf->file.data +
                         elf->names->sh_offset +
                         shdr->sh_name;
}

static
void scan_sections(elf_t elf, sec_scan_t callback, void *udata)
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

static
bool check_magic_number(elf_t elf)
{
    unsigned char *magic;

    magic = ((Elf32_Ehdr *)elf->file.data)->e_ident;
    return magic[EI_MAG0] == ELFMAG0 &&
           magic[EI_MAG1] == ELFMAG1 &&
           magic[EI_MAG2] == ELFMAG2 &&
           magic[EI_MAG3] == ELFMAG3;
}

static
bool release_file(elf_t elf)
{
    return (munmap(elf->file.data, elf->len) + close(elf->fd)) == 0;
}

static
bool map_file(elf_t elf, const char *filename)
{
    int fd;
    struct stat buf;
    size_t len;
    uint8_t *secarray;
    Elf32_Ehdr *header;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return false;
    if (fstat(fd, &buf) == -1) {
        close(fd);
        return false;
    }
    elf->len = len = buf.st_size;
    elf->file.data = mmap(NULL, len, PROT_READ, MAP_SHARED, fd, 0);
    elf->fd = fd;

    header = elf->file.header;
    secarray = (elf->file.data8b + header->e_shoff);
    elf->names = (Elf32_Shdr *) (secarray +
                 header->e_shstrndx * header->e_sheentsize);
    return true;
}


/* -------------------------------------------------------------------- */
/* TESTING                                                              */
/* -------------------------------------------------------------------- */

bool scanner (void *udata, elf_t elf, Elf32_Shdr *shdr)
{
    unsigned *counter = (unsigned *)udata;
    
    printf("Section id: %03d (0x%08X):\n", *counter, (unsigned)shdr);
    printf("    Name:  [%s]\n", section_name(elf, shdr));
    printf("    Flags: [%c%c%c]\n", shdr->sh_flags & SHF_WRITE     ? 'w' : '-',
                                    shdr->sh_flags & SHF_ALLOC     ? 'a' : '-',
                                    shdr->sh_flags & SHF_EXECINSTR ? 'x' : '-');
    (*counter)++;
    return true;
}

int main(int argc, char **argv)
{
    struct elf_struct elf;
    unsigned counter;

    assert(argc > 1);
    counter = 0;
    map_file(&elf, argv[1]);
    if (check_magic_number(&elf))
        scan_sections(&elf, scanner, (void *)&counter);
    else
        printf("Invalid magic!\n");
    release_file(&elf);

    return 0;
}
