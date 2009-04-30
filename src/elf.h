#ifndef __ELF_H__
#define __ELF_H__

#include <stdbool.h>
#include "elf_specification.h"

typedef struct elf_struct * elf_t;

/* Sections iteration function.
 * If the return value is true the iteration will be stopped */
typedef bool (*sec_scan_t)(void *udata, elf_t elf, Elf32_Shdr *shdr);

elf_t           elf_map_file        (const char *filename);
const char *    elf_section_name    (elf_t elf, Elf32_Shdr *shdr);
void            elf_sections_scan   (elf_t elf, sec_scan_t callback, void *udata);
bool            elf_check_magic     (elf_t elf);
bool            elf_release_file    (elf_t elf);
const char *    elf_section_name    (elf_t elf, Elf32_Shdr *shdr);
void            elf_sections_scan   (elf_t elf, sec_scan_t callback, void *udata);
bool            elf_check_magic     (elf_t elf);
bool            elf_release_file    (elf_t elf);

#endif /* __ELF_H__ */
