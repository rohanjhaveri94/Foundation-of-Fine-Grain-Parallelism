/*
 * error.h: This file is part of the PAST-unroller project.
 * 
 * Punroller: a library to perform unroll-and-jam on PAST trees.
 * 
 * Copyright (C) 2011 Louis-Noel Pouchet
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
#ifndef PUNROLLER_ERROR_H
# define PUNROLLER_ERROR_H 

#include <punroller/common.h>

BEGIN_C_DECLS

extern const char *program_name;
extern void	set_program_name (const char *argv0);

extern void	punroller_warning (const char *message);
extern void	punroller_error (const char *message);
extern void	punroller_fatal (const char *message);

END_C_DECLS


#endif // PUNROLLER_ERROR_H
