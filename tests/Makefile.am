AM_CFLAGS = -I$(top_srcdir)/libelfsword/
AM_LDFLAGS = -L$(top_srcdir)/libelfsword/
LDADD = -ldacav -lelfsword

check_PROGRAMS = 00_allocate 01_itersections 02_itersechash \
                 03_itersym 04_itersecfilter

TESTS = $(check_PROGRAMS)

00_allocate_SOURCES = 00_allocate.c
01_itersections_SOURCES = 01_itersections.c
02_itersechash_SOURCES = 02_itersechash.c
03_itersym_SOURCES = 03_itersym.c
04_itersecfilter_SOURCES = 04_itersecfilter.c
