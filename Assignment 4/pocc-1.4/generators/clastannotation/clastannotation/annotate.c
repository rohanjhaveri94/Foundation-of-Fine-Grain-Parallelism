/*
 * annotate.c: This file is part of the ClastAnnotation project.
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
#include <clastannotation/annotate.h>
#ifndef CANDL_SUPPORTS_SCOPLIB
# define CANDL_SUPPORTS_SCOPLIB
#endif
#include <candl/program.h>
#include <candl/options.h>
#include <candl/candl.h>
#include <clasttools/clastext.h>



/**
 * Code to detect and translate a parallel for.
 *
 */
static
struct clast_parfor*
translate_to_parfor (struct clast_for* f, struct clast_stmt** last,
		     int loop_id)
{
  printf ("[ClastAnnotation] Detected loop id: %d (iterator:%s) as parallel\n",
	  loop_id, f->iterator);
  f->stmt.op = &stmt_parfor;

  return (struct clast_parfor*) f;
}

static
struct clast_for*
translate_to_for (struct clast_for* f, struct clast_stmt** last,
		  int loop_id)
{
  f->stmt.op = &stmt_for;

  return (struct clast_for*) f;
}


static
void
traverse_clast_user_stmt (struct clast_stmt* s, int* list, int* id)
{
  // Traverse the clast.
  for ( ; s; s = s->next)
    {
      if (CLAST_STMT_IS_A(s, stmt_for))
	traverse_clast_user_stmt (((struct clast_for*)s)->body, list, id);
      else if (CLAST_STMT_IS_A(s, stmt_guard))
	traverse_clast_user_stmt (((struct clast_guard*)s)->then, list, id);
      else if (CLAST_STMT_IS_A(s, stmt_block))
	traverse_clast_user_stmt (((struct clast_block*)s)->body, list, id);
      else if (CLAST_STMT_IS_A(s, stmt_user) ||
	       CLAST_STMT_IS_A(s, stmt_user_extended))
	{
	  int i;
	  for (i = 0; list[i] != -1; ++i)
	    ;
	  list[i] = (*id)++;
	}
    }
}

static
int
check_par_for (struct clast_for* s,
	       CandlProgram* prog,
	       CandlDependence* deps,
	       int level,
	       int* stmt_offset,
	       int loop_id)
{
  // 1- Collect the user statements surrounded by this loop.
  int i, j;
  int stmtid[prog->nb_statements + 1];
  for (i = 0; i < prog->nb_statements + 1; ++i)
    stmtid[i] = -1;
  int id = *stmt_offset;
  traverse_clast_user_stmt (s->body, stmtid, &id);
  for (i = 0; i < prog->nb_statements && stmtid[i] != -1; ++i)
    ;
  int size = i;

  // 2- Check for the existence of loop-carried dependence for this level.
  CandlDependence* tmp;
  int is_par = 1;
  for (tmp = deps; tmp; tmp = tmp->next)
    {
      // Ensure the dependence reference 2 statements under this loop.
      for (i = 0; i < size; ++i)
	if (tmp->source->label == stmtid[i] || tmp->target->label == stmtid[i])
	  {
	    if (tmp->source->label == stmtid[i])
	      {
		for (j = 0; j < size; ++j)
		  if (tmp->target->label == stmtid[j])
		    break;
	      }
	    else
	      for (j = 0; j < size; ++j)
		if (tmp->source->label == stmtid[j])
		  break;
	    break;
	  }
      // Check the dependence is loop-carried, and not carried at this
      // level.
      if (i != size && j != size &&
	  candl_dependence_is_loop_carried (prog, tmp, loop_id - 1))
	if (tmp->depth == level + 1)
	  {
	    is_par = 0;
	    break;
	  }
    }

  return is_par;
}

static
void
traverse_clast_parfor (struct clast_stmt* s,
		       struct clast_stmt** last,
		       CandlProgram* prog,
		       CandlDependence* deps,
		       int level,
		       int* loop_id,
		       int* stmt_offset)
{
  // Traverse the clast.
  for ( ; s; last = &(s->next), s = s->next)
    {
      if (CLAST_STMT_IS_A(s, stmt_for) || CLAST_STMT_IS_A(s, stmt_parfor) ||
	  CLAST_STMT_IS_A(s, stmt_vectorfor))
	{
	  struct clast_for* f = (struct clast_for*) s;
	  ++(*loop_id);
	  if (check_par_for (f, prog, deps, level, stmt_offset, *loop_id))
	    {
	      struct clast_parfor* pf = translate_to_parfor (f, last, *loop_id);
	      traverse_clast_parfor (pf->body, &(pf->body), prog, deps,
				     level + 1, loop_id, stmt_offset);
	    }
	  else
	    {
	      translate_to_for (f, last, *loop_id);
	      traverse_clast_parfor (f->body, &(f->body), prog, deps,
				     level + 1, loop_id, stmt_offset);
	    }
	}
      else if (CLAST_STMT_IS_A(s, stmt_guard))
	traverse_clast_parfor (((struct clast_guard *)s)->then,
			       &(((struct clast_guard *)s)->then),
			       prog, deps, level, loop_id, stmt_offset);
      else if (CLAST_STMT_IS_A(s, stmt_block))
	traverse_clast_parfor (((struct clast_block *)s)->body,
			       &(((struct clast_block *)s)->body),
			       prog, deps, level, loop_id, stmt_offset);
      else if (CLAST_STMT_IS_A(s, stmt_user))
	*stmt_offset += 1;
    }
}



static
void
is_innermost (struct clast_stmt* s, int* is_inmost)
{
  // Traverse the clast.
  for ( ; s; s = s->next)
    {
      if (CLAST_STMT_IS_A(s, stmt_for) || CLAST_STMT_IS_A(s, stmt_parfor) ||
	  CLAST_STMT_IS_A(s, stmt_vectorfor))
	{
	  *is_inmost = 0;
	  return;
	}
      else if (CLAST_STMT_IS_A(s, stmt_guard))
	is_innermost (((struct clast_guard*)s)->then, is_inmost);
      else if (CLAST_STMT_IS_A(s, stmt_block))
	is_innermost (((struct clast_block*)s)->body, is_inmost);
    }
}

static
void
traverse_clast_innermost_for (struct clast_stmt* s)
{
  // Traverse the clast.
  for ( ; s; s = s->next)
    {
      if (CLAST_STMT_IS_A(s, stmt_for))
	traverse_clast_innermost_for (((struct clast_for*)s)->body);
      else if (CLAST_STMT_IS_A(s, stmt_parfor))
	{
	  struct clast_parfor* f = (struct clast_parfor*) s;
	  int isinm = 1;
	  is_innermost (f->body, &isinm);
	  if (isinm)
	    // Inner-most, parallel for loop. Mark it as vectorizable.
	    f->stmt.op = &stmt_vectorfor;
	  else
	    traverse_clast_innermost_for (((struct clast_parfor*)s)->body);
	}
      else if (CLAST_STMT_IS_A(s, stmt_guard))
	traverse_clast_innermost_for (((struct clast_guard*)s)->then);
      else if (CLAST_STMT_IS_A(s, stmt_block))
	traverse_clast_innermost_for (((struct clast_block*)s)->body);
    }
}



/**
 * This function detect all parallel loops, and change the clast_for
 * node associated to a clast_parfor node.
 *
 */
void
clastannotation_annotate_parallel (struct clast_stmt* root,
				   scoplib_scop_p scop,
				   CandlDependence* deps)
{
  // Build the CandlProgram associated to the scop.
  CandlProgram* cprogram = candl_program_convert_scop (scop, NULL);
  // Add all program scatterings in the candl program.
  CandlMatrix** scheds = XMALLOC(CandlMatrix*, cprogram->nb_statements);
  int i;
  scoplib_statement_p s = scop->statement;
  for (i = 0; i < cprogram->nb_statements; ++i, s = s->next)
    scheds[i] = (CandlMatrix*) scoplib_matrix_copy (s->schedule);
  cprogram->transformation = scheds;

  // Do the traversal: for each for node, check if it is a parfor. If
  // so, replace the clast_for node with a clast_parfor node.
  int loop_id = 0;
  int stmt_offset = 0;
  traverse_clast_parfor (root, NULL, cprogram, deps, 0, &loop_id, &stmt_offset);

  // Be clean.
  candl_program_free (cprogram);
}


/** 
 * Translate CLAST nodes to their refined type (eg, parallel for to parfor).
 *
 * Assume root <=> cloog(scop) <=> cloog(root) (ie, id schedule for
 * the scop).
 *
 */
int
clastannotation_annotate (struct clast_stmt* root, scoplib_scop_p scop)
{
  printf ("[ClastAnnotation] Starting CLAST annotation/translation\n");

  // 1- Compute the dependences
  CandlOptions* coptions = candl_options_malloc ();
  CandlProgram* cprogram = candl_program_convert_scop (scop, NULL);
  CandlDependence* deps = candl_dependence (cprogram, coptions);
  candl_options_free (coptions);

  // 2- Translate parallel for loops to parfor loops.
  clastannotation_annotate_parallel (root, scop, deps);

  // Be clean.
  candl_program_free (cprogram);
  candl_dependence_free (deps);

  printf ("[ClastAnnotation] all done\n");

  return 0;
}
