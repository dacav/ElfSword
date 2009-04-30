#ifndef __ELF_SPECIFICATION_H__
#define __ELF_SPECIFICATION_H__

#include <stdint.h>

/* This file specifies data structures representing the internal of an ELF
 * binary file. For further information please refer to ELF documentation
 */

/* -------------------------------------------------------------------- */
/* Elf specification data types                                         */
/* -------------------------------------------------------------------- */

typedef uint32_t Elf32_Addr;
typedef uint16_t Elf32_Half;
typedef uint32_t Elf32_Off;
typedef int32_t Elf32_Sword;
typedef uint32_t Elf32_Word;

/* -------------------------------------------------------------------- */
/* ELF File header                                                      */
/* -------------------------------------------------------------------- */

#define EI_NINDENT 16
typedef struct {
    unsigned char   e_ident[EI_NINDENT]; /* Magic number */
    Elf32_Half      e_type;              /* Object file type */
    Elf32_Half      e_machine;           /* Architecture */
    Elf32_Word      e_version;           /* Object file version */
    Elf32_Addr      e_entry;             /* VMA for process starting */
    Elf32_Off       e_phoff;             /* Program header table offset */
    Elf32_Off       e_shoff;             /* Section header table offset */
    Elf32_Word      e_flags;             /* Processor flags */
    Elf32_Half      e_ehsize;            /* Header size */
    Elf32_Half      e_phentsize;         /* Header table entry size */
    Elf32_Half      e_phnum;             /* Header number of entries */
    Elf32_Half      e_sheentsize;        /* Section header's size */
    Elf32_Half      e_shnum;             /* Section hdr number of entries */
    Elf32_Half      e_shstndx;           /* Section hdr string table */
} Elf32_Ehdr;

/* e_ident indexes for information positions. This includes magic
 * number for ELF, class, data, version and pad
 */
enum {
    EI_MAG0 = 0,
    EI_MAG1 = 1,
    EI_MAG2 = 2,
    EI_MAG3 = 3,
    EI_CLASS = 4,
    EI_DATA = 5,
    EI_VERSION = 6,
    EI_PAD = 7
};

/* e_ident values for EI_MAG0-3 */
enum {
    ELFMAG0 = 0x7f,
    ELFMAG1 = 'E',
    ELFMAG2 = 'L',
    ELFMAG3 = 'F'
};

/* e_ident values for EI_CLASS */
enum {
    ELFCLASSNONE = 0,                    /* Invalid */
    ELFCLASS32 = 1,                      /* 32-bit object */
    ELFCLASS64 = 2                       /* 64-bit object */
};

/* e_ident values for EI_DATA */
enum {
    ELFDATANONE = 0,                     /* Invalid */
    ELFDATA2LSB = 1,                     /* Least significative */
    ELFDATA2MSB = 2                      /* Most significative */
};

/* e_type field values */
enum {
    ET_NONE = 0,                         /* No file type */
    ET_REL = 1,                          /* Relocatable */
    ET_EXEC = 2,                         /* Executable */
    ET_DYN = 3,                          /* Shared object */
    ET_CORE = 4,                         /* Core file */
    ET_LOPROC = 0xff00,                  /* Processor specific */
    ET_HIPROC = 0xffff                   /* Processor specific */
};

/* e_machine filed values */
enum {
    EM_NONE = 0,                         /* No machine */
    EM_M32 = 1,                          /* AT&T WE 32100 */
    EM_SPARC = 2,                        /* SPARC */
    EM_386 = 3,                          /* Intel 80386 */
    EM_68K = 4,                          /* Motorola 68000 */
    EM_88K = 5,                          /* Motorola 88000 */
    EM_860 = 7,                          /* Intel 80860 */
    EM_MIPS = 8,                         /* MIS RS3000 Big Endian */
    EM_MIPS_RS4_BE = 10                  /* MIS RS3000 Big Endian */
};

/* e_version field values */
enum {
    EV_NONE = 0,                         /* Invalid version */
    EV_CURRENT = 1                       /* Current version */
};

/* -------------------------------------------------------------------- */
/* Section header                                                       */
/* -------------------------------------------------------------------- */

/* The section headers are stored as an array of memory chunks. The file
 * offset of the array, the size of each element and the number of
 * elements are stored into the main ELF header. */

/* The following headers indexes are reserved */
enum {
    SHN_UNDEF = 0,                       /* Undefined section */
    SHN_LORESERVE = 0xff00,              /* Lower bound (inclusive) of the */
                                         /* reserved range */
    SHN_LOPROC = 0xff00,                 /* Processor specific low bound */
    SHN_HIPROC = 0xff1f,                 /* Processor specific high bound */
    SHN_ABS = 0xfff1,                    /* Absoulute references values */
    SHN_COMMON = 0xfff2,                 /* Common symbols */
    SHN_HIRESERVE = 0xffff               /* Upper bound (inclusive) of the */
                                         /* reserved range */
};

typedef struct {
    Elf32_Word      sh_name;             /* Index of the name */
    Elf32_Word      sh_type;             /* Type of section */
    Elf32_Word      sh_flags;            /* Section flags */
    Elf32_Addr      sh_addr;             /* Virtual memory address (VMA) */
    Elf32_Off       sh_offset;           /* Referred section position */
    Elf32_Word      sh_size;             /* Referred section size */
    Elf32_Word      sh_link;             /* Link for other section headers */
    Elf32_Word      sh_info;             /* Extra informations */
    Elf32_Word      sh_addralign;        /* Alignment constraints */
    Elf32_Word      sh_entsize;          /* Size of section's sub-entries */
                                         /* (0 if there's no sub-entries) */
} Elf32_Shdr;

/* sh_type field values */
enum {
    SHT_NULL = 0,                        /* Section header inactive */
    SHT_PROGBITS = 1,                    /* Program defined content */
    SHT_SYMTAB = 2,                      /* Contains link editing symbols */
    SHT_STRTAB = 3,                      /* Contains a string table */
    SHT_RELA = 4,                        /* Contains relocation entries */
    SHT_HASH = 5,                        /* Contains a symbol hash table */
    SHT_DYNAMIC = 6,                     /* Information for dynamic linking */
    SHT_NOTE = 7,                        /* Note section */
    SHT_NOBITS = 8,                      /* Contains no data, conceptual */
                                         /* offset */
    SHT_REL = 9,                         /* Contains relocation entries
                                          * without addends */
    SHT_SHLIB = 10,                      /* Reserved */
    SHT_DYNSYM = 11,                     /* Contains link editing symbols */
    SHT_LOPROC = 0x70000000,             /* Lower bound (inclusive) for */
                                         /* processor specific types */
    SHT_HIPROC = 0x7FFFFFFF,             /* Upper bound (inclusive) for */
                                         /* processor specific types */
    SHT_LOUSER = 0x80000000,             /* Lower bound (inclusive) for */
                                         /* application programs */
    SHT_HIUSER = 0xFFFFFFFF              /* Upper bound (inclusive) for */
                                         /* papplication programs */
};

/* sh_flags field values, used as bitwise or */
enum {
    SHF_WRITE = 0x1,                     /* Writable by process */
    SHF_ALLOC = 0x2,                     /* Occupies memory only during */
                                         /* execution */
    SHF_EXECINSTR = 0x4,                 /* Executable code */
    SHF_MASKPROC = 0xf0000000            /* Mask for processor specific */
                                         /* flags */
};

#endif /* __ELF_SPECIFICATION_H__ */
