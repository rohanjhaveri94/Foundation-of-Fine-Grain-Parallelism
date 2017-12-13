/*
 * utils.h: this file is part of the ClastTools project.
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
#ifndef CLASTTOOLS_UTILS_H
# define CLASTTOOLS_UTILS_H

# include <clasttools/common.h>

# ifndef CLOOG_INT_GMP
#  define CLOOG_INT_GMP
# endif
# include <cloog/cloog.h>
# include <cloog/clast.h>
# include <clasttools/clastext.h>


BEGIN_C_DECLS

extern
int
clasttools_utils_number_parfor (struct clast_stmt* root);

extern
int
clasttools_utils_number_loops (struct clast_stmt* root);

extern
struct clast_stmt*
clasttools_utils_get_parent (struct clast_stmt* root, struct clast_stmt* node);

extern
struct clast_stmt**
clasttools_utils_get_pointer (struct clast_stmt* root, struct clast_stmt* node);

extern
int
clasttools_utils_contains_loops (struct clast_stmt* root);

extern
struct clast_stmt**
clasttools_utils_get_all_inner_loops (struct clast_stmt* root);

extern
struct clast_expr*
clasttools_utils_dup_expr (struct clast_expr* e);

extern
struct clast_stmt*
clasttools_utils_dup_stmt (struct clast_stmt* s);

extern
struct clast_stmt**
clasttools_utils_get_loops_at_level (struct clast_stmt* s,
				     int level);


END_C_DECLS


#endif // CLASTTOOLS_UTILS_H
