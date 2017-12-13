#
# Makefile.am: this file is part of the ClastTools project.
# 
# ClastTools, a set of extensions to the standard CLAST hierarchy
# 
# Copyright (C) 2010 Louis-Noel Pouchet
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

#############################################################################
SUBDIRS			=

#############################################################################
MAINTAINERCLEANFILES	= Makefile.in

INCLUDES		= -I$(top_builddir)/src -I$(top_srcdir)/src	\
			  -I$(top_builddir) -I$(top_builddir)/clasttools	\
			  -I$(top_srcdir) -I$(top_srcdir)/clasttools	\
			  -I$(top_builddir)/clasttools/include		\
			  -I$(top_srcdir)/clasttools/include

#############################################################################


noinst_HEADERS		= clasttools.h

bin_PROGRAMS		= clasttools

clasttools_SOURCES		= clasttools.c 

clasttools_LDADD		= $(top_srcdir)/clasttools/libclasttools.la
