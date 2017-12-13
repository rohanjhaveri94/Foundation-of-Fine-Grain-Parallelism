#
# Makefile.am: This file is part of the PAST-unroller project.
#
# Punroller: a library to perform unroll-and-jam on PAST trees.
#
# Copyright (C) 2011 Louis-Noel Pouchet
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public License
# as published by the Free Software Foundation; either version 3
# of the License, or (at your option) any later version.
#
# The complete GNU Lesser General Public Licence Notice can be found
# as the `COPYING.LESSER' file in the root directory.
#
# Author:
# Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
#

#############################################################################
SUBDIRS			=

#############################################################################
MAINTAINERCLEANFILES	= Makefile.in

INCLUDES		= -I$(top_builddir) -I$(top_srcdir) \
			   -I$(top_builddir)/punroller/include \
		           -I$(top_srcdir)/punroller/include

#############################################################################

pkginclude_HEADERS 	=			\
	include/punroller/error.h		\
	include/punroller/common.h		\
	include/punroller/list.h		\
	include/punroller/punroll.h

lib_LTLIBRARIES 	= libpunroller.la


libpunroller_la_SOURCES 	=		\
	error.c					\
	list.c					\
	punroll.c				\
	xmalloc.c				\
	xstrdup.c				\
	xstrerror.c
