INCLUDES = -I./ -I$(top_srcdir)/includes/
lib_LIBRARIES = libsimple.a

include_HEADERS = simplehash.h
libsimple_a_SOURCES = simplehash.h simplehash.c

check_PROGRAMS = test00

TESTS = $(check_PROGRAMS)

test00_SOURCES = test00.c
test00_LDFLAGS = -L./
test00_LADD    = -lsimple
