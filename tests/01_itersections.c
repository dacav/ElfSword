#include <elfsword.h>
#include <dacav.h>
#include <assert.h>
#include <elf.h>

int main (int argc, char **argv)
{
    elf_t *me;
    diter_t *iter;
    int count;
    Elf32_Shdr *sh;

    assert(elf_map_file(argv[0], &me) == ELF_SUCCESS);
    iter = elf_sect_iter_new(me, SHT_NULL);
    count = -1;
    while (diter_hasnext(iter)) {
        diter_next(iter);
        //sh = (Elf32_Shdr *) diter_next(iter);
        //printf("name='%s' address=%p\n",
        //       elf_sect_name(me, sh), (void *) sh);
        count ++;
    }
    elf_sect_iter_free(iter);

    assert(elf_sect_seek(me, count, &sh) == ELF_SUCCESS);
    assert(elf_sect_seek(me, count + 1, &sh) == ELF_NOSECTION);

    elf_release_file(me);
    exit(0);
}
