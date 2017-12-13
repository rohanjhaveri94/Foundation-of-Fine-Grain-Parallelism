/*
 * clast2past.c: this file is part of the ClastTools project.
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

#include <assert.h>

#include <clasttools/common.h>
#include <clasttools/clast2past.h>
#include <clasttools/clastext.h>
#include <past/past.h>
#include <past/symbols.h>

#ifndef CLOOG_INT_GMP
# define CLOOG_INT_GMP
#endif
#include <cloog/stride.h>

#if defined(CLOOG_INT_GMP)
# define cloog_int_get_si(val) mpz_get_si(val)
#else
# define cloog_int_get_si(val) val
#endif

static
s_past_node_t*
convert_expr_tree (struct clast_expr* e, s_symbol_table_t* table,
		   int data_is_char)
{
    if (!e)
      return NULL;
    switch (e->type)
      {
      case clast_expr_name:
	{
	  struct clast_name* n = (struct clast_name*) e;
	  s_symbol_t* symb;
	  if (data_is_char)
	    symb = symbol_add_from_char (table, (char*)n->name);
	  else
	    assert (! "ERROR: clast2past: conversion from non-char-based CLAST trees is no longer supported!");
	    /* symb = symbol_add_from_data (table, (void*)n->name); */
	  return past_node_varref_create (symb);
	}
      case clast_expr_term:
	{
	  struct clast_term* t = (struct clast_term*) e;
	  int val = cloog_int_get_si(t->val);
	  if (t->var)
	    {
	      if (val != 1)
		return past_node_binary_create
		  (past_mul, past_node_value_create_from_int (val),
		   convert_expr_tree (t->var, table, data_is_char));
	      else
		return convert_expr_tree (t->var, table, data_is_char);
	    }
	  else
	    return past_node_value_create_from_int (val);
	}
      case clast_expr_red:
	{
	  int i;
	  cs_past_node_type_t* bintype;
	  struct clast_reduction *r = (struct clast_reduction*) e;
	  if (r->type == clast_red_sum)
	    bintype = past_add;
	  else if (r->type == clast_red_min)
	    bintype = past_min;
	  else if (r->type == clast_red_max)
	    bintype = past_max;
	  s_past_node_t* binop = convert_expr_tree (r->elts[0], table,
						    data_is_char);
	  if (r->n > 1)
	    {
	      int i;
	      for (i = 1; i < r->n; ++i)
		binop = past_node_binary_create
		  (bintype, binop,
		   convert_expr_tree (r->elts[i], table, data_is_char));
	    }
	  return binop;
	}
      case clast_expr_bin:
	{
	  struct clast_binary *b = (struct clast_binary*) e;
	  cs_past_node_type_t* bintype;
	  if (b->type == clast_bin_fdiv)
	    bintype = past_floord;
	  else if (b->type == clast_bin_cdiv)
	    bintype = past_ceild;
	  else if (b->type == clast_bin_div)
	    bintype = past_div;
	  else if (b->type == clast_bin_mod)
	    bintype = past_mod;
	  return past_node_binary_create
	    (bintype, convert_expr_tree (b->LHS, table, data_is_char),
	     past_node_value_create_from_int (cloog_int_get_si(b->RHS)));
	}
      default:
	fprintf (stderr, "Unsupported expr node\n");
	assert (0);
      }
}

static
s_past_node_t*
convert_tree (struct clast_stmt* s, s_symbol_table_t* table, int data_is_char,
	      int is_stmt_ass)
{
  s_past_node_t* ret = NULL;;
  s_past_node_t* val;
  s_past_node_t** stmt = &val;

  // Traverse the clast.
  for ( ; s; s = s->next)
    {
      if (CLAST_STMT_IS_A(s, stmt_root))
	{
	  struct clast_root* cr = (struct clast_root*) s;
	  *stmt = past_node_root_create
	    (table, convert_tree (cr->stmt.next, table,
				  data_is_char, is_stmt_ass));
	  // Skip the remaining nodes attached to the root, they are already in
	  // the body attribute of the past_root node.
	  while (s->next)
	    s = s->next;
	}
      else if (CLAST_STMT_IS_A(s, stmt_for) ||
	       CLAST_STMT_IS_A(s, stmt_parfor) ||
	       CLAST_STMT_IS_A(s, stmt_vectorfor))
	{
	  struct clast_for* cf = (struct clast_for*) s;
	  s_past_node_t* iter = past_node_varref_create
	    (symbol_add_from_char (table, (char*)cf->iterator));
	  s_past_node_t* lb = NULL;
	  if (cf->LB)
	    lb = past_node_binary_create (past_assign, iter,
					  convert_expr_tree (cf->LB, table,
							     data_is_char));
	  iter = past_node_varref_create
	    (symbol_add_from_char (table, (char*)cf->iterator));
	  s_past_node_t* ub = NULL;
	  if (cf->UB)
	    ub = past_node_binary_create (past_leq, iter,
					  convert_expr_tree (cf->UB, table,
							     data_is_char));
	  iter = past_node_varref_create
	    (symbol_add_from_char (table, (char*)cf->iterator));
	  int val = cloog_int_get_si(cf->stride);
	  s_past_node_t* increment;
	  if (val != 1)
	    {
	      increment = past_node_binary_create
		(past_add, iter, past_node_value_create_from_int (val));
	      iter = past_node_varref_create
		(symbol_add_from_char (table, (char*)cf->iterator));
	      increment =
		past_node_binary_create (past_assign, iter, increment);
	    }
	  else
	    increment = past_node_unary_create (past_inc_after, iter);
	  iter = past_node_varref_create
	    (symbol_add_from_char (table, (char*)cf->iterator));
	  s_past_node_t* body = convert_tree (cf->body, table, 
					      data_is_char, is_stmt_ass);
	  if (! CLAST_STMT_IS_A(cf->body, stmt_block))
	    body = past_node_block_create (body);
	  *stmt = past_node_for_create
	    (lb, ub, ((s_past_varref_t*) iter)->symbol, increment,
	     body);
	}
      else if (CLAST_STMT_IS_A(s, stmt_ass))
	{
	  struct clast_assignment* ca = (struct clast_assignment*) s;
	  if (ca->LHS)
	    {
	      s_symbol_t* symb = symbol_add_from_char (table, (char*)ca->LHS);
	      s_past_node_t* converted =
	      past_node_binary_create
		(past_assign, past_node_varref_create (symb),
		 convert_expr_tree (ca->RHS, table, data_is_char));
	      if (! is_stmt_ass)
		*stmt = past_node_statement_create (converted);
	      else
		*stmt = converted;
	    }
	  else
	    {
	      s_past_node_t* converted =
		convert_expr_tree (ca->RHS, table, data_is_char);
	      if (! is_stmt_ass)
		*stmt = past_node_statement_create (converted);
	      else
		*stmt = converted;
	    }
	}
      else if (CLAST_STMT_IS_A(s, stmt_guard))
	{
	  struct clast_guard* cg = (struct clast_guard*) s;
	  cs_past_node_type_t* eqtype;
	  if (cg->eq[0].sign == 0)
	    eqtype = past_equal;
	  else if (cg->eq[0].sign > 0)
	    eqtype = past_geq;
	  else if (cg->eq[0].sign < 0)
	    eqtype = past_leq;
	  s_past_node_t* cond =
	    past_node_binary_create
	    (eqtype,
	     convert_expr_tree (cg->eq[0].LHS, table, data_is_char),
	     convert_expr_tree (cg->eq[0].RHS, table, data_is_char));
	  if (cg->n > 1)
	    {
	      int i;
	      for (i = 1; i < cg->n; ++i)
		{
		  if (cg->eq[i].sign == 0)
		    eqtype = past_equal;
		  else if (cg->eq[i].sign > 0)
		    eqtype = past_geq;
		  else if (cg->eq[i].sign < 0)
		    eqtype = past_leq;
		  s_past_node_t* cond1 = past_node_binary_create
		    (eqtype,
		     convert_expr_tree (cg->eq[i].LHS, table, data_is_char),
		     convert_expr_tree (cg->eq[i].RHS, table,
					data_is_char));
		  cond = past_node_binary_create (past_and, cond, cond1);
		}
	    }
	  *stmt = past_node_affineguard_create
	    (cond, convert_tree (cg->then, table, data_is_char, is_stmt_ass));
	}
      else if (CLAST_STMT_IS_A(s, stmt_block))
	{
	  struct clast_block* cb = (struct clast_block*) s;
	  *stmt = past_node_block_create
	    (convert_tree (cb->body, table, data_is_char, is_stmt_ass));
	}
      else if (CLAST_STMT_IS_A(s, stmt_user))
	{
	  struct clast_user_stmt* cu = (struct clast_user_stmt*) s;
	  char symbol[512];
	  if (cu->statement->name)
	    sprintf (symbol, "%s", cu->statement->name);
	  else
	    sprintf (symbol, "S%d", cu->statement->number);
	  s_symbol_t* symb = symbol_add_from_char (table, (char*)symbol);
	  *stmt = past_node_cloogstmt_create
	    (cloog_domain_copy (cu->domain),
	     cloog_statement_copy (cu->statement),
	     past_varref_create (symb),
	     cu->statement->number,
	     convert_tree (cu->substitutions, table,
			   data_is_char, 1));
	}
      else
	fprintf (stderr, "Unknown node\n");
      if (ret == NULL)
	ret = *stmt;
      stmt = &((*stmt)->next);
    }
  *stmt = NULL;

  return ret;
}


/**
 * Convert a CLAST (standard, non-extended) to a PAST.
 *
 *
 */
s_past_node_t* clast2past (struct clast_stmt* root, int data_is_char)
{
  s_symbol_table_t* table = symbol_table_malloc ();
  s_past_node_t* proot = convert_tree (root, table, data_is_char, 0);
  past_set_parent (proot);
  if (past_node_is_a (proot, past_root))
    {
      PAST_DECLARE_TYPED(root, pr, proot);
      pr->symboltable = table;
    }
  else if (past_node_is_a (proot, past_block))
    {
      PAST_DECLARE_TYPED(block, pr, proot);
      pr->symboltable = table;
    }

  return proot;
}

