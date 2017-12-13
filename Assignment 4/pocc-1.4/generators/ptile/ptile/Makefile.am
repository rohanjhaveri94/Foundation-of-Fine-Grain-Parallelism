#
# Makefile.am: This file is part of the PTile project.
#
# PTile: A PAST-to-PAST parametric tiling software
#
# Copyright (C) 2010,2011 Sanket Tavarage
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

INCLUDES		= -I$(top_builddir) -I$(top_srcdir)	\
			   -I$(top_builddir)/ptile/include	\
		           -I$(top_srcdir)/ptile/include


#############################################################################

pkginclude_HEADERS 	=				\
	include/ptile/PTile.hpp				\
	include/ptile/AstGenerator.hpp			\
	include/ptile/ConvexHullFormer.hpp		\
	include/ptile/ExpressionLibrary.hpp		\
	include/ptile/GenericUtility.hpp		\
	include/ptile/InputReaderParser.hpp		\
	include/ptile/PtileClasses.hpp			\
	include/ptile/Polynomial.hpp			\
	include/ptile/RSFME.hpp				\
	include/ptile/ScoplibToExpressionConverter.hpp	\
	include/ptile/Term.hpp				\
	include/ptile/TileLoopInserter.hpp		\
	include/ptile/Tiler.hpp				\
	include/ptile/TilingDriver.hpp			\
	include/ptile/TilingPostProcessor.hpp		\
	include/ptile/VariableExtractor.hpp		\
	include/ptile/common.h				\
	include/ptile/error.h				\
	include/ptile/options.h				\
	include/ptile/pocc_driver.h			\
	include/ptile/Expression.hpp			\
	include/ptile/FullTileMaker.hpp			\
	include/ptile/EvolveTile_outerParallel.hpp	\
        include/ptile/EvolveTile_wavefrontParallel.hpp	\
	include/ptile/AstOptimizer.hpp                  \
        include/ptile/SecondLevelTiler.hpp

lib_LTLIBRARIES 	= libptile.la


libptile_la_SOURCES 	=			\
	pocc_driver.c				\
	error.c					\
	parametrictiling.cpp			\
	options.cpp				\
	xmalloc.c				\
	xstrdup.c				\
	xstrerror.c				\
	ConvexHullFormer.cpp			\
	Polynomial.cpp				\
	Term.cpp				\
	Expression.cpp				\
	ExpressionLibrary.cpp			\
	GenericUtility.cpp			\
	AstGenerator.cpp			\
	ScoplibToExpressionConverter.cpp	\
	TileLoopInserter.cpp			\
	InputReaderParser.cpp			\
	RSFME.cpp				\
	TilingDriver.cpp			\
	Tiler.cpp				\
	FullTileMaker.cpp			\
	EvolveTile_outerParallel.cpp		\
	EvolveTile_wavefrontParallel.cpp	\
	AstOptimizer.cpp                        \
	SecondLevelTiler.cpp



