#include <elfsword.h>
#include <dacav.h>
#include <assert.h>

int main (int argc, char **argv)
{
    elf_t *me;
    diter_t *iter;
    int i = 0;

    assert(elf_map_file(argv[0], &me) == ELF_SUCCESS);
    iter = elf_sects_iter_new(me);
    while (diter_hasnext(iter)) {
        printf("Section %d : %p\n", i++, diter_next(iter));
    }
    elf_sects_iter_free(iter);
    elf_release_file(me);

    exit(0);
}
