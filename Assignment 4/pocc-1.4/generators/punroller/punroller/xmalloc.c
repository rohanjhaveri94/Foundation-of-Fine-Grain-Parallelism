/*
 * xmalloc.c: This file is part of the PAST-unroller project.
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
#if HAVE_CONFIG_H
# include <punroller/config.h>
#endif

#include <punroller/common.h>
#include <punroller/error.h>

void *
xmalloc (size_t num)
{
  void *new = malloc (num);
  if (! new)
    punroller_fatal ("Memory exhausted");
  return new;
}

void *
xrealloc (void *p, size_t num)
{
  void *new;

  if (! p)
    return xmalloc (num);

  new = realloc (p, num);
  if (! new)
    punroller_fatal ("Memory exhausted");

  return new;
}

void *
xcalloc (size_t num, size_t size)
{
  void *new = xmalloc (num * size);
  bzero (new, num * size);
  return new;
}