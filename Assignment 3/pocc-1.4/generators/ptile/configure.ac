dnl
dnl configure.ac: This file is part of the Parametric Tiling project.
dnl
dnl Parametric Tiling: A CLAST-to-CLAST parametric tiling software
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
AC_INIT([ptile], [0.2.1], [tavarage@cse.ohio-state.edu])
## Automatic generation of config.h
AC_CONFIG_HEADERS([ptile/include/ptile/config.h:ptile/include/ptile/config-h.in])
## A common file, which should be included by every source file.
AC_CONFIG_SRCDIR([ptile/include/ptile/common.h])
## Put as most as possible configuration files to an auxialiry
## directory.
AC_CONFIG_AUX_DIR([config])
## Initialize automake. Here, a special tar version that enables
## (very) long filenames.
AM_INIT_AUTOMAKE([1.9 tar-ustar no-define foreign dist-bzip2])
#############################################################################

## Use C language.
AC_PROG_CC
AC_PROG_CXX
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
	 [AC_DEFINE([HAVE_LIBCLOOG], [1], [Define if you have libcloog-isl])],
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
              	             [DIR Location of GMP package]),
              [CPPFLAGS="${CPPFLAGS} -I$withval/include";
	       LDFLAGS="${LDFLAGS} -L$withval/lib";
	       LIBS="-lgmp $LIBS";
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
	 [AC_DEFINE([HAVE_LIBPAST], [1], [Define if you have libpast])],
         [if test "x$with_past" != xcheck; then
           AC_MSG_FAILURE([--with-past was given, but test for past failed])
          fi
         ])
	])

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
       [DEFINE_HAS_SCOPLIB_LIB="-DVECTORIZER_SUPPORTS_SCOPLIB" ],
       [DEFINE_HAS_SCOPLIB_LIB=""
        if test "x$with_scoplib" != xcheck; then
          AC_MSG_FAILURE([Test for ScopLib failed. \ Use --with-scoplib to specify libscoplib path.])
        fi ])
])


dnl /********************************************************************
dnl *	                      Where is IRConverter?			*
dnl ********************************************************************/

dnl Offer --with-irconverter.
AC_ARG_WITH(irconverter,
	AC_HELP_STRING([--with-irconverter=DIR],
	               [DIR Location of Irconverter package]),
		       [with_irconverter=$withval;
		        CPPFLAGS="${CPPFLAGS} -I$withval/include";
			LDFLAGS="${LDFLAGS} -L$withval/lib"],
		       [with_irconverter=yes])
dnl Check for irconverter existence.
AS_IF([test "x$with_irconverter" != xno],
      [AC_SEARCH_LIBS([past2scop_control_only], [irconverter],
       [ ],
       [if test "x$with_irconverter" != xcheck; then
          AC_MSG_FAILURE([Test for Irconverter failed. Use --with-irconverter to specify libirconverter path.])
        fi ])
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
	 [AC_DEFINE([HAVE_LIBPIPLIB], [1], [Define if you have libpiplib64])],
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
       [ ],
       [if test "x$with_candl" != xcheck; then
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
	 [AC_DEFINE([HAVE_LIBSCOPTOOLS], [1], [Define if you have libscoptools])],
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
	 [AC_DEFINE([HAVE_LIBCLASTTOOLS], [1], [Define if you have libclasttools])],
         [if test "x$with_clasttools" != xcheck; then
           AC_MSG_FAILURE([--with-clasttools was given, but test for clasttools failed])
          fi
         ])
	])

dnl /********************************************************************
dnl *	                      Where is ISL?				*
dnl ********************************************************************/

dnl Offer --with-isl.
  AC_ARG_WITH(isl,
	      AC_HELP_STRING([--with-isl=DIR],
              	             [DIR Location of Isl package]),
              [with_isl=$withval;
	       CPPFLAGS="${CPPFLAGS} -I$withval/include";
	       LDFLAGS="${LDFLAGS} -L$withval/lib"
	      ],
              [with_isl=check])
dnl Check for isl existence.
  AS_IF([test "x$with_isl" != xno],
	[AC_SEARCH_LIBS([isl_version], [isl],
	 [LIBS="-lisl $LIBS";
	 ],
         [DEFINE_HAS_ISL_LIB=""
  	  if test "x$with_isl" != xcheck; then
           AC_MSG_FAILURE([Test for Isl failed. Use --with-isl to specify libisl path.])
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
	ptile/Makefile
	src/Makefile
	tests/Makefile
	],
	[test -z "$CONFIG_HEADERS" || echo timestamp > ptile/stamp-h.in])

## Output the result.
AC_OUTPUT
