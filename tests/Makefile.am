AM_CFLAGS = -I$(top_srcdir)/libelfsword/
AM_LDFLAGS = -L$(top_srcdir)/libelfsword/
LDADD = -ldacav -lelfsword

check_PROGRAMS = 00_allocate 01_itersections 02_itersechash

TESTS = $(check_PROGRAMS)

00_allocate_SOURCES = 00_allocate.c
01_itersections_SOURCES = 01_itersections.c
02_itersechash_SOURCES = 02_itersechash.c
