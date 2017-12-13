/*
 * options.h: This file is part of the Parametric Tiling project.
 *
 * Parametric Tiling: A CLAST-to-CLAST parametric tiling software
 *
 * Copyright (C) 2010 Sanket Tavargeri
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

#ifndef PTILE_OPTIONS_H
# define PTILE_OPTIONS_H

# include <past/past.h>


BEGIN_C_DECLS


struct ptile_options
{
  int fullTileSeparation; // 1 for full tile separation, 0 for basic tiling. Default: 0
  int level; // Levles of tiling. Default : 1
  int parallel; // 1 for parallel. 0 for sequential. Default: 0
  int RSFME; // 1 for performing RSFME
  int verbose_level;

  int data_is_char; // 1 if elements in scop (eg, iterator/parameter
		    //names) are char, 0 if they are void*.

  int quiet; // 1 if no output is to be printed on stdout. Default: 0.

  /// For internal use. Store the symbol table of newly created symbols.
  s_symbol_table_t* symboltable;

  int EvolveTile; // 1 - if adaptive tiled code is to generated; Default: 0

}; // struct ptileOptions
typedef struct ptile_options s_ptile_options_t;


s_ptile_options_t* ptile_options_malloc ();

void ptile_options_free (s_ptile_options_t* ptopts);




END_C_DECLS

#endif // PTILE_PTILE_H
