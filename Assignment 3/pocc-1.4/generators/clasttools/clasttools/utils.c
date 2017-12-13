/*
 * utils.c: this file is part of the ClastTools project.
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

#include <clasttools/common.h>
#include <clasttools/utils.h>


static
void
traverse_clast_nparf (struct clast_stmt* s, int* count, int par_only)
{
  // Traverse the clast.
  for ( ; s; s = s->next)
    {
      if (CLAST_STMT_IS_A(s, stmt_parfor))
	{
	  (*count)++;
	  traverse_clast_nparf (((struct clast_parfor*)s)->body, count,
				par_only);
	}
      else if (CLAST_STMT_IS_A(s, stmt_for))
	{
	  if (par_only == 0)
	    (*count)++;
	  traverse_clast_nparf (((struct clast_for*)s)->body, count, par_only);
	}
      else if (CLAST_STMT_IS_A(s, stmt_for))
	{
	  if (par_only == 0)
	    (*count)++;
	  traverse_clast_nparf (((struct clast_vectorfor*)s)->body,
				count, par_only);
	}
      else if (CLAST_STMT_IS_A(s, stmt_guard))
	traverse_clast_nparf (((struct clast_guard*)s)->then, count, par_only);
      else if (CLAST_STMT_IS_A(s, stmt_block))
	traverse_clast_nparf (((struct clast_block*)s)->body, count, par_only);
    }
}


static
void
traverse_clast_parent (struct clast_stmt* s,
		       struct clast_stmt* node,
		       struct clast_stmt** cur_parent,
		       void** parent,
		       int get_pointer)
{
  if (*parent != NULL)
    return;
  // Traverse the clast.
  struct clast_stmt** last = NULL;
  for ( ; s; last = &(s->next), s = s->next)
    {
      if (s == node)
	{
	  if (! get_pointer)
	    *parent = *cur_parent;
	  else
	    {
	      if (last == NULL)
		*parent = cur_parent;
	      else
		*parent = last;
	    }
	  return;
	}
      if (CLAST_STMT_IS_A(s, stmt_parfor))
	traverse_clast_parent (((struct clast_parfor*)s)->body,
			       node,
			       &(((struct clast_parfor*)s)->body),
			       parent, get_pointer);
      else if (CLAST_STMT_IS_A(s, stmt_vectorfor))
	traverse_clast_parent (((struct clast_vectorfor*)s)->body,
			       node,
			       &(((struct clast_vectorfor*)s)->body),
			       parent, get_pointer);
      else if (CLAST_STMT_IS_A(s, stmt_for))
	traverse_clast_parent (((struct clast_for*)s)->body,
			       node,
			       &(((struct clast_for*)s)->body),
			       parent, get_pointer);
      else if (CLAST_STMT_IS_A(s, stmt_guard))
	traverse_clast_parent (((struct clast_guard*)s)->then,
			       node,
			       &(((struct clast_guard*)s)->then),
			       parent, get_pointer);
      else if (CLAST_STMT_IS_A(s, stmt_block))
	traverse_clast_parent (((struct clast_block*)s)->body,
			       node,
			       &(((struct clast_block*)s)->body),
			       parent, get_pointer);
    }
}

static
void
traverse_clast_innerloops (struct clast_stmt* s,
			   struct clast_stmt** loops)
{
  // Traverse the clast.
  for ( ; s; s = s->next)
    {
      if (CLAST_STMT_IS_A(s, stmt_parfor) ||
	  CLAST_STMT_IS_A(s, stmt_vectorfor) ||
	  CLAST_STMT_IS_A(s, stmt_for))
	{
	  struct clast_stmt* body;
	  if (CLAST_STMT_IS_A(s, stmt_parfor))
	    body = ((struct clast_parfor*) s)->body;
	  else if (CLAST_STMT_IS_A(s, stmt_vectorfor))
	    body = ((struct clast_vectorfor*) s)->body;
	  else if (CLAST_STMT_IS_A(s, stmt_for))
	    body = ((struct clast_for*) s)->body;
	  if (clasttools_utils_contains_loops (body))
	      traverse_clast_innerloops (body, loops);
	  else
	    {
	      int i;
	      for (i = 0; loops[i]; ++i)
		;
	      loops[i] = s;
	    }
	}
      else if (CLAST_STMT_IS_A(s, stmt_guard))
	traverse_clast_innerloops (((struct clast_guard*)s)->then,
				   loops);
      else if (CLAST_STMT_IS_A(s, stmt_block))
	traverse_clast_innerloops (((struct clast_block*)s)->body,
				   loops);
    }
}

static
int
traverse_clast_hasloop (struct clast_stmt* s)
{
  // Traverse the clast.
  for ( ; s; s = s->next)
    {
      if (CLAST_STMT_IS_A(s, stmt_parfor) ||
	  CLAST_STMT_IS_A(s, stmt_vectorfor) ||
	  CLAST_STMT_IS_A(s, stmt_for))
	return 1;
      else if (CLAST_STMT_IS_A(s, stmt_guard))
	return traverse_clast_hasloop (((struct clast_guard*)s)->then);
      else if (CLAST_STMT_IS_A(s, stmt_block))
	return traverse_clast_hasloop (((struct clast_block*)s)->body);
    }

  return 0;
}


/**
 * Count the number of parfor loops in the (sub)tree.
 *
 */
int
clasttools_utils_number_parfor (struct clast_stmt* root)
{
  int count = 0;
  traverse_clast_nparf (root, &count, 1);

  return count;
}


/**
 * Count the number of loops in the (sub)tree.
 *
 */
int
clasttools_utils_number_loops (struct clast_stmt* root)
{
  int count = 0;
  traverse_clast_nparf (root, &count, 0);

  return count;
}


/**
 * Get the parent of a node, in the (sub)tree.
 *
 */
struct clast_stmt*
clasttools_utils_get_parent (struct clast_stmt* root, struct clast_stmt* node)
{
  void* parent = NULL;
  traverse_clast_parent (root, node, &root, &parent, 0);

  return (struct clast_stmt*) parent;
}


/**
 * Get the address of the pointer to a given node, in the (sub)tree.
 *
 */
struct clast_stmt**
clasttools_utils_get_pointer (struct clast_stmt* root, struct clast_stmt* node)
{
  void* parent = NULL;
  traverse_clast_parent (root, node, &root, &parent, 1);

  return (struct clast_stmt**) parent;
}


/**
 * Determine if there is one or more loops in the (sub)tree.
 *
 */
int
clasttools_utils_contains_loops (struct clast_stmt* root)
{
  return traverse_clast_hasloop (root);
}


/**
 * Get the set of inner loops, in the (sub)tree.
 *
 */
struct clast_stmt**
clasttools_utils_get_all_inner_loops (struct clast_stmt* root)
{
  int size = clasttools_utils_number_loops (root);
  struct clast_stmt** loops = XMALLOC(struct clast_stmt*, size + 1);
  int i;
  for (i = 0; i < size + 1; ++i)
    loops[i] = NULL;

  traverse_clast_innerloops (root, loops);

  return loops;
}


/**
 * Duplicate a CLAST expression.
 *
 */
struct clast_expr*
clasttools_utils_dup_expr (struct clast_expr* e)
{
  struct clast_binary* b;
  struct clast_term* t;
  struct clast_reduction* r;
  struct clast_reduction* newr;
  int i;

  if (e == NULL)
    return NULL;
  switch (e->type)
    {
    case clast_expr_term:
      t = (struct clast_term*) e;
      return &new_clast_term (t->val, t->var)->expr;
    case clast_expr_red:
      r = (struct clast_reduction*) e;
      newr = new_clast_reduction (r->type, r->n);
      for (i = 0; i < r->n; ++i)
	newr->elts[i] = clasttools_utils_dup_expr (r->elts[i]);
      return &newr->expr;
    case clast_expr_bin:
      b = (struct clast_binary*) e;
      return
	&new_clast_binary (b->type,
			   clasttools_utils_dup_expr (b->LHS), b->RHS)->expr;
    default:
      fprintf (stderr, "[ClastTools] Unkown CLAST expression node type\n");
      assert(0);
    }
}


/**
 * Duplicate a statement (list).
 *
 */
struct clast_stmt*
clasttools_utils_dup_stmt (struct clast_stmt* s)
{
  struct clast_stmt* ret = NULL;
  struct clast_stmt* val;
  struct clast_stmt** stmt = &val;
  struct clast_root* r;
  struct clast_assignment* a;
  struct clast_user_stmt* u;
  struct clast_user_stmt_extended* ue;
  struct clast_for* f;
  struct clast_for* newf;
  struct clast_parfor* pf;
  struct clast_parfor* newpf;
  struct clast_vectorfor* vf;
  struct clast_vectorfor* newvf;
  struct clast_guard* g;
  struct clast_guard* newg;
  struct clast_block* b;
  struct clast_block* newb;
  int i;

  for ( ; s; s = s->next)
    {
      if (CLAST_STMT_IS_A(s, stmt_root))
	{
	  r = (struct clast_root*) s;
	  *stmt = &new_clast_root (r->names)->stmt;
	}
      else if (CLAST_STMT_IS_A(s, stmt_ass))
	{
	  a = (struct clast_assignment*) s;
	  *stmt = &new_clast_assignment
	    (a->LHS, clasttools_utils_dup_expr (a->RHS))->stmt;
	}
      else if (CLAST_STMT_IS_A(s, stmt_user))
	{
	  u = (struct clast_user_stmt*) s;
	  *stmt = &new_clast_user_stmt
	    (cloog_domain_copy(u->domain), u->statement,
	     clasttools_utils_dup_stmt (u->substitutions))->stmt;
	}
      else if (CLAST_STMT_IS_A(s, stmt_user_extended))
	{
	  ue = (struct clast_user_stmt_extended*) s;
	  *stmt = &new_clast_user_stmt_extended
	    (u->statement, clasttools_utils_dup_stmt (u->substitutions),
	     ue->scop_statement_id, strdup (ue->define_string))->stmt;
	}
      else if (CLAST_STMT_IS_A(s, stmt_for))
	{
	  f = (struct clast_for*) s;
	  cloog_int_t offset; cloog_int_init(offset);
	  cloog_int_set_si(offset, 0);
	  CloogStride* cstride = cloog_stride_alloc(f->stride, offset);
	  newf = new_clast_for
	    (cloog_domain_copy(f->domain), f->iterator,
	     clasttools_utils_dup_expr (f->LB),
	     clasttools_utils_dup_expr (f->UB), cstride);
	  cloog_stride_free (cstride);
	  newf->body = clasttools_utils_dup_stmt (f->body);
	  *stmt = &newf->stmt;
	}
      else if (CLAST_STMT_IS_A(s, stmt_parfor))
	{
	  pf = (struct clast_parfor*) s;
	  newpf = new_clast_parfor
	    (f->iterator, clasttools_utils_dup_expr (f->LB),
	     clasttools_utils_dup_expr (f->UB), f->stride);
	  newpf->body = clasttools_utils_dup_stmt (f->body);
	  *stmt = &newpf->stmt;
	}
      else if (CLAST_STMT_IS_A(s, stmt_vectorfor))
	{
	  vf = (struct clast_vectorfor*) s;
	  newvf = new_clast_vectorfor
	    (f->iterator, clasttools_utils_dup_expr (f->LB),
	     clasttools_utils_dup_expr (f->UB), f->stride);
	  newvf->body = clasttools_utils_dup_stmt (f->body);
	  *stmt = &newvf->stmt;
	}
      else if (CLAST_STMT_IS_A(s, stmt_guard))
	{
	  g = (struct clast_guard*) s;
	  newg = new_clast_guard (g->n);
	  newg->then = clasttools_utils_dup_stmt (g->then);
	  for (i = 0; i < g->n; ++i)
	    {
	      newg->eq[i].LHS = clasttools_utils_dup_expr (g->eq[i].LHS);
	      newg->eq[i].RHS = clasttools_utils_dup_expr (g->eq[i].RHS);
	      newg->eq[i].sign = g->eq[i].sign;
	    }
	  *stmt = &newg->stmt;
	}
      else if (CLAST_STMT_IS_A(s, stmt_block))
	{
	  b = (struct clast_block*) s;
	  newb = new_clast_block();
	  newb->body = clasttools_utils_dup_stmt (b->body);
	  *stmt = &newb->stmt;
	}
      else
	{
	  fprintf (stderr,
		   "[ClastTools] Unkown CLAST statement node type\n");
	  assert(0);
	}
      if (ret == NULL)
	ret = *stmt;
      stmt = &((*stmt)->next);
    }
  *stmt = NULL;

  return ret;
}


static
void
traverse_clast_get_loops_at_level (struct clast_stmt* s,
				   int level,
				   int cur_level,
				   struct clast_stmt** lns)
{
  // Traverse the clast.
  for ( ; s; s = s->next)
    {
      if (CLAST_STMT_IS_A(s, stmt_for) ||
	  CLAST_STMT_IS_A(s, stmt_parfor) ||
	  CLAST_STMT_IS_A(s, stmt_vectorfor))
	{
	  if (cur_level == level)
	    {
	      int i;
	      for (i = 0; lns[i]; ++i)
		;
	      lns[i] = s;
	    }
	  else
	    {
	      struct clast_stmt* body;
	      if (CLAST_STMT_IS_A(s, stmt_for))
		body = ((struct clast_for*)s)->body;
	      else if  (CLAST_STMT_IS_A(s, stmt_parfor))
		body = ((struct clast_parfor*)s)->body;
	      else if  (CLAST_STMT_IS_A(s, stmt_vectorfor))
		body = ((struct clast_vectorfor*)s)->body;
	      traverse_clast_get_loops_at_level (body, level,
						 cur_level + 1, lns);
	    }
	}
      else if (CLAST_STMT_IS_A(s, stmt_guard))
	traverse_clast_get_loops_at_level (((struct clast_guard*)s)->then,
					   level, cur_level, lns);
      else if (CLAST_STMT_IS_A(s, stmt_block))
	traverse_clast_get_loops_at_level (((struct clast_block*)s)->body,
					   level, cur_level, lns);
    }
}

/**
 * Returns an array of nodes, one for each
 * clast_{for,parfor,vectorfor} node which occurs at level 'level'
 * (0-indexed).
 *
 */
struct clast_stmt**
clasttools_utils_get_loops_at_level (struct clast_stmt* s,
				     int level)
{
  int size = clasttools_utils_number_loops (s);
  struct clast_stmt** lns = XMALLOC(struct clast_stmt*, size + 1);
  int i;
  for (i = 0; i < size + 1; ++i)
    lns[i] = NULL;
  traverse_clast_get_loops_at_level (s, level, 0, lns);

  return lns;
}
