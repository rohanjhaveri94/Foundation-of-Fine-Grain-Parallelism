/*
 * annotate.h: This file is part of the ClastAnnotation project.
 *
 * ClastAnnotation: A CLAST translator providing annotated nodes.
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
 *
 */
#ifndef CLASTANNOTATION_ANNOTATE_H
# define CLASTANNOTATION_ANNOTATE_H

# ifndef LINEAR_VALUE_IS_LONGLONG
#  define LINEAR_VALUE_IS_LONGLONG
# endif
# ifndef SCOPLIB_INT_T_IS_LONGLONG
#  define SCOPLIB_INT_T_IS_LONGLONG
# endif
# define CLOOG_SUPPORTS_SCOPLIB
# ifndef CLOOG_INT_GMP
#  define CLOOG_INT_GMP
# endif
# include <scoplib/scop.h>
# include <cloog/cloog.h>
# include <cloog/clast.h>


BEGIN_C_DECLS


extern
int
annotate_par_loops (struct clast_stmt* root, scoplib_scop_p scop);

extern
int
clastannotation_annotate (struct clast_stmt* root, scoplib_scop_p scop);


END_C_DECLS


#endif // CLASTANNOTATION_ANNOTATE_H
