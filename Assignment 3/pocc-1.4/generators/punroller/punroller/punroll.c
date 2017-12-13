/*
 * punroll.c: This file is part of the PAST-unroller project.
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

#include <assert.h>
#include <math.h>

#include <punroller/common.h>
#include <punroller/punroll.h>
#include <past/past_api.h>

static
void traverse_update_refs (s_past_node_t* node, void* data)
{
  if (past_node_is_a (node, past_varref))
    {
      PAST_DECLARE_TYPED(varref, pv, node);
      void** args = (void**)data;
      s_symbol_t* iter = args[0];
      if (symbol_equal (pv->symbol, iter))
	{
	  int* factor = args[1];
	  s_past_node_t*** map = args[2];
	  s_past_node_t* inc = past_node_value_create_from_int (*factor);
	  s_past_node_t* rep;
	  s_past_node_t* next = node->next;
	  node->next = NULL;
	  rep = past_node_binary_create (past_add, past_clone (node), inc);
	  int i;
	  for (i = 0; map[i][0]; ++i)
	    ;
	  map[i][0] = node;
	  map[i][1] = rep;
	  node->next = next;
	}
    }
}


int
punroll_update_increment (s_past_for_t* node, int size)
{
  s_past_node_t* inc = NULL;
  s_past_node_t* var = NULL;
  int val = 1;

  if (past_node_is_a (node->increment, past_inc_before) ||
      past_node_is_a (node->increment, past_inc_after))
    {
      PAST_DECLARE_TYPED(unary, pu, node->increment);
      if (! past_node_is_a (pu->expr, past_varref))
	return -1;
      inc = node->increment;
      var = pu->expr;
    }
  else if (past_node_is_a (node->increment, past_assign))
    {
      PAST_DECLARE_TYPED(binary, pb, node->increment);
      if (! past_node_is_a (pb->lhs, past_varref))
	return -1;
      PAST_DECLARE_TYPED(varref, pv, pb->lhs);
      if (! past_node_is_a (pb->rhs, past_add))
	return -1;
      PAST_DECLARE_TYPED(binary, pb2, pb->rhs);
      if (! past_node_is_a (pb2->lhs, past_varref))
	return -1;
      PAST_DECLARE_TYPED(varref, pv2, pb2->lhs);
      if (! symbol_equal (pv->symbol, pv2->symbol))
	return -1;
      if (! past_node_is_a (pb2->rhs, past_value))
	return -1;
      PAST_DECLARE_TYPED(value, pval, pb2->rhs);
      if (pval->type != e_past_value_int)
	return -1;
      val = pval->value.intval;
      if (val < 1)
	return -1;
    }
  else
    return -1;

  s_past_node_t* newinc =
    past_node_binary_create
    (past_assign, past_node_varref_create (node->iterator),
     past_node_binary_create
     (past_add, past_node_varref_create (node->iterator),
      past_node_value_create_from_int (size * val)));
  past_deep_free (node->increment);
  node->increment = newinc;

  return val;
}

static
int unroll_cost_model_adjust (s_past_node_t* node, int size, int nb_register)
{
  // Count the number of statements in the loop.
  int num_stmts = past_count_statements (node);

  // cost model: num_stmts * 2.5 * size < nb_register.
  int ret  = round ((float)nb_register / (num_stmts * 2.5));
  if (ret > size)
    ret = size;
  if (ret == 0)
    ret = 1;
  return ret;
}

static
s_past_node_t* create_init (s_past_varref_t* iter, int size)
{
  if (size == 0)
    size = 1;
  s_past_node_t* ret =
    past_node_binary_create
    (past_assign, past_clone ((s_past_node_t*)iter),
     past_node_binary_create
     (past_sub, past_clone ((s_past_node_t*)iter),
      past_node_value_create_from_int (size - 1)));

  return ret;
}


/**
 * Export for psimdkzer.
 *
 *
 */
void
punroll_unroll_cost (s_past_node_t* node, int size,
		     s_symbol_t* iter,
		     int nb_register)
{
  assert (past_node_is_a (node, past_for));
  PAST_DECLARE_TYPED(for, pf, node);
  // Cannot unroll without an ub.
  if (pf->test == NULL)
    return;
  // Nothing to do is size is 1.
  if (size == 1)
    return;

  // Adapt the unroll factor using a naive cost model based on the
  // number of statements and number of register.
  if (nb_register != -1)
    size = unroll_cost_model_adjust (node, size, nb_register);

  s_past_node_t* next;
  s_past_node_t* tmp;
  int i, j, k;

  // Duplicate the loop.
  s_past_node_t* loopepilog = past_clone (node);
  PAST_DECLARE_TYPED(for, pl, loopepilog);
	pl->body = past_clone(pf->body);
  past_deep_free (pl->init);
  pl->init = NULL;


  // Increment the loop body by the unroll size.
  int base_loop_inc = punroll_update_increment (pf, size);
  if (base_loop_inc < 1)
    {
      printf ("[PUnroll][WARNING] Unsupported loop increment\n");
      past_deep_free (loopepilog);
      return;
    }


  // Change the loop ub to ub - size, doing "iter -> iter - size + 1".
  int num_var_ref = 0;
  for (tmp = pf->test; tmp; tmp = tmp->next)
    num_var_ref += past_count_nodetype (tmp, past_varref);
  s_past_node_t*** map = XMALLOC(s_past_node_t**, num_var_ref + 1);
  for (i = 0; i < num_var_ref + 1; ++i)
    {
      map[i] = XMALLOC(s_past_node_t*, 2);
      map[i][0] = map[i][1] = NULL;
    }
  int factor = (base_loop_inc * size) - 1;
  void* args[3]; args[0] = iter; args[1] = &factor; args[2] = map;
  past_visitor (pf->test, traverse_update_refs, (void*)args, NULL, NULL);
  for (j = 0; map[j][0]; ++j)
    {
      past_replace_node (map[j][0], map[j][1]);
      past_deep_free (map[j][0]);
    }
  for (i = 0; i < num_var_ref + 1; ++i)
    XFREE(map[i]);
  XFREE(map);

  // Create a map to store the replacements.
  num_var_ref = 0;
  for (tmp = pf->body; tmp; tmp = tmp->next)
    num_var_ref += past_count_nodetype (tmp, past_varref);
  map = XMALLOC(s_past_node_t**, num_var_ref + 1);
  for (i = 0; i < num_var_ref + 1; ++i)
    {
      map[i] = XMALLOC(s_past_node_t*, 2);
      map[i][0] = map[i][1] = NULL;
    }
  // Find the end of the body.
  for (next = pf->body; next->next; next = next->next)
    ;

  // Duplicate the body.
  s_past_node_t* newbody[size - 1];
  for (i = 0; i < size - 1; ++i)
    newbody[i] = past_clone (pf->body);

  // Duplicate the body 'size - 1' times.
  for (i = 0; i < size - 1; ++i)
    {
      past_set_parent (newbody[i]);
      // Find the varref
      int ufact = (i + 1) * base_loop_inc;
      void* args[3]; args[0] = iter; args[1] = &ufact; args[2] = map;
      past_visitor (newbody[i], traverse_update_refs, (void*)args, NULL, NULL);

      // Substitute.
      for (j = 0; map[j][0]; ++j)
	{
	  s_past_node_t* nextp = map[j][0]->next;
	  map[j][0]->next = NULL;
	  past_replace_node (map[j][0], map[j][1]);
	  map[j][1]->next = nextp;
	  past_deep_free (map[j][0]);
	  map[j][0] = map[j][1] = NULL;
	}

      // Insert.
      next->next = newbody[i];
      newbody[i]->parent = node;
      for (next = newbody[i]; next && next->next; next = next->next)
	;
    }

  // Final insert.
//	printf("epilog print\n");
//	past_pprint(stdout,loopepilog);
  loopepilog->next = node->next;
//	printf("node next print\n");
//	past_pprint(stdout,node->next);
  node->next = loopepilog;

  // Be clean.
  for (i = 0; i < num_var_ref + 1; ++i)
    XFREE(map[i]);
  XFREE(map);
}

/**
 * Unroll systematically all inner loops by 'size'.
 *
 */
void
punroll_dummy (scoplib_scop_p scop, s_past_node_t* root, int size)
{
  past_set_parent (root);

  // 1- Find all inner-most loops.
  s_past_node_t** inner = past_inner_loops (root);

  // 2- Unroll them by the unroll factor.
  int i;
  for (i = 0; inner[i]; ++i)
    {
      assert (past_node_is_a (inner[i], past_for));
      PAST_DECLARE_TYPED(for, pf, inner[i]);
      punroll_unroll_cost (inner[i], size, pf->iterator, -1);
    }
  past_set_parent (root);
}

/**
 * Unroll inner-loops in order to not exceed register size. Rough
 * estimate (does not consider intra-register reuse). Do not exceed
 * max_ufactor unrolling of the loop anyway.
 *
 */
void
punroll (scoplib_scop_p scop, s_past_node_t* root,
	 int unroll_factor, int nb_register)
{
  past_set_parent (root);
  // 1- Find all inner-most loops.
  s_past_node_t** inner = past_inner_loops (root);

  // 2- Unroll them by the unroll factor.
  int i;
  for (i = 0; inner[i]; ++i)
    {
      // Do not unroll simd loops.
      if (past_node_is_a (inner[i], past_parfor))
	continue;
      assert (past_node_is_a (inner[i], past_for));
      PAST_DECLARE_TYPED(for, pf, inner[i]);
      punroll_unroll_cost (inner[i], unroll_factor, pf->iterator, nb_register);
    }

  past_set_parent (root);
}

// MK: Modified version of update_increment. Get the current increment of the unrolled loop
int punroll_get_increment (s_past_for_t* node)
{
  s_past_node_t* inc = NULL;
  s_past_node_t* var = NULL;
  int val = 1;

  if (past_node_is_a (node->increment, past_inc_before) ||
      past_node_is_a (node->increment, past_inc_after))
    {
      PAST_DECLARE_TYPED(unary, pu, node->increment);
      if (! past_node_is_a (pu->expr, past_varref))
	return -1;
      inc = node->increment;
      var = pu->expr;
    }
  else if (past_node_is_a (node->increment, past_assign))
    {
      PAST_DECLARE_TYPED(binary, pb, node->increment);
      if (! past_node_is_a (pb->lhs, past_varref))
	return -1;
      PAST_DECLARE_TYPED(varref, pv, pb->lhs);
      if (! past_node_is_a (pb->rhs, past_add))
	return -1;
      PAST_DECLARE_TYPED(binary, pb2, pb->rhs);
      if (! past_node_is_a (pb2->lhs, past_varref))
	return -1;
      PAST_DECLARE_TYPED(varref, pv2, pb2->lhs);
      if (! symbol_equal (pv->symbol, pv2->symbol))
	return -1;
      if (! past_node_is_a (pb2->rhs, past_value))
	return -1;
      PAST_DECLARE_TYPED(value, pval, pb2->rhs);
      if (pval->type != e_past_value_int)
	return -1;
      val = pval->value.intval;
      if (val < 1)
	return -1;
    }
  else
    return -1;

  return val;
}

static
s_past_node_t* get_enclosed_node (s_past_node_t* node)
{
	if (past_node_is_a (node,past_block))
		{
			PAST_DECLARE_TYPED (block, pb, node);
			return get_enclosed_node (pb->body);
		}
	else
		return node;
}

// test nestedness of inner loop with respect to
// its enclosing loop.
int punroll_is_perfectly_nested (s_past_node_t* inner)
{
	s_past_node_t* parent;
	for (parent = inner->parent;
			! past_node_is_a (parent, past_for);
			parent = parent->parent);
	PAST_DECLARE_TYPED (for, pfparent, parent);
	s_past_node_t* child = get_enclosed_node (pfparent->body) ;
	int i, pos_inner;
	// counts number of statements and inner loop position
	for (i = 0, pos_inner = -1 ; child; child = child->next, ++i)
		{
			if (child == inner) pos_inner = i;
		}
	// inner loop is the only statement inside its parent
	// hence it's perfectly nested
	if (i-1 == pos_inner && i == 1)
		{
			return 1;
		}
	// not perfecly nested
	else if (pos_inner != -1)
		{
			return 0;
		}
	// inner loop is not a child of its parent,
	// hence tree is inconsistent. This should not happen.
	return -1;
}

// checks for the existance of an affine guard/if
// conditional between an inner loop and the first
// enclosing outer loop
static
int has_nested_conditional (s_past_node_t* inner)
{
	s_past_node_t* pred;
	for (pred = inner->parent;
		pred && !past_node_is_a (pred, past_for);
		pred = pred->parent)
		if (past_node_is_a (pred, past_affineguard) ||
				past_node_is_a (pred, past_if))
			return 1;
	// must find an outer loop, otherwise abort
	assert (pred);
	// didn't find a conditional
	return 0;
}

// Unroll a single statement. Used for unrolling prologs and epilogs
s_past_node_t *
punroll_single_statement ( s_past_node_t * node, int size , s_past_for_t * loop)
{
	int base_loop_inc = punroll_get_increment ( loop );
  // Create a map to store the replacements.
  int num_var_ref ;
	int i,j;
	s_past_node_t*** map ;
  num_var_ref = past_count_nodetype (node, past_varref);
  map = XMALLOC(s_past_node_t**, num_var_ref + 1);
  for (i = 0; i < num_var_ref + 1; ++i)
    {
      map[i] = XMALLOC(s_past_node_t*, 2);
      map[i][0] = map[i][1] = NULL;
    }

  s_past_node_t* newbody[size - 1];
  for (i = 0; i < size - 1; ++i){
    newbody[i] = past_clone (node);
		newbody[i]->next  = NULL;
	}
  // Duplicate the body 'size - 1' times.
  for (i = 0; i < size - 1; ++i)
  {
      past_set_parent (newbody[i]);
      // Find the varref
      int ufact = (i + 1) * base_loop_inc;
      void* args[3]; args[0] = loop->iterator; args[1] = &ufact; args[2] = map;
      past_visitor (newbody[i], traverse_update_refs, (void*)args, NULL, NULL);
      // Substitute.
      for (j = 0; map[j][0]; ++j)
			{
						s_past_node_t* nextp = map[j][0]->next;
						map[j][0]->next = NULL;
						past_replace_node (map[j][0], map[j][1]);
						map[j][1]->next = nextp;
						past_deep_free (map[j][0]);
						map[j][0] = map[j][1] = NULL;
			}

      // Insert.
			node->next = newbody[i];
      newbody[i]->parent = (s_past_node_t*)loop;
			node = node->next;
   }
	return node; // return last node
}


/// MK: when called from polyopt loop statements might be enclosed
//	in multiple braces, and when unrolling and jamming imperfectly
//	nested loops, this becomes a problem. So  we remove them here.
static
void
remove_useless_blocks (s_past_node_t* outer)
{
	PAST_DECLARE_TYPED (for, pfo, outer);
	PAST_DECLARE_TYPED (block, pb, pfo->body);
	int is_useless = past_node_is_a (pb->body, past_block) ||
					past_node_is_a (pb->body, past_statement);
	if (! is_useless)
		return;
	s_past_node_t* first = NULL;
	s_past_node_t* last = NULL;
	s_past_node_t* currblock;
	s_past_node_t* curr;
	for (currblock = pfo->body; currblock; currblock = currblock->next)
		{
			curr = past_clone (get_enclosed_node (currblock));
			if (! last)
				first = last = curr;
			else
				last->next = curr;
			for ( ; last->next; last = last->next);
		}
	last->next = NULL;
	s_past_node_t* old_body = pfo->body;
	past_replace_node (old_body, first);
	past_deep_free (old_body);
}


// Loop 1: outer, loop 2: inner.
static
void
punroll_and_jam_loops_imperfect (scoplib_scop_p scop, s_past_node_t* root,
		       s_past_node_t* loop1, s_past_node_t* loop2,
		       int* size, int nb_register)
{
	if (past_node_is_a (loop1, past_for) && past_node_is_a (loop2, past_for))
		{
			PAST_DECLARE_TYPED (for, pf1, loop1);
			PAST_DECLARE_TYPED (for, pf2, loop2);
			int i;
			int perf_nest = punroll_is_perfectly_nested (loop2);
			// must not be perfectly nested.
			// Either way it won't get here if it's perfectly nested
			// and called from punroll_and_jam_loops,
			// So this must not happen. Nevertheless, someday someone
			// might decide to call this function in a direct manner.
			assert (perf_nest == 0);
			// First clone outer loop into the unrolled loop and the epilog
			s_past_node_t* outer_unrolled = past_clone (loop1);
			s_past_node_t* outer_epilog 	= past_clone (loop1);
			// unroll new outer loop
			punroll_unroll_cost (outer_unrolled, size[0], pf1->iterator, nb_register);
			// remove init node from epilog
			PAST_DECLARE_TYPED (for, pf1e, outer_epilog);
			past_deep_free (pf1e->init);
			pf1e->init = NULL;
			// link outer unrolled and outer epilog
			outer_unrolled->next = outer_epilog;
			// remove potential double braces which break
			// cause problems.
			remove_useless_blocks (outer_unrolled);
			// collect inner loops of outer_unrolled for unrolling them
			PAST_DECLARE_TYPED (for, pfou, outer_unrolled);
			s_past_node_t* first_child;
			s_past_node_t* first;
			// fetch the very fist statement of the unrolled loop body
			first_child = first = get_enclosed_node (pfou->body);
			s_past_node_t** inner = past_inner_loops (outer_unrolled);
			// unroll each inner loop and link properly.
			// do not use past_replace_node because this function
			// seems to replace node by node and not node by list.
			for (i = 0; inner[i]; ++i)
				{
					// store node that follows the current inner loop
					s_past_node_t* child_next = inner[i]->next;
					// clone inner loop
					s_past_node_t* new_inner = past_clone (inner[i]);
					// remove double braces if present
					remove_useless_blocks (new_inner);
					// unroll it
					punroll_unroll_cost (new_inner, size[1], pf2->iterator, nb_register);
					// most complicated part. Chain the nodes nicely.
					s_past_node_t* prev;
					s_past_node_t* next;
					// This conditional handles the case wherein the
					// inner loop is precisely the first statement of
					// the outer_unrolled.
					if (first_child == inner[i])
						{
							first = new_inner;
							past_replace_node (first_child, new_inner);
						}
					else
						{
							for (prev = first, next = first->next;
								 next != inner[i];
								 prev = next, next = next->next);
							prev->next = new_inner;
						}
					// unrolled inner loop has an epilog so use the
					// next->next field.
					new_inner->next->next = child_next;
					// unhook next of the original inner loop
					// before deep freeing.
					inner[i]->next = NULL;
					past_deep_free (inner[i]);
				}
			// set the parent field of the linked list
			past_set_parent (first);
			// replace old outer loop by new outer loop
			past_replace_node (loop1, outer_unrolled);
			// just in case link manually
			outer_epilog->next = loop1->next;
			loop1->next = NULL;
			// free old outer loop
			past_deep_free (loop1);
		}
  else
		fprintf (stderr, "[Punroll][WARNING] Input loops are not loops!\n");
}




// Unroll and jam perfectly nested loops.
// Loop 1: outer, loop 2: inner.
static
void
punroll_and_jam_loops_perfect (scoplib_scop_p scop, s_past_node_t* root,
		       s_past_node_t* loop1, s_past_node_t* loop2,
		       int* size, int nb_register)
{
  if (past_node_is_a (loop1, past_for) && past_node_is_a (loop2, past_for))
    {
			int perf_nest = punroll_is_perfectly_nested ( loop2 );
			assert ( perf_nest );

      PAST_DECLARE_TYPED(for, pf1, loop1);
      PAST_DECLARE_TYPED(for, pf2, loop2);
      // 0- Backup original body of outer loop.
      s_past_node_t* loop1_backup = past_clone (loop1);

      // 1- Unroll loop2 with loop2 iterator.
      s_past_node_t* backup_inc2 = past_clone (pf2->increment);
      punroll_unroll_cost (loop2, size[1], pf2->iterator, nb_register);
      // Backup correct loop2 increment.
      s_past_node_t* correct_inc2 = pf2->increment;
      // Restore original loop bound.
      pf2->increment = backup_inc2;
      backup_inc2 = past_clone (pf2->increment);
      // Backup new test.
      s_past_node_t* loop2_test = past_clone (pf2->test);

      // 2- Unroll loop2 with loop1 iterator.
			// This 2 lines were the bug:
			//s_past_node_t* l2_epilog = loop2->next;
			//loop2->next = NULL;
      punroll_unroll_cost (loop2, size[0], pf1->iterator, nb_register);
			// Bug fix:
			s_past_node_t* l2_epilog = loop2->next->next;
			loop2->next = NULL;
      // Delete useless epilog.
      past_deep_free (loop2->next);
      loop2->next = NULL;
      // Restore correct test.
      past_deep_free (pf2->test);
      pf2->test = loop2_test;
      // Restore correct increment.
      past_deep_free (pf2->increment);
      pf2->increment = correct_inc2;

			// MK: unroll loop prolog
			s_past_node_t * l1_prolog = pf1->body;
			if ( l1_prolog != loop2 )
			{
				while (l1_prolog != loop2 )
				{
					s_past_node_t* next = l1_prolog->next;
					l1_prolog = punroll_single_statement(l1_prolog,size[0], pf1);
					l1_prolog->next = next;
					l1_prolog = l1_prolog->next;
				}
			}

      // Unroll the epilog code for loop2 with loop1 iterator.
      if (l2_epilog)
			{
				s_past_node_t* le2_epilog = l2_epilog->next;
				l2_epilog->next = NULL;
				punroll_unroll_cost (l2_epilog, size[0], pf1->iterator, nb_register);
				// Set correct increment for epilog of loop2.
				PAST_DECLARE_TYPED(for, pf2e, l2_epilog);
				past_deep_free (pf2e->increment);
				pf2e->increment = backup_inc2;
				past_deep_free (l2_epilog->next);
				l2_epilog->next = le2_epilog;
				loop2->next = l2_epilog;
				/// MK: unroll epilog level 2
				if ( le2_epilog )
				{
					while ( le2_epilog )
					{
						s_past_node_t* next = le2_epilog->next;
						le2_epilog = punroll_single_statement(le2_epilog,size[0], pf1);
						le2_epilog->next = next;
						le2_epilog = le2_epilog->next;
					}
				}
			}

      // 3- unroll outer, to generate the epilogue code for loop1.
      loop1_backup->next = loop1->next;
      punroll_unroll_cost (loop1_backup, size[0], pf1->iterator, nb_register);
      // Insert the generated epilog after loop1.
      loop1->next = loop1_backup->next;
      loop1_backup->next = NULL;
      // Update test and increment of loop1.
      PAST_DECLARE_TYPED(for, pfb, loop1_backup);
      past_deep_free (pf1->test);
      pf1->test = past_clone (pfb->test);
      past_deep_free (pf1->increment);
      pf1->increment = past_clone (pfb->increment);
      // Delete useless unrolled loop.
      past_deep_free (loop1_backup);

      // Set parent node, just in case.
      past_set_parent (root);
    }
  else
    fprintf (stderr, "[Punroll][WARNING] Input loops are not loops!\n");
}


// Checks the nestedness property of the inner loop
// and calls the necessary function.
// Loop 1: outer, loop 2: inner.
void
punroll_and_jam_loops (scoplib_scop_p scop, s_past_node_t* root,
		       s_past_node_t* loop1, s_past_node_t* loop2,
		       int* size, int nb_register)
{
	if (has_nested_conditional (loop2))
	{
	  fprintf (stderr, "[Punroll] Unrolling is not possible due to nested conditionals!\n");
		assert (0);
	}
	if (punroll_is_perfectly_nested (loop2))
		punroll_and_jam_loops_perfect (scop, root,
		       loop1, loop2,
		       size, nb_register);
	else
		punroll_and_jam_loops_imperfect (scop, root,
		       loop1, loop2,
		       size, nb_register);
}


/**
 * Unroll a specific loop.
 *
 */
void punroll_unroll_loop (s_past_for_t* node, int size, int nb_register)
{
  punroll_unroll_cost (&(node->node), size, node->iterator, nb_register);
}


/**
 * FIXME: debug!
 */

void
punroll_and_jam (scoplib_scop_p scop, s_past_node_t* root,
		 int* size, int nb_register)
{
  // 1- Find all maximal perfectly nested loops.
  /// FIXME: TBD.
  /// Dummy test: u-a-j the first inner-most loop and its immediate
  /// parent loop.

  /* martin commented this:
     s_past_node_t* root_back = root;
     root = past_clone (root_back);
     end of martin's comment */
  past_set_parent (root);
  s_past_node_t** inloops = past_inner_loops (root);
  s_past_node_t* loop1 = NULL;
  s_past_node_t* loop2 = NULL;
  if (has_nested_conditional (inloops[0]))
    {
      fprintf (stderr, "[Punroll] Unrolling is not possible due to nested conditionals\n");
      assert (0);
    }

  if (inloops)
    {
      loop2 = inloops[0];
      s_past_node_t* tmp = loop2->parent;
      while (tmp && ! past_node_is_a(tmp, past_for)) tmp = tmp->parent;
      loop1 = tmp;
    }

  //   size[0] = 4;
  //   size[1] = 2;
  punroll_and_jam_loops (scop, root, loop1, loop2, size, nb_register);
  past_set_parent (root);
  //past_deep_free (root);
}
