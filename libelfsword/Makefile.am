INCLUDES = -I./elfsword/ -I./ -I$(top_srcdir)/includes/
AM_CFLAGS = -D_GNU_SOURCE

# Produced library:
lib_LIBRARIES = libelfsword.a

# Public headers to be installed in the $PREFIX/include directory:
includeelfsworddir = $(prefix)/include/elfsword
includeelfsword_HEADERS = elfsword/elf.h elfsword/elf_spec.h
include_HEADERS = elfsword.h
libelfsword_a_SOURCES = $(include_HEADERS) \
                        $(includetree_HEADERS) \
                        elf.c elf_spec.c

# Include files from src
#check_PROGRAMS = test00

# tests to be run during `make check'
#TESTS = $(check_PROGRAMS)

#test00_SOURCES = test00.c
#test00_LDFLAGS = -L.
#test00_LDADD   = -lelfsword
