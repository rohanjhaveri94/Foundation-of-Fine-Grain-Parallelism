#
# Makefile.am: This file is part of the ClastAnnotation project.
# 
# ClastAnnotation: A CLAST translator providing annotated nodes.
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
# 

#############################################################################
SUBDIRS			=

#############################################################################
MAINTAINERCLEANFILES	= Makefile.in

INCLUDES		= -I$(top_builddir) -I$(top_builddir)/clastannotation \
			-I$(top_srcdir) -I$(top_srcdir)/clastannotation

#############################################################################


noinst_HEADERS		= clastannotation.h

bin_PROGRAMS		= clastannotation

clastannotation_SOURCES		= clastannotation.c 

clastannotation_LDADD		= $(top_srcdir)/clastannotation/libclastannotation.la
