/*
 * error.h: this file is part of the ClastTools project.
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
#ifndef CLASTTOOLS_ERROR_H
# define CLASTTOOLS_ERROR_H 

#include <clasttools/common.h>

BEGIN_C_DECLS

extern const char *program_name;
extern void	set_program_name (const char *argv0);

extern void	clasttools_warning (const char *message);
extern void	clasttools_error (const char *message);
extern void	clasttools_fatal (const char *message);

END_C_DECLS


#endif // CLASTTOOLS_ERROR_H
