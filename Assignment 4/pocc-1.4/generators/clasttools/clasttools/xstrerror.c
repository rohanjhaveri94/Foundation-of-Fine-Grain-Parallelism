/*
 * xstrerror.c: this file is part of the ClastTools project.
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
#if HAVE_CONFIG_H
# include <clasttools/config.h>
#endif

#include <stdio.h>

extern char *strerror ();

/* If strerror returns NULL, we'll format the number into a static buffer.  */
#define ERRSTR_FMT "undocumented error #%d"
static char xstrerror_buf[sizeof ERRSTR_FMT + 20];

/* Like strerror, but result is never a null pointer.  */
char *
xstrerror (int errnum)
{
  char *errstr = strerror (errnum);

  /* If `errnum' is out of range, result might be NULL.  We'll fix that.  */
  if (!errstr)
    {
      sprintf (xstrerror_buf, ERRSTR_FMT, errnum);
      errstr = xstrerror_buf;
    }

  return errstr;
}
