/*
 * punroll.h: This file is part of the PAST-unroller project.
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
#ifndef PUNROLLER_PUNROLL_H
# define PUNROLLER_PUNROLL_H


# ifndef SCOPLIB_INT_T_IS_LONGLONG
#  define SCOPLIB_INT_T_IS_LONGLONG
# endif
# define LINEAR_VALUE_IS_LONGLONG


# include <scoplib/scop.h>
# include <past/past.h>

BEGIN_C_DECLS


/**
 * Unroll systematically all inner loops by 'size'.
 *
 */
extern
void punroll_dummy (scoplib_scop_p scop, s_past_node_t* root, int size);

/**
 * Unroll inner-loops in order to not exceed register size. Rough
 * estimate (does not consider intra-register reuse). Do not exceed
 * max_ufactor unrolling of the loop anyway.
 *
 */
extern void
punroll (scoplib_scop_p scop, s_past_node_t* root, int max_ufactor,
	 int nb_register);

/**
 * Unroll-and-jam.
 *
 */
extern void
punroll_and_jam (scoplib_scop_p scop, s_past_node_t* root,
		 int* size, int nb_register);
/**
 * Unroll-and-jam loop1 by size[0], unroll loop2 by size[1].
 *
 */
extern void
punroll_and_jam_loops (scoplib_scop_p scop, s_past_node_t* root,
		       s_past_node_t* loop1, s_past_node_t* loop2,
		       int* size, int nb_register);
/**
 * Unroll a specific loop.
 *
 */
extern void
punroll_unroll_loop (s_past_for_t* node, int size, int nb_register);


/**
 * Get the increment of a for node. Returns a positive number.
 *
 */
extern int
punroll_get_increment (s_past_for_t* node);

/**
 * Update the increment of a for node.
 *
 */
extern
int
punroll_update_increment (s_past_for_t* node, int size);


/**
 * Check whether an innermost loop is perfectly nested
 * with respect to its enclosing (outer) loop.
 */
extern int
punroll_is_perfectly_nested ( s_past_node_t * inner );

/**
 * Export for psimdkzer.
 *
 */
void
punroll_unroll_cost (s_past_node_t* node, int size,
		     s_symbol_t* iter,
		     int nb_register);

END_C_DECLS


#endif // PUNROLLER_PUNROLL_H
