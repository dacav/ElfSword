INCLUDES = -I./ -I$(top_srcdir)/includes/
AM_CFLAGS = -D_GNU_SOURCE

# Produced library:
lib_LIBRARIES = libelfsword.a

# Public headers to be installed in the $PREFIX/include directory:
include_HEADERS = elf.h elf_spec.h
libelfsword_a_SOURCES = elf.c elf_spec.c elf.h elf_spec.h doc.h

# Include files from src
#check_PROGRAMS = test00

# tests to be run during `make check'
#TESTS = $(check_PROGRAMS)

#test00_SOURCES = test00.c
#test00_LDFLAGS = -L.
#test00_LDADD   = -lelfsword
