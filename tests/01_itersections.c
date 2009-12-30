#include <elfsword.h>
#include <dacav.h>
#include <assert.h>
#include <elf.h>

int main (int argc, char **argv)
{
    elf_t *me;
    diter_t *iter;

    assert(elf_map_file(argv[0], &me) == ELF_SUCCESS);
    iter = elf_sect_iter_new(me, SHT_NULL);
    while (diter_hasnext(iter)) {
        Elf32_Shdr *sh = (Elf32_Shdr *) diter_next(iter);
        printf("name='%s' address=%p\n",
               elf_sect_name(me, sh), (void *) sh);
    }
    elf_sect_iter_free(iter);
    elf_release_file(me);

    exit(0);
}
