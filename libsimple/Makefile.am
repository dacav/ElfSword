INCLUDES = -I./simple/ -I./ -I$(top_srcdir)/includes/
DIST_SUBDIRS = simple 
lib_LIBRARIES = libsimple.a

includesimpledir = $(prefix)/include/simple
include_HEADERS = simple.h
includesimple_HEADERS = simple/simplehash.h simple/simpletypes.h
libsimple_a_SOURCES = $(include_HEADERS) \
                      $(includetreedir_HEADERS) \
                      simplehash.c 

check_PROGRAMS = test00

TESTS = $(check_PROGRAMS)

test00_SOURCES = test00.c
test00_LDFLAGS = -L./
test00_LDADD   = -lsimple
