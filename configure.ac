# Copyright (C) 2009 2010 Giovanni [dacav] Simoni
# 						  <simgidacav@gmail.com>
# 
# This program is free software; you can redistribute it and/or 
# modify it under the terms of the GNU General Public License 
# as published by the Free Software Foundation; either 
# version 3 of the License, or (at your option) any later 
# version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
# 

AC_INIT([ElfSword, and ELF analysis library], [0.1],
        [Giovanni Simoni <simgidacav@gmail.com>],
        [elfsword])

AM_INIT_AUTOMAKE([-Wall])

AC_CONFIG_HEADERS([libelfsword/config.h])

AC_PROG_CC
AC_PROG_RANLIB

AC_CHECK_FUNCS([memset])
AC_CHECK_FUNCS([munmap])

AC_CHECK_HEADERS([fcntl.h stdint.h stdlib.h stdbool.h string.h unistd.h assert.h])

AC_CHECK_HEADER([dacav.h],[],
                [AC_MSG_ERROR(libdacav not found.  Please install libdacav)])

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
                 libelfsword/Makefile
                 tests/Makefile])
AC_OUTPUT
