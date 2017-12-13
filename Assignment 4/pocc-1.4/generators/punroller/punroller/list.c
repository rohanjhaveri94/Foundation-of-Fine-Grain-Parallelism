/*
 * list.c: This file is part of the PAST-unroller project.
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
#include <punroller/list.h>

List*
list_new (void *data)
{
  List *res = XMALLOC (List, 1);

  res->next = NULL;
  res->data = data;

  return res;
}

List*
list_cons (List* head, List* tail)
{
  head->next = tail;
  return head;
}


List*
list_tail (List *head)
{
  return head->next;
}


size_t
list_length (List *head)
{
  size_t n;
  
  for (n = 0; head; ++n)
    head = head->next;

  return n;
}
