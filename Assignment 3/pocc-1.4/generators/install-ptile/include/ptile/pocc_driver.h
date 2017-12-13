/*
 * foo.h: This file is part of the PTile
 * 
 * PTile: A PAST-to-PAAST parametric tiling software
 * 
 * Copyright (C) 2010 Sanket Tavargeri
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
 * Sanket Tavargeri <sanket.tavargeri@gmail.com>
 * 
 */
#ifndef PTILE_POCC_DRIVER_H
# define PTILE_POCC_DRIVER_H

# ifndef SCOPLIB_INT_T_IS_LONGLONG
#  define SCOPLIB_INT_T_IS_LONGLONG
# endif
# ifndef LINEAR_VALUE_IS_LONGLONG
#  define LINEAR_VALUE_IS_LONGLONG
# endif
# include <scoplib/scop.h>
# ifndef CLOOG_INT_GMP
#  define CLOOG_INT_GMP
# endif
# include <past/past.h>
# include <ptile/options.h>


BEGIN_C_DECLS

extern
void
ptile_pocc_driver (scoplib_scop_p program,
		   s_past_node_t* root,
		   s_ptile_options_t* ptopts);



END_C_DECLS


#endif // PTILE_POCC_DRIVER_H
