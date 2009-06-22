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
 * along with ElfSword.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/*! \file elf.h
 *
 * This module allows to extract pieces of information from an ELF file.
 */
#ifndef __ELF_H__
#define __ELF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>
#include "elf_specification.h"

/*! \addtogroup elfAccFile */
/*@{*/

/*! \brief ELF file representation type. */
typedef struct elf_struct * Elf;

/*! \brief ELF file mapper.
 *
 * Produces an Elf object by mapping the given file in memory.
 *
 * \param filename The name of the ELF file to be mapped;
 * \return an Elf object or NULL on failure (i.e. invalid file).
 */
Elf elf_map_file(const char *filename);

/*! \brief ELF file releaser
 *
 * Frees the Elf object.
 *
 * \param elf The Elf object to be freed;
 * \return true on success, false on failure.
 */
bool elf_release_file(Elf elf);

/*! \brief Checks wether the ELF file is well formed.
 *
 * \param elf The Elf object;
 * \return true if the object is well formed, false otherwise.
 */
bool elf_check_format(Elf elf);

/*! \brief Returns a const pointer to the first byte of the ELF file
 *         mapping.
 *
 * \param elf The ELF file;
 * \return a const pointer to the first byte.
 */
const uint8_t * elf_get_content(Elf elf);

/*@}*/

/*! \addtogroup elfAccSections */
/*@{*/

/*! \brief Section getter by name.
 *
 * Retrieves a section by searching the given name on the sections hash
 * table.
 *
 * \param elf The Elf object;
 * \param secname The name of the section;
 * \return A pointer to the section header or NULL if there's no such
 *         section.
 */
Elf32_Shdr * elf_section_get(Elf elf, const char *secname);

/*! \brief Section getter by index.
 *
 * Retrieves a section by positioning on the given entry of the section
 * header table.
 *
 * \param elf The Elf object;
 * \param idx The required index;
 * \return A pointer to the section header or NULL if there's no such
 *         section.
 */
Elf32_Shdr * elf_section_seek(Elf elf, unsigned idx);

/*! \brief Section name getter
 *
 * Retrieves the name of the given section from the ELF string table.
 *
 * \param elf The Elf object;
 * \param shdr The section header;
 * \return The section name or NULL if the ELF file doesn't have a string
 *         table.
 */
const char * elf_section_name(Elf elf, Elf32_Shdr *shdr);

/*! \brief Section content retriever.
 *
 * Returns the position of the section's content and its length through
 * parameters side effect.
 *
 * \param elf The Elf object;
 * \param shdr The section header;
 * \param cont The pointer to be moved on the section content;
 * \param size Will contain the size of the section content in bytes.
 */
void elf_section_content(Elf elf, Elf32_Shdr *shdr, void **cont,
                         size_t *size);

/*! \brief Iteration function for section scanning.
 *
 * \param udata User data;
 * \param elf The Elf object;
 * \param shdr A pointer to the section header;
 * \return If false the iteration will be stopped.
 */
typedef bool (*SecScan)(void *udata, Elf elf, Elf32_Shdr *shdr);

/*! \brief Scans through the sections.
 *
 * The callback function provided (\see SecScan) gets called for each
 * section in the ELF file.
 *
 * \note If the callback returns false the iteration will be stopped.
 *
 * \param elf The Elf object;
 * \param callback The callback to be called;
 * \param udata User data for the callback.
 * \return true if the scan has been completed, false if it has been
 *         interrupted by the callback.
 */
bool elf_sections_scan(Elf elf, SecScan callback, void *udata);

/*@}*/

/*! \addtogroup elfAccSymbols */
/*@{*/

/*! \brief Iteration function for section's symbols scanning.
 *
 * \param udata User data;
 * \param elf The Elf object;
 * \param sec_type May be either SHT_SYMTAB or SHT_DYNSYM, depending on 
 *                 the symbol belonging, respectively the .symtab or the
 *                 .dymsym section;
 * \param name The symbol name, already retrieved through the appropriate
 *             string table
 * \param yhdr A pointer to the symbol header;
 * \return If false the iteration will be stopped.
 */
typedef bool (*SymScan)(void *udata, Elf elf, Elf32_Word sym_type,
                        const char *name, Elf32_Sym *yhdr);

/*! \brief Scans through a section's symbols.
 *
 * The callback function provided (\see SymScan) gets called for each
 * symbol in the given section.
 *
 * \note If the callback returns false the iteration will be stopped.
 *
 * \param elf The Elf object;
 * \param callback The callback to be called;
 * \param udata User data for the callback.
 * \return false if the callback interrupted the scan operation or if the
 *         ELF file doesn't have SHT_SYMTAB or SHT_DYNSYM sections, true
 *         if the scan has been completed.
 */
bool elf_symbols_scan(Elf elf, SymScan callback, void *udata);

/*! \brief Symbol getter by name.
 *
 * Retrieves a symbol by searching the given name
 *
 * \param elf The Elf object;
 * \param symname The name of the symbol;
 * \return A pointer to the symbol header or NULL if there's no such
 *         symbol.
 */
Elf32_Sym *elf_symbol_get(Elf elf, const char *symname);

/*! \brief Symbol getter by index.
 *
 * Retrieves a symbol by positioning on the given entry of the symbol
 * header table.
 *
 * \param elf The Elf object;
 * \param idx The required index;
 * \return A pointer to the symbol header or NULL if there's no such
 *         symbol.
 */
Elf32_Sym *elf_symbol_seek(Elf elf, Elf32_Word type, unsigned idx);

/*! \brief Array structure used for hash table buckets. */
typedef struct {
    Elf32_Word *array;  /*!< Pointer to the first element of the array. */
    size_t length;      /*!< Length of the array. */
} ElfArray;

/*! \breif Elf Hash table. */
typedef struct {
    ElfArray bucket;    /*!< Bucket of indexes. */
    ElfArray chain;     /*!< Chain of alternative indexes. */
} ElfHash;

/*! \brief Retrieves the hash table of the ELF file.
 *
 * \param elf The ELF object;
 * \param h A pointer to the ElfHash element to fill.
 */
bool elf_symbols_hash(Elf elf, ElfHash *h);

/*@}*/

/*! \addtogroup elfAccProgHead */
/*@{*/

/*! \brief Iteration function for program header's entry scanning.
 *
 * \param udata User data;
 * \param elf The Elf object;
 * \param phdr The program header entry;
 * \return If false the iteration will be stopped.
 */
typedef bool (*PHeaderScan)(void *udata, Elf elf, Elf32_Phdr *phdr);

/*! \brief Scans through the program header array.
 *
 * The callback function provided (\see PHeaderScan) gets called for each
 * entry in the program header.
 *
 * \param elf The Elf object;
 * \param callback The callback to be called;
 * \param udata User data for the callback;
 * \return false if the callback interrupted the scan operation or if the
 *         ELF file doesn't have a program header, true if the scan has
 *         been completed.
 */
bool elf_progheader_scan(Elf elf, PHeaderScan callback, void *udata);

/*@}*/

/*! \addtogroup elfAccRel */
/*@{*/

/*! \brief Reference to relocation related data, used for relocation
 *         section scanning.
 *
 * \see RelSectionScan, Elf32_Rel, Elf32_Rela
 */
struct RelocData {
    Elf32_Word sh_type;     /*!< Type of the section containing the value,
                             *   may contain SHT_REL or SHT_RELA */
    union {
        Elf32_Rel *rel;     /*!< To use if RelocData::sh_type is SHT_REL */
        Elf32_Rela *rela;   /*!< To use if RelocData::sh_type is SHT_RELA */
        void *_assign;
    } data;                 /*!< Contained data */
};

/*! \brief Iteration function for relocation section entry scanning.
 *
 * \see RelocData
 *
 * \param udata User data;
 * \param elf The Elf object;
 * \param s_name The container section's name;
 * \param rd The relocation entry;
 * \return If false the iteration will be stopped.
 */
typedef bool (*RelSectionScan) (void *udata, Elf elf, const char *s_name,
                                struct RelocData *rd);

/*! \brief Scans through the dynamic section entry.
 *
 * The callback function provided (\see DynSectionScan) gets called for
 * each entry of relocation sections.
 *
 * \param elf The Elf object;
 * \param callback The callback to be called;
 * \param udata User data for the callback;
 * \return false if the callback interrupted the scan operation or if the
 *         ELF file doesn't have a program header, true if the scan has
 *         been completed.
 */
bool elf_relocation_scan(Elf elf, RelSectionScan callback, void *udata);

/*@}*/

/*! \addtogroup elfAccDynamic */
/*@{*/

/*! \brief Iteration function for dynamic section entry scanning.
 *
 * \param udata User data;
 * \param elf The Elf object;
 * \param phdr The program header entry;
 * \return If false the iteration will be stopped.
 */
typedef bool (*DynSectionScan) (void *udata, Elf elf, Elf32_Dyn *dyn);

/*! \brief Scans through the dynamic section entry.
 *
 * The callback function provided (\see DynSectionScan) gets called for
 * each entry in the program header.
 *
 * \param elf The Elf object;
 * \param callback The callback to be called;
 * \param udata User data for the callback;
 * \return false if the callback interrupted the scan operation or if the
 *         ELF file doesn't have a program header, true if the scan has
 *         been completed.
 */
bool elf_dynamic_scan(Elf elf, DynSectionScan callback, void *udata);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* __ELF_H__ */
