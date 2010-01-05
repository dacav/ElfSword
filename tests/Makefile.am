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

AM_CFLAGS = -I$(top_srcdir)/libelfsword/ -Wall -std=gnu99 -Werror -pedantic
AM_LDFLAGS = -L$(top_srcdir)/libelfsword/
LDADD = -ldacav -lelfsword

check_PROGRAMS = 00_allocate 01_itersections 02_secchecknames \
                 03_itersym 04_itersecfilter 05_itersym2 \
                 06_itersym3 07_proghead 08_staticreloc 09_dynamicreloc

TESTS = $(check_PROGRAMS)

00_allocate_SOURCES = 00_allocate.c
01_itersections_SOURCES = 01_itersections.c
02_secchecknames_SOURCES = 02_secchecknames.c
03_itersym_SOURCES = 03_itersym.c
04_itersecfilter_SOURCES = 04_itersecfilter.c
05_itersym2_SOURCES = 05_itersym2.c
06_itersym3_SOURCES = 06_itersym3.c
07_proghead_SOURCES = 07_proghead.c
08_staticreloc_SOURCES = 08_staticreloc.c
09_dynamicreloc_SOURCES = 09_dynamicreloc.c
