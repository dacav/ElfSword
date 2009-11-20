AC_INIT([ElfSword, and ELF analysis library], [0.1],
        [Giovanni Simoni <simgidacav@gmail.com>],
        [elfsword])

AM_INIT_AUTOMAKE

AC_CONFIG_HEADERS([includes/config.h])

AC_PROG_CC
AC_PROG_RANLIB

AC_CHECK_FUNCS([memset])
AC_CHECK_FUNCS([munmap])

AC_CHECK_HEADERS([fcntl.h stdint.h stdlib.h string.h unistd.h assert.h])

#AC_CHECK_HEADER([dacav.h],[],
#                [AC_MSG_ERROR(libdacav not found.  Please install libdacav)])

AC_C_INLINE
AC_FUNC_MALLOC
AC_FUNC_MMAP
AC_HEADER_STDBOOL

AC_TYPE_SIZE_T
AC_TYPE_INT32_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

AC_CONFIG_FILES([Makefile
                 includes/Makefile
                 libelfsword/Makefile])
AC_OUTPUT
