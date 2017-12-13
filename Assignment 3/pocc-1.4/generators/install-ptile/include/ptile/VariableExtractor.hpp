/*
 * VariableExtractor.hpp: This file is part of the Parametric Tiling project.
 * 
 * Parametric Tiling: A CLAST-to-CLAST parametric tiling software
 * 
 * Copyright (C) 2011 Sanket Tavargeri
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
 * Sanket Tavargeri <sanket.tavargeri@gmail.com>
 * 
 */

#ifndef PTILE_VARIABLEEXTRACTOR_H
# define PTILE_VARIABLEEXTRACTOR_H

# include <ptile/PtileClasses.hpp>

# include <ptile/ext_clast.h>

class VariableExtractor
{
public:

  set<string*, GeneralUtilityClass::StringComparator> variables;

  void ExtractVariablesFrom_name(struct ext_clast_name *n)
  {
    if (n->name != NULL)
      {	
    	variables.insert (new string(n->name));
      }//     if (n->name != NULL)
  }


  void ExtractVariablesFrom_term(struct ext_clast_term *t)
  {
    if (t->var) {
      ExtractVariablesFrom_expr(t->var);
    }
  }

  void ExtractVariablesFrom_sum(struct ext_clast_reduction *r)
  {
    int i;
    struct ext_clast_term *t;

    assert(r->n >= 1);
    assert(r->elts[0]->type == ext_clast_expr_term);
    t = (struct ext_clast_term *) r->elts[0];
    ExtractVariablesFrom_term(t);

    for (i = 1; i < r->n; ++i) {
      assert(r->elts[i]->type == ext_clast_expr_term);
      t = (struct ext_clast_term *) r->elts[i];
      ExtractVariablesFrom_term(t);
    }
  }


  void ExtractVariablesFrom_binary_nonaffine(struct ext_clast_binary_nonaffine *b)
  {
    ExtractVariablesFrom_expr(b->LHS);
    ExtractVariablesFrom_expr(b->RHS);
  }


  void ExtractVariablesFrom_binary(struct ext_clast_binary *b)
  {
    ExtractVariablesFrom_expr(b->LHS);
  }

  void ExtractVariablesFrom_minmax_f(struct ext_clast_reduction *r)
  {
    int i;
    if (r->n == 0)
      return;

    ExtractVariablesFrom_expr(r->elts[0]);
    for (i = 1; i < r->n; ++i) {
      ExtractVariablesFrom_expr(r->elts[i]);
    }
  }

  void ExtractVariablesFrom_minmax(struct ext_clast_reduction *r)
  {
    int i;
    if (r->n > 0)
      ExtractVariablesFrom_expr(r->elts[0]);
    for (i = 1; i < r->n; ++i) {
      ExtractVariablesFrom_expr(r->elts[i]);
    }
  }

  void ExtractVariablesFrom_reduction(struct ext_clast_reduction *r)
  {
    switch (r->type) {
    case ext_clast_red_sum:
      ExtractVariablesFrom_sum(r);
      break;
    case ext_clast_red_min:
    case ext_clast_red_max:
      if (r->n == 1) {
	ExtractVariablesFrom_expr(r->elts[0]);
	break;
      }

      ExtractVariablesFrom_minmax(r);
      break;
    default:
      assert(0);
    }
  }


  void ExtractVariablesFrom_function(struct ext_clast_function *f)
  {
    if (f == NULL)
      return;

    int j;

    if (f->n > 0)
      ExtractVariablesFrom_expr(f->elts[0]);
    for (j = 1; j < f->n; ++j) {
      ExtractVariablesFrom_expr(f->elts[j]);	
    }
  }


  void ExtractVariablesFrom_arrayType(struct ext_clast_arrayType *f)
  {
    if (f == NULL)
      return;
        
    string s(f->arrayName);
    s.append(GeneralUtilityClass::GetArrayAppendixString());
    if (f->arrayName != NULL)
      {
	variables.insert (new string(s));
      }// if (f->arrayName != NULL)

        
    int j;

    if (f->n > 0)
      {
	ExtractVariablesFrom_expr(f->elts[0]);	
      }

    for (j = 1; j < f->n; ++j) {
      ExtractVariablesFrom_expr(f->elts[j]);
    }
	
  }

  void ExtractVariablesFrom_expr(struct ext_clast_expr *e)
  {
    if (!e)
      return;
    switch (e->type) {
    case ext_clast_expr_name:
      ExtractVariablesFrom_name((struct ext_clast_name*) e);
      break;
    case ext_clast_expr_term:
      ExtractVariablesFrom_term((struct ext_clast_term*) e);
      break;
    case ext_clast_expr_red:
      ExtractVariablesFrom_reduction((struct ext_clast_reduction*) e);
      break;
    case ext_clast_expr_function:
      ExtractVariablesFrom_function((struct ext_clast_function*) e);
      break;
    case ext_clast_expr_arrayType:
      ExtractVariablesFrom_arrayType((struct ext_clast_arrayType*) e);
      break;
    case ext_clast_expr_bin:
      ExtractVariablesFrom_binary((struct ext_clast_binary*) e);
      break;
    case ext_clast_expr_bin_nonaffine:
      ExtractVariablesFrom_binary_nonaffine((struct ext_clast_binary_nonaffine*) e);
      break;
    default:
      //printf("Faulting type = %d\n", e->type);
      assert(0);
    }
  }

  void ExtractVariablesFrom_equation(struct ext_clast_equation *eq)
  {
    ExtractVariablesFrom_expr(eq->LHS);
    ExtractVariablesFrom_expr(eq->RHS);
  }

  void ExtractVariablesFrom_logical_op(struct ext_clast_logical_op* op)
  {
    if (op == NULL)
      return;
	
    if (op->eq != NULL)
      {
	ExtractVariablesFrom_equation(op->eq);
	return;
      }

    if (op->LHS == NULL || op->RHS == NULL)
      assert(0);
	
    ExtractVariablesFrom_logical_op(op->LHS);	
    ExtractVariablesFrom_logical_op(op->RHS);
  }

  void ExtractVariablesFrom_assignment(struct ext_clast_assignment *a)
  {
    if (a->LHS != NULL)
      {
	variables.insert (new string(a->LHS));
      }// if (a->LHS != NULL)

    ExtractVariablesFrom_expr(a->RHS);
  }


  void ExtractVariablesFrom_assignment_nonaffine(struct ext_clast_assignment_nonaffine *a)
  {
    ExtractVariablesFrom_expr(a->LHS);
    ExtractVariablesFrom_expr(a->RHS);
  }


  void ExtractVariablesFrom_user_stmt(struct ext_clast_user_stmt *u)
  {
    struct ext_clast_stmt *t;

    for (t = u->substitutions; t; t = t->next) {
      ExtractVariablesFrom_assignment((struct ext_clast_assignment *)t);
    }
  }

  void ExtractVariablesFrom_guard(struct ext_clast_guard *g)
  {
    int k;

    for (k = 0; k < g->n; ++k) {
      ExtractVariablesFrom_equation(&g->eq[k]);
    }

    /* Printing ext_clast_logical_op begins */

    if (g->logical_op != NULL && g->n == 0)
      {
	ExtractVariablesFrom_logical_op(g->logical_op);
      }
	
    /* Printing ext_clast_logical_op ends */

    ExtractVariablesFrom_stmt_list(g->then);

    /* Printing elseif begins */
	
    if (g->elsepart != NULL)
      {
	ExtractVariablesFrom_stmt_list(g->elsepart);
      }

    /* Printing elseif ends */
  }

  void ExtractVariablesFrom_for(struct ext_clast_for *f)
  {
    if (f->iterator != NULL)
      {
    	variables.insert (new string(f->iterator));
      }//     if (f->iterator != NULL)

 
    if (f->LB) {
      ExtractVariablesFrom_expr(f->LB);
    } 

    if (f->UB) { 
      ExtractVariablesFrom_expr(f->UB);
    } 

    ExtractVariablesFrom_stmt_list(f->body);
  }

  void ExtractVariablesFrom_stmt_list(struct ext_clast_stmt *s)
  {
    for ( ; s; s = s->next) {
      if (EXT_CLAST_STMT_IS_A(s, ext_stmt_root))
	continue;

      if (EXT_CLAST_STMT_IS_A(s, ext_stmt_ass)) {
	ExtractVariablesFrom_assignment((struct ext_clast_assignment *) s);
      } else if (EXT_CLAST_STMT_IS_A(s, ext_stmt_ass_nonaffine)) {
	ExtractVariablesFrom_assignment_nonaffine((struct ext_clast_assignment_nonaffine *) s);
      } else if (EXT_CLAST_STMT_IS_A(s, ext_stmt_program_text)) {
	continue;
      }
      else if (EXT_CLAST_STMT_IS_A(s, ext_stmt_user)) {
	ExtractVariablesFrom_user_stmt((struct ext_clast_user_stmt *) s);
      } else if (EXT_CLAST_STMT_IS_A(s, ext_stmt_for)) {
	ExtractVariablesFrom_for((struct ext_clast_for *) s);
      } else if (EXT_CLAST_STMT_IS_A(s, ext_stmt_guard)) {
	ExtractVariablesFrom_guard((struct ext_clast_guard *) s);
      } else if (EXT_CLAST_STMT_IS_A(s, ext_stmt_block)) {
	ExtractVariablesFrom_stmt_list(((struct ext_clast_block *)s)->body);
      } else {
	assert(0);
      }
    }
  }



  set<string*, GeneralUtilityClass::StringComparator> ExtractVariablesFrom_ext_clast_stmt(struct ext_clast_stmt *root)
  {
    variables.clear();
    ExtractVariablesFrom_stmt_list(root);
    return variables;
  }


}; // class VariableExtractor


#endif // !PTILE_VARIABLEEXTRACTOR_H
