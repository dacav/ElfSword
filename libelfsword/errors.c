#include <elf.h>

// Index must correspond to elfsword/errors.h enumeration (elf_err_t)
const char *errors[] = {
    "No error",
    "Unable to open the file",
    "Unable to map the file",
    "Invalid ELF object"
}

const char * elf_error(elf_err_t err)
{
    return errors[err];
}
