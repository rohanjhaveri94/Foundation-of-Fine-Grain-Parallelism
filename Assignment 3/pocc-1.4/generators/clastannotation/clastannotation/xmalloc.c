/*
 * xmalloc.c: This file is part of the ClastAnnotation project.
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
#if HAVE_CONFIG_H
# include <clastannotation/config.h>
#endif

#include <clastannotation/common.h>
#include <clastannotation/error.h>

void *
xmalloc (size_t num)
{
  void *new = malloc (num);
  if (! new)
    clastannotation_fatal ("Memory exhausted");
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
    clastannotation_fatal ("Memory exhausted");

  return new;
}

void *
xcalloc (size_t num, size_t size)
{
  void *new = xmalloc (num * size);
  bzero (new, num * size);
  return new;
}
