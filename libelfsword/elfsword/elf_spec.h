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
/*! \file elf_spec.h
 *
 * This file specifies data structures representing the internal of an ELF
 * binary file. For further information please refer to ELF documentation
 */

#ifndef __defined_elfsword_elf_spec_h
#define __defined_elfsword_elf_spec_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*! \addtogroup elfTypPrimitive */
/*@{*/
typedef uint32_t Elf32_Addr;    /*!< Unsigned program address */
typedef uint16_t Elf32_Half;    /*!< Unsigned medium integer */
typedef uint32_t Elf32_Off;     /*!< Unsigned file offset */
typedef int32_t Elf32_Sword;    /*!< Signed large integer */
typedef uint32_t Elf32_Word;    /*!< Unsigned large integer */
/*@}*/

/*! \addtogroup elfConstants */
/*! \brief Size of the file's magic number */
#define EI_NINDENT 16

/*! \addtogroup elfTypComposite */
/*@{*/
/*! \brief Elf file header
 *
 * This structure must be mapped on the very beginning of the file in
 * order to obtain the initial header. It can be used for reaching all the
 * parts of the ELF file.
 */
typedef struct {
    unsigned char   e_ident[EI_NINDENT]; /*!< Magic number
                                          *   \see hdr_indexes,
                                          *   hdr_magic_id, hdr_class
                                          */
    Elf32_Half      e_type;              /*!< Object file type */
    Elf32_Half      e_machine;           /*!< Architecture */
    Elf32_Word      e_version;           /*!< Object file version */
    Elf32_Addr      e_entry;             /*!< VMA for process starting */
    Elf32_Off       e_phoff;             /*!< Program header table offset */
    Elf32_Off       e_shoff;             /*!< Section header table offset */
    Elf32_Word      e_flags;             /*!< Processor flags */
    Elf32_Half      e_ehsize;            /*!< Header size */
    Elf32_Half      e_phentsize;         /*!< Header table entry size */
    Elf32_Half      e_phnum;             /*!< Header number of entries */
    Elf32_Half      e_sheentsize;        /*!< Section header's size */
    Elf32_Half      e_shnum;             /*!< Section header number of
                                              entries */
    Elf32_Half      e_shstrndx;          /*!< Section header string table */
} Elf32_Ehdr;
/*@}*/

/*! \addtogroup elfConstants */
/*@{*/

/*! \brief Elf32_Ehdr::e_ident indexes */
enum hdr_indexes {
    EI_MAG0 = 0,                         /*!< Magic number, position 1 */
    EI_MAG1 = 1,                         /*!< Magic number, position 2 */
    EI_MAG2 = 2,                         /*!< Magic number, position 3 */
    EI_MAG3 = 3,                        /*!< Magic number, position 4 */
    EI_CLASS = 4,                       /*!< Classification of the file */
    EI_DATA = 5,                        /*!< Significance  */
    EI_VERSION = 6,                     /*!< Version of the ELF file */
    EI_PAD = 7
};

/*! \brief EI_MAG0 EI_MAG1 EI_MAG3 values
 *
 * These are the first four bytes of every ELF file.
 * \see hdr_indexes
 */
enum hdr_magic_id {
    ELFMAG0 = 0x7f,                     /*!< DEL ascii character */
    ELFMAG1 = 'E',                      /*!< 'E' ascii character */
    ELFMAG2 = 'L',                      /*!< 'L' ascii character */
    ELFMAG3 = 'F'                       /*!< 'F' ascii character */
};

/*! \brief EI_CLASS values
 *
 * These values specify word size of ELF object.
 * \see hdr_indexes
 */
enum hdr_class {
    ELFCLASSNONE = 0,                    /*!< Invalid */
    ELFCLASS32 = 1,                      /*!< 32-bit object */
    ELFCLASS64 = 2                       /*!< 64-bit object */
};

/*! \brief EI_DATA values
 *
 * These values specify the significance of the ELF object's words.
 * \see hdr_indexes
 */
enum hdr_data {
    ELFDATANONE = 0,                     /*!< Invalid */
    ELFDATA2LSB = 1,                     /*!< Least significative */
    ELFDATA2MSB = 2                      /*!< Most significative */
};

/*! \brief EI_VERSION and Elf32_Ehdr::e_version values
 *
 * These values specify the version of the ELF object.
 * \see hdr_indexes
 */
enum hdr_e_version {
    EV_NONE = 0,                         /*!< Invalid version */
    EV_CURRENT = 1                       /*!< Current version */
};

/*! \brief Elf32_Ehdr::e_type field values */
enum hdr_e_type {
    ET_NONE = 0,                         /*!< No file type */
    ET_REL = 1,                          /*!< Relocatable */
    ET_EXEC = 2,                         /*!< Executable */
    ET_DYN = 3,                          /*!< Shared object */
    ET_CORE = 4,                         /*!< Core file */
    ET_LOPROC = 0xff00,                  /*!< Processor specific */
    ET_HIPROC = 0xffff                   /*!< Processor specific */
};

/*! \brief Elf32_Ehdr::e_machine filed values */
enum hdr_e_machine {
    EM_NONE = 0,                         /*!< No machine */
    EM_M32 = 1,                          /*!< AT&T WE 32100 */
    EM_SPARC = 2,                        /*!< SPARC */
    EM_386 = 3,                          /*!< Intel 80386 */
    EM_68K = 4,                          /*!< Motorola 68000 */
    EM_88K = 5,                          /*!< Motorola 88000 */
    EM_860 = 7,                          /*!< Intel 80860 */
    EM_MIPS = 8,                         /*!< MIS RS3000 Big Endian */
    EM_MIPS_RS4_BE = 10                  /*!< MIS RS3000 Big Endian */
};

/*@}*/

/*! \addtogroup elfTypComposite */
/*@{*/
/*! \brief Section header
 *
 * A program section may contain instructions, data, symbols, relocation
 * information and other information.
 *
 * The section headers are stored as an array of memory chunks. The file
 * offset of the array, the size of each element and the number of
 * elements are stored into the main ELF header.
 */

typedef struct {
    Elf32_Word      sh_name;             /*!< Index of the name */
    Elf32_Word      sh_type;             /*!< Type of section */
    Elf32_Word      sh_flags;            /*!< Section flags */
    Elf32_Addr      sh_addr;             /*!< Virtual memory address (VMA) */
    Elf32_Off       sh_offset;           /*!< Referred section position */
    Elf32_Word      sh_size;             /*!< Referred section size */
    Elf32_Word      sh_link;             /*!< Link for other section headers */
    Elf32_Word      sh_info;             /*!< Extra informations */
    Elf32_Word      sh_addralign;        /*!< Alignment constraints */
    Elf32_Word      sh_entsize;          /*!< Size of section's sub-entries */
                                         /*   (0 if there's no sub-entries) */
} Elf32_Shdr;

/*@}*/

/*! \addtogroup elfConstants */
/*@{*/

/*! \brief Reserved header indexes */
enum reserv_idx {
    SHN_UNDEF = 0,                       /*!< Undefined section */
    SHN_LORESERVE = 0xff00,              /*!< Lower bound (inclusive) of the */
                                         /*!< reserved range */
    SHN_LOPROC = 0xff00,                 /*!< Processor specific low bound */
    SHN_HIPROC = 0xff1f,                 /*!< Processor specific high bound */
    SHN_ABS = 0xfff1,                    /*!< Absoulute references values */
    SHN_COMMON = 0xfff2,                 /*!< Common symbols */
    SHN_HIRESERVE = 0xffff               /*!< Upper bound (inclusive) of the */
                                         /*!< reserved range */
};

/*! \brief Elf32_Shdr::sh_type field values */
enum shdr_sh_type {
    SHT_NULL = 0,                        /*!< Section header inactive */
    SHT_PROGBITS = 1,                    /*!< Program defined content */
    SHT_SYMTAB = 2,                      /*!< Contains link editing symbols */
    SHT_STRTAB = 3,                      /*!< Contains a string table */
    SHT_RELA = 4,                        /*!< Contains relocation entries */
    SHT_HASH = 5,                        /*!< Contains a symbol hash table */
    SHT_DYNAMIC = 6,                     /*!< Information for dynamic linking */
    SHT_NOTE = 7,                        /*!< Note section */
    SHT_NOBITS = 8,                      /*!< Contains no data, conceptual */
                                         /*   offset */
    SHT_REL = 9,                         /*!< Contains relocation entries
                                          *   without addends */
    SHT_SHLIB = 10,                      /*!< Reserved */
    SHT_DYNSYM = 11,                     /*!< Contains link editing symbols */
    SHT_LOPROC = 0x70000000,             /*!< Lower bound (inclusive) for */
                                         /*   processor specific types */
    SHT_HIPROC = 0x7FFFFFFF,             /*!< Upper bound (inclusive) for */
                                         /*   processor specific types */
    SHT_LOUSER = 0x80000000,             /*!< Lower bound (inclusive) for */
                                         /*   application programs */
    SHT_HIUSER = 0xFFFFFFFF              /*!< Upper bound (inclusive) for */
                                         /*   papplication programs */
};

/*! \brief Elf32_Shdr::sh_flags field values, used as bitwise or */
enum shdr_sh_flags {
    SHF_WRITE = 0x1,                     /*!< Writable by process */
    SHF_ALLOC = 0x2,                     /*!< Occupies memory only during */
                                         /*   execution */
    SHF_EXECINSTR = 0x4,                 /*!< Executable code */
    SHF_MASKPROC = 0xf0000000            /*!< Mask for processor specific */
                                         /*   flags */
};

/*@}*/

/*! \addtogroup elfTypComposite */
/*@{*/

/*! \brief Symbols header 
 *
 * A symbol labels a single piece of information: a data object, a
 * function, a section to be relocated or the name of a source file
 * associated with the object file.
 *
 * The symbol headers are stored as an array of memory chunks. The file
 * offset of the array, the size of each element and the number of
 * elements are stored into the main ELF header.
 */
typedef struct {
    Elf32_Word      st_name;            /*!< Name index */
    Elf32_Addr      st_value;           /*!< Symbol value */
    Elf32_Word      st_size;            /*!< Size in bytes */
    unsigned char   st_info;            /*!< Symbol type and binding */
                                        /*!< attributes. */
    unsigned char   st_other;           /*!< No meaning */
    Elf32_Half      st_shndx;           /*!< Belonging section index */
} Elf32_Sym;

/*! \brief Elf32_Sym::st_info bind extraction */
#define ELF32_ST_BIND(i)    ((i)>>4)                

/*! \brief Elf32_Sym::st_info type extraction */
#define ELF32_ST_TYPE(i)    ((i)&0xf)

/*! \brief Elf32_Sym::st_info composition */
#define ELF32_ST_INFO(b,t)  (((b)<<4)+((t)&0xf))

/*! \brief Elf32_Sym::st_info binding values */
enum sym_st_info_bindings {
    STB_LOCAL = 0,                      /*!< Locally scoped symbol */
    STB_GLOBAL = 1,                     /*!< Globally scoped symbol */
    STB_WEAK = 2,                       /*!< Globally scoped, lower */
                                        /*   precedence */
    STB_LOPROC = 13,                    /*!< Low bound (inclusive) for */
                                        /*   processor specific binding */
    STB_HIPROC = 15                     /*!< High bound (inclusive) for */
                                        /*   processor specific binding */
};

/*! \brief Elf32_Sym::st_info type values */
enum sym_st_info_type {
    STT_NOTYPE = 0,                     /*!< Not specified */
    STT_OBJECT = 1,                     /*!< Data object */
    STT_FUNC = 2,                       /*!< Function or executable */
    STT_SECTION = 3,                    /*!< Section (used for
                                         *   relocation) */
    STT_FILE = 4,                       /*!< Source file associated with
                                         *   the object file */
    STT_LOPROC = 13,                    /*!< Low bound (inclusive) for */
                                        /*   processor specific type */
    STT_HIPROC = 15                     /*!< High bound (inclusive) for */
                                        /*   processor specific type */
};

/*@}*/

/*! \addtogroup elfFunctions */
/*@{*/

/*! \brief ELF Hashing function.
 *
 * This function calculates the hash value of a symbol name, used on elf
 * hash tables (.hash sections).
 *
 * \param name The name of the symbol;
 * \return The calculated hash value.
 */
unsigned long elf_hash(const unsigned char *name);

/*@}*/

/*! \addtogroup elfTypComposite */
/*@{*/

/*! \brief Program header.
 *
 * Program headers describe segments used to achieve loading and dynamic
 * linking of executables and dynamic libraries.
 *
 * Program headers are stored as an array of memory chunks. The file
 * offset of the array, the size of each element and the number of
 * elements are stored into the main ELF header.
 */
typedef struct {
    Elf32_Word      p_type;             /*!< Type of segment. */
    Elf32_Off       p_offset;           /*!< Offset from the file's
                                         *   beginning of the first byte of
                                         *   the segment. */
    Elf32_Addr      p_vaddr;            /*!< Virtual address of the first
                                         *   byte. */
    Elf32_Addr      p_paddr;            /*!< Reserved for phisical
                                         *   address. */
    Elf32_Word      p_filesz;           /*!< Size of the segment's file
                                         *   image. */
    Elf32_Word      p_memsz;            /*!< Size of the segment's memory
                                         *   image. */
    Elf32_Word      p_flags;            /*!< Segment flags. */
    Elf32_Word      p_align;            /*!< Segment alignment. */
} Elf32_Phdr;

/*@}*/

/*! \addtogroup elfConstants */
/*@{*/

/*! \brief Elf32_Phdr::p_type field values. */
enum phdr_p_type {
    PT_NULL = 0,                        /*!< Array element unused */
    PT_LOAD = 1,                        /*!< Loadable segment. */
    PT_DYNAMIC = 2,                     /*!< Element specifying dynamic
                                         *   linking info. */
    PT_INTERP = 3,                      /*!< Null terminated path of
                                         *   interpreter. */
    PT_NOTE = 4,                        /*!< Auxiliary information */
    PT_SHLIB = 5,                       /*!< Reserved. */
    PT_PHDR = 6,                        /*!< Location/size of the program
                                         *   header itself. */
    PT_LOPROC = 0x70000000,             /*!< Processor specific reserved. */
    PT_HIPROC = 0x7fffffff              /*!< Processor specific reserved. */
};

/*! \brief Elf32_Phdr::p_flags field values. */
enum phdr_p_flags {
    PF_X = 0x01,                        /*!< Execute permission */
    PF_W = 0x02,                        /*!< Write permission */
    PF_R = 0x04,                        /*!< Read permission */
    PF_MASKPROC = 0xf0000000            /*!< Mask for processor
                                         *   specific */
};

/*@}*/

/*! \addtogroup elfTypComposite */
/*@{*/

/*! \brief .rel.* sections content.
 *
 * .rel.* sections are marked with the SHT_REL type and contain
 * information on how to modify section contents.
 */
typedef struct {
    Elf32_Addr r_offset;                /*!< Offset of the unit affected
                                         *   by relocation: offset from
                                         *   the beginning of the section
                                         *   for relocable files, virtual
                                         *   address for executables and
                                         *   dynamic linking libraries. */
    Elf32_Word r_info;                  /*!< Information on symbol table
                                         *   respect to relocation must be
                                         *   made and type of relocation
                                         *   to apply. \see ELF32_R_SYM,
                                         *   ELF32_R_TYPE, ELF32_R_INFO */
} Elf32_Rel;

/*! \brief .rela.* sections content.
 *
 * .rela.* sections are marked with the SHT_RELA type and contain
 * information on how to modify section contents.
 */
typedef struct {
    Elf32_Addr r_offset;                /*!< Offset of the unit affected
                                         *   by relocation: offset from
                                         *   the beginning of the section
                                         *   for relocable files, virtual
                                         *   address for executables and
                                         *   dynamic linking libraries. */
    Elf32_Word r_info;                  /*!< Information on symbol table
                                         *   respect to relocation must be
                                         *   made and type of relocation
                                         *   to apply. \see ELF32_R_SYM,
                                         *   ELF32_R_TYPE, ELF32_R_INFO */
    Elf32_Sword r_addend;               /*!< Addend to value of relocation
                                         *   field */
} Elf32_Rela;

/*! \brief Macro for symbol table relocation extraction */
#define ELF32_R_SYM(i)  ((i)>>8)

/*! \brief Macro for type of relocation */
#define ELF32_R_TYPE(i) ((unsigned char)(i))

/*! \brief Macro for Elf32_Rel::r_info field construction */
#define ELF32_R_INFO(s,t) (((s)<<8) + (unsigned char)(t))

/*@}*/

/*! \addtogroup elfTypComposite */
/*@{*/

/*! \brief .dynamic section internal structure
 *
 * The .dynamic section, having type PT_DYNAMIC and labeled by the
 * _DYNAMIC symbol, contains an array of this structures. This kind of
 * information is holded only by executables and shared libraries.
 *
 * Each entry of the array represents a tag used during dynamic
 * relocation.
 */
typedef struct {
    Elf32_Sword d_tag;                  /*!< Interpretation controller:
                                         *   depending on this value the
                                         *   d_un union absumes a
                                         *   different significance */
    union {
        Elf32_Word d_val;               /*!< Integer representation */
        Elf32_Addr d_ptr;               /*!< Pointer representation */
    } d_un;                             /*!< Dynamic entry value */
} Elf32_Dyn;

/*@}*/

/* \addtogroup elfConstants */
/*@{*/

/*! \brief Elf32_Dyn::d_tag field values */
enum dyn_d_tag {
    DT_NULL = 0,                        /*!< End of dynamic array; Ignore
                                         *   d_un */
    DT_NEEDED = 1,                      /*!< Offset of a string, name of a
                                         *   needed library; Use d_val */
    DT_PLTRELSZ = 2,                    /*!< Total size of reolocation
                                         *   entries of the procedure
                                         *   linkage table; Use d_val */
    DT_PLTGOT = 3,                      /*!< Address of procedure linkage
                                         *   table and/or global offset
                                         *   table; Use d_ptr */
    DT_HASH = 4,                        /*!< Address of the symbol hash
                                         *   table; Use d_ptr */
    DT_STRTAB = 5,                      /*!< Address of the string table;
                                         *   Use d_ptr */
    DT_SYMTAB = 6,                      /*!< Address of the symbol table; 
                                         *   Use d_ptr */
    DT_RELA = 7,                        /*!< Address of a part of the
                                             relocation table to build by
                                             concatenation; Use d_ptr */
    DT_RELASZ = 8,                      /*!< Total size of DT_RELA table;
                                             Use d_val */
    DT_RELAENT = 9,                     /*!< Sie of the DT_RELA entry; Use
                                             d_val */
    DT_STRSZ = 10,                      /*!< Size of the string table;
                                             Use d_val */
    DT_SYMENT = 11,                     /*!< Size of a symbol table entry;
                                         *   Use d_val */
    DT_INIT = 12,                       /*!< Address of initialization
                                         *   function; Use d_ptr */
    DT_FINI = 13,                       /*!< Address of termination
                                         *   function; Use d_ptr */
    DT_SONAME = 14,                     /*!< String table offset, name of
                                         *   the shared object; Use d_val */
    DT_RPATH = 15,                      /*!< Library search path string; 
                                         *   Use d_val */
    DT_SYMBOLIC = 16,                   /*!< Start linking from the shared
                                         *   object instead of executable;
                                         *   Ignore d_un */
    DT_REL = 17,                        /*!< Like DT_RELA, implicit addends;
                                         *   Use d_ptr */
    DT_RELSZ = 18,                      /*!< Total size of DT_REL;
                                         *   Use d_val */
    DT_RELENT = 19,                     /*!< Entry size of DT_REL;
                                         *   Use d_val */
    DT_PLTREL = 20,                     /*!< Type of relocation entry, d_val
                                         *   can be either DT_REL or DT_RELA
                                         */
    DT_DEBUG = 21,                      /*!< For debugging, not specified;
                                         *   Use d_ptr */
    DT_TEXTREL = 22,                    /*!< If present non writable
                                         *   segments can be modified;
                                         *   Ignore d_un */
    DT_JMPREL = 23,                     /*!< Address of relocation entries
                                         *   of procedure linkage table;
                                         *   Use d_ptr */
    DT_BIND_NOW = 24,                   /*!< Do not lazy-bind.
                                         *   Ignore d_un */
    DT_LOPROC = 0x70000000,             /*!< Use d_val */
    DT_HIPROC = 0x7fffffff              /*!< Use d_val */
};

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* __defined_elfsword_elf_spec_h */
