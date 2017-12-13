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
SUBDIRS 		= doc punroller src tests


#############################################################################
ACLOCAL_AMFLAGS		= -I config

CONFIGURE_DEPENDENCIES 	= $(srcdir)/config/punroller.m4

m4datadir		= $(datadir)/aclocal

dist_m4data_DATA	= config/punroller.m4

AUX_DIST                =			\
	$(ac_aux_dir)/config.guess		\
	$(ac_aux_dir)/config.sub		\
	$(ac_aux_dir)/install-sh		\
	$(ac_aux_dir)/ltmain.sh			\
	$(ac_aux_dir)/missing


EXTRA_DIST		= 			\
	bootstrap.sh


MAINTAINERCLEANFILES 	=			\
	Makefile.in				\
	aclocal.m4				\
	configure				\
	punroller/include/punroller/config-h.in	\
	punroller/stamp-h.in			\
	$(AUX_DIST)


dist-hook:
	(cd $(distdir) && mkdir -p $(ac_aux_dir))
	for file in $(AUX_DIST) $(AUX_DIST_EXTRA); do \
	  cp $$file $(distdir)/$$file; \
	done
#############################################################################
