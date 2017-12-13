dnl
dnl configure.ac: This file is part of the ClastAnnotation project.
dnl
dnl ClastAnnotation: A CLAST translator providing annotated nodes.
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
dnl

#############################################################################
## Require for autoconf >= 2.54.
AC_PREREQ([2.54])

#############################################################################
## Fill here the @bug email adress.
AC_INIT([clastannotation], [0.1.0], [pouchet@cse.ohio-state.edu])
## Automatic generation of config.h
AC_CONFIG_HEADERS([clastannotation/include/clastannotation/config.h:clastannotation/include/clastannotation/config-h.in])
## A common file, which should be included by every source file.
AC_CONFIG_SRCDIR([clastannotation/include/clastannotation/common.h])
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
dnl *	                      Where is ScopLib?				*
dnl ********************************************************************/

dnl Offer --with-scoplib.
AC_ARG_WITH(scoplib,
	AC_HELP_STRING([--with-scoplib=DIR],
	               [DIR Location of ScopLib package]),
		       [with_scoplib=$withval;
		        CPPFLAGS="${CPPFLAGS} -I$withval/include";
			LDFLAGS="${LDFLAGS} -L$withval/lib"],
		       [with_scoplib=check])
dnl Check for scoplib existence.
AS_IF([test "x$with_scoplib" != xno],
      [AC_SEARCH_LIBS([scoplib_scop_read], [scoplib],
       [LIBS="-lscoplib $LIBS"; DEFINE_HAS_SCOPLIB_LIB="-DVECTORIZER_SUPPORTS_SCOPLIB" ],
       [DEFINE_HAS_SCOPLIB_LIB=""
        if test "x$with_scoplib" != xcheck; then
          AC_MSG_FAILURE([Test for ScopLib failed. \ Use --with-scoplib to specify libscoplib path.])
        fi ])
])


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
dnl *	                      Where is PIPLib?				*
dnl ********************************************************************/

dnl Offer --with-piplib.
  AC_ARG_WITH(piplib,
	      AC_HELP_STRING([--with-piplib=DIR],
              	             [DIR Location of PipLib package]),
              [with_piplib=$withval;
	       CPPFLAGS="${CPPFLAGS} -I$withval/include";
	       LDFLAGS="${LDFLAGS} -L$withval/lib"
	      ],
              [with_piplib=check])
dnl Check for piplib existence.
  AS_IF([test "x$with_piplib" != xno],
	[AC_SEARCH_LIBS([pip_solve], [piplib64],
	 [LIBS="-lpiplib64 $LIBS";
	  AC_DEFINE([HAVE_LIBPIPLIB], [1], [Define if you have libpiplib64])
         ],
         [if test "x$with_piplib" != xcheck; then
           AC_MSG_FAILURE([--with-piplib was given, but test for piplib failed])
          fi
         ])
	])

dnl /********************************************************************
dnl *	                      Where is Candl?				*
dnl ********************************************************************/

dnl Offer --with-candl.
AC_ARG_WITH(candl,
	AC_HELP_STRING([--with-candl=DIR],
	               [DIR Location of Candl package]),
		       [with_candl=$withval;
		        CPPFLAGS="${CPPFLAGS} -I$withval/include";
			LDFLAGS="${LDFLAGS} -L$withval/lib"],
		       [with_candl=check])
dnl Check for candl existence.
AS_IF([test "x$with_candl" != xno],
      [AC_SEARCH_LIBS([candl_program_read], [candl],
       [LIBS="-lcandl $LIBS"; DEFINE_HAS_CANDL_LIB="-DVECTORIZER_SUPPORTS_CANDL" ],
       [DEFINE_HAS_CANDL_LIB=""
        if test "x$with_candl" != xcheck; then
          AC_MSG_FAILURE([Test for Candl failed. Use --with-candl to specify libcandl path.])
        fi ])
])


dnl /********************************************************************
dnl *	                      Where is ScopTools?			*
dnl ********************************************************************/

dnl Offer --with-scoptools.
  AC_ARG_WITH(scoptools,
	      AC_HELP_STRING([--with-scoptools=DIR],
              	             [DIR Location of Scoptools package]),
              [with_scoptools=$withval;
	       CPPFLAGS="${CPPFLAGS} -I$withval/include";
	       LDFLAGS="${LDFLAGS} -L$withval/lib"
	      ],
              [with_scoptools=check])
dnl Check for scoptools existence.
  AS_IF([test "x$with_scoptools" != xno],
	[AC_SEARCH_LIBS([scoptools_clast2scop], [scoptools],
	 [LIBS="-lscoptools $LIBS";
	  AC_DEFINE([HAVE_LIBSCOPTOOLS], [1], [Define if you have libscoptools])
         ],
         [if test "x$with_scoptools" != xcheck; then
           AC_MSG_FAILURE([--with-scoptools was given, but test for scoptools failed])
          fi
         ])
	])


dnl /********************************************************************
dnl *	                      Where is ClastTools?			*
dnl ********************************************************************/

dnl Offer --with-clasttools.
  AC_ARG_WITH(clasttools,
	      AC_HELP_STRING([--with-clasttools=DIR],
              	             [DIR Location of ClastTools package]),
              [with_clasttools=$withval;
	       CPPFLAGS="${CPPFLAGS} -I$withval/include";
	       LDFLAGS="${LDFLAGS} -L$withval/lib"
	      ],
              [with_clasttools=check])
dnl Check for clasttools existence.
  AS_IF([test "x$with_clasttools" != xno],
	[AC_SEARCH_LIBS([clasttols_clast_pprint_extended], [clasttools],
	 [LIBS="-lclasttools $LIBS";
	  AC_DEFINE([HAVE_LIBCLASTTOOLS], [1], [Define if you have libclasttools])
         ],
         [if test "x$with_clasttools" != xcheck; then
           AC_MSG_FAILURE([--with-clasttools was given, but test for clasttools failed])
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
	clastannotation/Makefile
	src/Makefile
	tests/Makefile
	],
	[test -z "$CONFIG_HEADERS" || echo timestamp > clastannotation/stamp-h.in])

## Output the result.
AC_OUTPUT
