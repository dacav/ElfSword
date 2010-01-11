AM_CFLAGS = -I./ -Wall -Werror -std=gnu99 -pedantic

# Produced library:
lib_LTLIBRARIES = libelfsword.la

# Public headers to be installed in the $PREFIX/include directory:
includetreedir = $(prefix)/include/elfsword
includetree_HEADERS = elfsword/elfmap.h elfsword/errors.h \
                      elfsword/check.h elfsword/sections.h \
                      elfsword/symbols.h elfsword/proghead.h \
                      elfsword/statrel.h elfsword/dynrel.h
include_HEADERS = elfsword.h

libelfsword_la_SOURCES = $(include_HEADERS) \
                        $(includetree_HEADERS) \
                        algorithms.h descriptor.h algorithms.c check.c \
                        elfmap.c sections.c symbols.c proghead.c \
                        statrel.c dynrel.c

