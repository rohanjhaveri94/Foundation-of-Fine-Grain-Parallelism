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
SUBDIRS 		= doc clastannotation src tests


#############################################################################
ACLOCAL_AMFLAGS		= -I config

CONFIGURE_DEPENDENCIES 	= $(srcdir)/config/clastannotation.m4

m4datadir		= $(datadir)/aclocal

AUX_DIST                =			\
	$(ac_aux_dir)/config.guess		\
	$(ac_aux_dir)/config.sub		\
	$(ac_aux_dir)/install-sh		\
	$(ac_aux_dir)/ltmain.sh			\
	$(ac_aux_dir)/missing


EXTRA_DIST		= 			\
	COPYING					\
	bootstrap.sh


MAINTAINERCLEANFILES 	=					\
	Makefile.in						\
	aclocal.m4						\
	configure						\
	clastannotation/include/clastannotation/config-h.in	\
	clastannotation/stamp-h.in				\
	$(AUX_DIST)


dist-hook:
	(cd $(distdir) && mkdir -p $(ac_aux_dir))
	for file in $(AUX_DIST) $(AUX_DIST_EXTRA); do \
	  cp $$file $(distdir)/$$file; \
	done
#############################################################################
