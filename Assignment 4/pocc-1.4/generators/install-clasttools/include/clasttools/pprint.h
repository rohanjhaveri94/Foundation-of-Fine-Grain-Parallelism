/*
 * pprint.h: this file is part of the ClastTools project.
 *
 * ClastTools, a set of extensions to the standard CLAST hierarchy
 *
 * Copyright (C) 2010 Louis-Noel Pouchet
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * The complete GNU Lesser General Public Licence Notice can be found
 * as the `COPYING.LESSER' file in the root directory.
 *
 * Author:
 * Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
 */
#ifndef CLASTTOOLS_PPRINT_H
# define CLASTTOOLS_PPRINT_H

# include <clasttools/common.h>

# ifndef CLOOG_INT_GMP
#  define CLOOG_INT_GMP
# endif
# include <cloog/cloog.h>
# include <cloog/clast.h>


BEGIN_C_DECLS


extern
void clasttols_clast_pprint_extended(FILE *foo, struct clast_stmt *root,
				     int indent, CloogOptions *options);
extern
void clasttols_clast_pprint_debug(FILE *foo, struct clast_stmt *root,
				  int indent, CloogOptions *options);


END_C_DECLS


#endif // CLASTTOOLS_PPRINT_H
