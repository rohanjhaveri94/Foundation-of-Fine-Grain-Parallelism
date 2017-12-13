dnl
dnl configure.ac: this file is part of the ClastTools project.
dnl
dnl ClastTools, a set of extensions to the standard CLAST hierarchy
dnl
dnl Copyright (C) 2010 Louis-Noel Pouchet
dnl
dnl This program is free software; you can redistribute it and/or
dnl modify it under the terms of the GNU Lesser General Public License
dnl as published by the Free Software Foundation; either version 3
dnl of the License, or (at your option) any later version.
dnl
dnl The complete GNU Lesser General Public Licence Notice can be found
dnl as the `COPYING.LESSER' file in the root directory.
dnl
dnl Author:
dnl Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>

#############################################################################
## Require for autoconf >= 2.54.
AC_PREREQ([2.54])

#############################################################################
## Fill here the @bug email adress.
AC_INIT([clasttools], [0.2.2], [pouchet@cse.ohio-state.edu])
## Automatic generation of config.h
AC_CONFIG_HEADERS([clasttools/include/clasttools/config.h:clasttools/include/clasttools/config-h.in])
## A common file, which should be included by every source file.
AC_CONFIG_SRCDIR([clasttools/include/clasttools/common.h])
## Put as most as possible configuration files to an auxialiry
## directory.
AC_CONFIG_AUX_DIR([config])
## Initialize automake. Here, a special tar version that enables
## (very) long filenames.
AM_INIT_AUTOMAKE([1.9 tar-ustar no-define foreign dist-bzip2])
#############################################################################

## Use C language.
AC_PROG_CC
## Use libtool to generate libraries.
AC_PROG_LIBTOOL


## Check for some essential headers.
AC_HEADER_STDC
AC_CHECK_HEADERS([errno.h stddef.h stdlib.h string.h strings.h unistd.h])

## Check for some essential C properties.
AC_C_CONST
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_C_VOLATILE


dnl /********************************************************************
dnl *	                      Where is CLooG?				*
dnl ********************************************************************/

dnl Offer --with-cloog.
  AC_ARG_WITH(cloog,
	      AC_HELP_STRING([--with-cloog=DIR],
              	             [DIR Location of Cloog package]),
              [with_cloog=$withval;
	       CPPFLAGS="${CPPFLAGS} -I$withval/include";
	       LDFLAGS="${LDFLAGS} -L$withval/lib"
	      ],
              [with_cloog=yes])
dnl Check for cloog existence.
  AS_IF([test "x$with_cloog" != xno],
	[AC_SEARCH_LIBS([cloog_program_generate], [cloog-isl],
	 [LIBS="-lcloog-isl $LIBS";
	  AC_DEFINE([HAVE_LIBCLOOG], [1], [Define if you have libcloog-isl])
         ],
         [if test "x$with_cloog" != xcheck; then
           AC_MSG_FAILURE([--with-cloog was given, but test for cloog failed])
          fi
         ])
	])

dnl /********************************************************************
dnl *	                 Where are GMP headers?				*
dnl ********************************************************************/

dnl Offer --with-gmp-include.
  AC_ARG_WITH(gmp-prefix,
	      AC_HELP_STRING([--with-gmp-prefix=DIR],
              	             [DIR Location of GMP package (only headers are needed)]),
              [CPPFLAGS="${CPPFLAGS} -I$withval/include";
	      ])


dnl /********************************************************************
dnl *	                      Where is PAST?				*
dnl ********************************************************************/

dnl Offer --with-past.
  AC_ARG_WITH(past,
	      AC_HELP_STRING([--with-past=DIR],
              	             [DIR Location of Past package]),
              [with_past=$withval;
	       CPPFLAGS="${CPPFLAGS} -I$withval/include";
	       LDFLAGS="${LDFLAGS} -L$withval/lib"
	      ],
              [with_past=yes])
dnl Check for past existence.
  AS_IF([test "x$with_past" != xno],
	[AC_SEARCH_LIBS([past_pprint], [past],
	 [LIBS="-lpast $LIBS";
	  AC_DEFINE([HAVE_LIBPAST], [1], [Define if you have libpast-isl])
         ],
         [if test "x$with_past" != xcheck; then
           AC_MSG_FAILURE([--with-past was given, but test for past failed])
          fi
         ])
	])

#############################################################################
## Variable substitutions.
AC_SUBST(ac_aux_dir)

#############################################################################
## Configure Makefiles.
AC_CONFIG_FILES([
	Makefile
	doc/Makefile
	clasttools/Makefile
	src/Makefile
	tests/Makefile
	],
	[test -z "$CONFIG_HEADERS" || echo timestamp > clasttools/stamp-h.in])

## Output the result.
AC_OUTPUT
