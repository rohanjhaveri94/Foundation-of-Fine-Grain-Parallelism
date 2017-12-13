/*
 * clastext.c: this file is part of the ClastTools project.
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
#include <clasttools/clastext.h>

#ifndef CLOOG_INT_GMP
# define CLOOG_INT_GMP
#endif
#include <cloog/stride.h>


/**
 * Functions to deal with the clast_pragma_omp_for node.
 *
 */
static void free_clast_pragma_omp_for (struct clast_stmt* s);

const struct clast_stmt_op stmt_pragma_omp_for = { free_clast_pragma_omp_for };

struct clast_pragma_omp_for *new_clast_pragma_omp_for (const char* clause)
{
  struct clast_pragma_omp_for* p = malloc (sizeof(struct clast_pragma_omp_for));
  p->stmt.op = &stmt_pragma_omp_for;
  p->clause = clause;
  return p;
}


static void free_clast_pragma_omp_for (struct clast_stmt* s)
{
    struct clast_pragma_omp_for* p = (struct clast_pragma_omp_for*) s;
    assert (CLAST_STMT_IS_A(s, stmt_pragma_omp_for));
    free (p);
}



/**
 * Functions to deal with the clast_pragma_vectorize node.
 *
 */
static void free_clast_pragma_vectorize (struct clast_stmt* s);

const struct clast_stmt_op stmt_pragma_vectorize =
  { free_clast_pragma_vectorize };

struct clast_pragma_vectorize* new_clast_pragma_vectorize (const char* clause)
{
  struct clast_pragma_vectorize* p =
    malloc (sizeof(struct clast_pragma_vectorize));
  p->stmt.op = &stmt_pragma_vectorize;
  p->clause = clause;
  return p;
}


static void free_clast_pragma_vectorize (struct clast_stmt* s)
{
    struct clast_pragma_vectorize* p = (struct clast_pragma_vectorize*) s;
    assert (CLAST_STMT_IS_A(s, stmt_pragma_vectorize));
    free (p);
}


/**
 * Functions to manage the new clast node type clast_parfor.
 *
 */
static void free_clast_parfor (struct clast_stmt* s);

const struct clast_stmt_op stmt_parfor = { free_clast_parfor };

struct clast_parfor* new_clast_parfor (const char* it, struct clast_expr* LB,
				       struct clast_expr* UB,
				       cloog_int_t stride)
{
  cloog_int_t offset;
  cloog_int_init (offset);
  cloog_int_set_si (offset, 0);
  CloogStride* cstride = cloog_stride_alloc (stride, offset);
  struct clast_parfor* newf =
    (struct clast_parfor*) new_clast_for (NULL, it, LB, UB, cstride);
  cloog_stride_free (cstride);
  newf->stmt.op = &stmt_parfor;

  return newf;
}


static void free_clast_parfor (struct clast_stmt* s)
{
    struct clast_for* f = (struct clast_for*)s;
    assert (CLAST_STMT_IS_A(s, stmt_parfor));
    free_clast_expr (f->LB);
    free_clast_expr (f->UB);
    cloog_int_clear (f->stride);
    cloog_clast_free (f->body);
    free (f);
}


/**
 * Functions to manage the new clast node type clast_vectorfor.
 *
 */
static void free_clast_vectorfor (struct clast_stmt *s);

const struct clast_stmt_op stmt_vectorfor = { free_clast_vectorfor };

struct clast_vectorfor* new_clast_vectorfor (const char* it,
					     struct clast_expr* LB,
					     struct clast_expr* UB,
					     cloog_int_t stride)
{
  cloog_int_t offset;
  cloog_int_init (offset);
  cloog_int_set_si (offset, 0);
  CloogStride* cstride = cloog_stride_alloc (stride, offset);
  struct clast_vectorfor* newf =
    (struct clast_vectorfor*) new_clast_for (NULL, it, LB, UB, cstride);
  cloog_stride_free (cstride);
  newf->stmt.op = &stmt_vectorfor;
}


static void free_clast_vectorfor (struct clast_stmt* s)
{
    struct clast_for* f = (struct clast_for*)s;
    assert (CLAST_STMT_IS_A(s, stmt_vectorfor));
    free_clast_expr (f->LB);
    free_clast_expr (f->UB);
    cloog_int_clear (f->stride);
    cloog_clast_free (f->body);
    free (f);
}


/**
 * Functions to manage the new clast node type clast_user_stmt_extended.
 *
 */
static void free_clast_user_stmt_extended (struct clast_stmt* s);

const struct clast_stmt_op stmt_user_extended =
  { free_clast_user_stmt_extended };

static void free_clast_user_stmt_extended (struct clast_stmt* s)
{
    struct clast_user_stmt_extended* u = (struct clast_user_stmt_extended*)s;
    assert (CLAST_STMT_IS_A(s, stmt_user_extended));
    cloog_statement_free (u->statement);
    cloog_clast_free (u->substitutions);
    if (u->define_string)
      free (u->define_string);
    free (u);
}

struct clast_user_stmt_extended*
new_clast_user_stmt_extended (CloogStatement* stmt,
			      struct clast_stmt* subs,
			      int scop_stmt_id,
			      char* define_string)
{
  struct clast_user_stmt_extended* u =
    malloc (sizeof(struct clast_user_stmt_extended));
    u->stmt.op = &stmt_user_extended;
    u->stmt.next = NULL;
    u->statement = cloog_statement_copy (stmt);
    u->substitutions = subs;
    u->scop_statement_id = scop_stmt_id;
    u->define_string = define_string;

    return u;
}
