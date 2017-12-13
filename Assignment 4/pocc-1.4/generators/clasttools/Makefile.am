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
SUBDIRS 		= doc clasttools src tests


#############################################################################
ACLOCAL_AMFLAGS		= -I config

CONFIGURE_DEPENDENCIES 	= $(srcdir)/config/clasttools.m4

m4datadir		= $(datadir)/aclocal

dist_m4data_DATA	= config/clasttools.m4

AUX_DIST                =			\
	$(ac_aux_dir)/config.guess		\
	$(ac_aux_dir)/config.sub		\
	$(ac_aux_dir)/install-sh		\
	$(ac_aux_dir)/ltmain.sh			\
	$(ac_aux_dir)/missing


EXTRA_DIST		= 			\
	COPYING.LESSER				\
	bootstrap.sh


MAINTAINERCLEANFILES 	=				\
	Makefile.in					\
	aclocal.m4					\
	configure					\
	clasttools/include/clasttools/config-h.in	\
	clasttools/stamp-h.in				\
	$(AUX_DIST)


dist-hook:
	(cd $(distdir) && mkdir -p $(ac_aux_dir))
	for file in $(AUX_DIST) $(AUX_DIST_EXTRA); do \
	  cp $$file $(distdir)/$$file; \
	done
#############################################################################
