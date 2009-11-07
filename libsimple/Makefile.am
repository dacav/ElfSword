INCLUDES = -I./simple/ -I./ -I$(top_srcdir)/includes/
DIST_SUBDIRS = simple 
lib_LIBRARIES = libsimple.a

include_HEADERS = simple.h

includesimpledir = $(prefix)/include/simple
includesimple_HEADERS = simple/simplehash.h \
                        simple/simplelist.h \
                        simple/simpletypes.h

libsimple_a_SOURCES = $(include_HEADERS) \
                      $(includetreedir_HEADERS) \
                      simplehash.c \
                      simplelist.c

check_PROGRAMS = test00 test01 test02

TESTS = $(check_PROGRAMS)

test00_SOURCES = test00.c
test00_LDFLAGS = -L./
test00_LDADD   = -lsimple

test01_SOURCES = test01.c
test01_LDFLAGS = -L./
test01_LDADD   = -lsimple

test02_SOURCES = test02.c
test02_LDFLAGS = -L./
test02_LDADD   = -lsimple

