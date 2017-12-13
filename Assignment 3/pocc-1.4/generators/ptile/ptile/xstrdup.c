/*
 * xstrdup.c: This file is part of the Parametric Tiling project.
 * 
 * Parametric Tiling: A CLAST-to-CLAST parametric tiling software
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
#ifndef WITH_DMALLOC

#if HAVE_CONFIG_H
#  include <ptile/config.h>
#endif

#include <ptile/common.h>

char *
xstrdup (const char *string)
{
  return string ? strcpy (xmalloc (strlen (string) + 1), string) : NULL;
}

#endif /* !WITH_DMALLOC */
