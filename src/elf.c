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
        void *data;
        Elf32_Ehdr *header;
    } file;
    size_t len;
    int fd;

    /* Auxiliary data */
    Elf32_Shdr *secnames;

};

/* Sections iteration function.
 * If the return value is true the iteration will be stopped */
typedef bool (*sec_scan_t)(void *udata, Elf32_Shdr *header);

static
void scan_sections(elf_t elf, sec_scan_t callback, void *udata)
{
    Elf32_Ehdr *header;
    Elf32_Shdr *cursor;
    uint32_t sec_count;
    size_t sec_size;

    Elf32_Shdr *old;

    header = elf->file.header;
    cursor = (Elf32_Shdr *)((uint8_t *)elf->file.data + header->e_shoff);
    sec_count = header->e_shnum;
    sec_size = header->e_sheentsize;

    while(sec_count--) {
        if (!callback(udata, cursor))
            break;
        old = cursor;
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
    return true;
}


/* -------------------------------------------------------------------- */
/* TESTING                                                              */
/* -------------------------------------------------------------------- */

bool scanner (void *udata, Elf32_Shdr *header)
{
    unsigned *counter = (unsigned *)udata;
    
    printf("Section id: %03d; Section flags: [%c%c%c]; string: ",
           *counter,
           header->sh_flags & SHF_WRITE ? 'w' : '-',
           header->sh_flags & SHF_ALLOC ? 'a' : '-',
           header->sh_flags & SHF_EXECINSTR ? 'x' : '-');
    printf("%s\n", header->sh_type == SHT_STRTAB ? "true  <--" : "false");
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
