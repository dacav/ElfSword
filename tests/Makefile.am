# Include files from src
INCLUDES = -I$(top_srcdir)/src/
check_PROGRAMS = test00

# tests to be run during `make check'
TESTS = $(check_PROGRAMS)

test00_SOURCES = test00.c
test00_LDFLAGS = -L$(top_srcdir)/src/
test00_LDADD   = -lelfsword
