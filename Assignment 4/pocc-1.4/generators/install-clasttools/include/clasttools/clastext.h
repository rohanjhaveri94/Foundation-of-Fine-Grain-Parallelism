/*
 * clastext.h: this file is part of the ClastTools project.
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
#ifndef CLASTTOOLS_CLASTEXT_H
# define CLASTTOOLS_CLASTEXT_H

# include <clasttools/common.h>

# ifndef CLOOG_INT_GMP
#  define CLOOG_INT_GMP
# endif
# include <cloog/cloog.h>
# include <cloog/clast.h>


BEGIN_C_DECLS


// Declare new clast nodes, as used in PACE/PolyRose.
struct clast_pragma_omp_for {
    struct clast_stmt	stmt;
    const char *	clause;
};

struct clast_pragma_vectorize {
    struct clast_stmt	stmt;
    const char *	clause;
};

struct clast_parfor {
    struct clast_stmt	stmt;
    CloogDomain *	domain;
    const char *	iterator;
    struct clast_expr *	LB;
    struct clast_expr *	UB;
    cloog_int_t		stride;
    struct clast_stmt *	body;
};

struct clast_vectorfor {
    struct clast_stmt	stmt;
    CloogDomain *	domain;
    const char *	iterator;
    struct clast_expr *	LB;
    struct clast_expr *	UB;
    cloog_int_t		stride;
    struct clast_stmt *	body;
};

struct clast_user_stmt_extended {
    struct clast_stmt	stmt;
    CloogStatement *	statement;
    int			scop_statement_id;
    char*		define_string;
    struct clast_stmt *	substitutions;
};

extern const struct clast_stmt_op stmt_pragma_omp_for;
extern const struct clast_stmt_op stmt_pragma_vectorize;
extern const struct clast_stmt_op stmt_parfor;
extern const struct clast_stmt_op stmt_vectorfor;
extern const struct clast_stmt_op stmt_user_extended;

struct clast_pragma_omp_for*
new_clast_pragma_omp_for (const char* clause);

struct clast_pragma_vectorize*
new_clast_pragma_vectorize (const char* clause);

struct clast_parfor*
new_clast_parfor (const char *it, struct clast_expr *LB,
		  struct clast_expr *UB, cloog_int_t stride);

struct clast_vectorfor*
new_clast_vectorfor (const char *it, struct clast_expr *LB,
		     struct clast_expr *UB, cloog_int_t stride);

struct clast_user_stmt_extended*
new_clast_user_stmt_extended (CloogStatement *stmt,
			      struct clast_stmt *subs,
			      int scop_stmt_id,
			      char* define_string);


END_C_DECLS


#endif // CLASTTOOLS_CLASTEXT_H
