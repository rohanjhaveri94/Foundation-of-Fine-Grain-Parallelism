/*
 * list.h: This file is part of the PAST-unroller project.
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
#ifndef PUNROLLER_LIST_H
# define PUNROLLER_LIST_H

# include <punroller/common.h>

BEGIN_C_DECLS

struct list
{
  void*		data;
  struct list*	next;
};

typedef struct list List;


extern List*	list_new(void *data);
extern List*	list_cons(List *head, List *tail);
extern List*	list_tail(List *head);
extern size_t	list_length(List *head);


END_C_DECLS


#endif // PUNROLLER_LIST_H
