#
# Makefile.am: This file is part of the Parametric Tiling project.
# 
# Parametric Tiling: A CLAST-to-CLAST parametric tiling software
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

MAINTAINERCLEANFILES    = Makefile.in

TESTS_ENVIRONMENT       = top_builddir=$(top_builddir) SRCDIR=$(srcdir)

#############################################################################

EXTRA_DIST              = checker.sh

testsubdir              = test_suite

check_SCRIPTS		= checker.sh

## Replace by program names when needed
# check_PROGRAMS = ...
TESTS			 = $(check_SCRIPTS) 

EXTRA_DIST		 += 			\
			empty.test


#############################################################################
distclean-local:
	rm -rf $(testsubdir)
