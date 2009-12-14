#include <stdlib.h>
#include <elfsword.h>
#include <assert.h>

int main (int argc, char **argv)
{
    elf_t *me;
   
    assert(elf_map_file(argv[0], &me) == ELF_SUCCESS);
    assert(elf_check_magic(me));
    elf_release_file(me);

    exit(0);
}
