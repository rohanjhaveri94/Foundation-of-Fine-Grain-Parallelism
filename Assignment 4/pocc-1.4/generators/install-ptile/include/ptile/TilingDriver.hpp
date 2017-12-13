/*
 * TilingDriver.hpp: This file is part of the Parametric Tiling project.
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

#ifndef PTILE_TILINGDRIVER_H
# define PTILE_TILINGDRIVER_H

#include <stdio.h>
#include <stdlib.h>
#include<string>
#include<iostream>
#include<vector>
#include <set>
#include<sstream>

#include <past/past.h>
# include <ptile/PTile.hpp>
# include <ptile/AstGenerator.hpp>
# include <ptile/ConvexHullFormer.hpp>
# include <ptile/Expression.hpp>
# include <ptile/ExpressionLibrary.hpp>
# include <ptile/GenericUtility.hpp>
# include <ptile/InputReaderParser.hpp>
# include <ptile/Polynomial.hpp>
# include <ptile/RSFME.hpp>
# include <ptile/ScoplibToExpressionConverter.hpp>
# include <ptile/Term.hpp>
# include <ptile/TileLoopInserter.hpp>
# include <ptile/Tiler.hpp>

class TilingDriver
{
public:

  static
  void traverse_for_replace (s_past_node_t* node, void* data);

  static
  void traverse_for_find_first (s_past_node_t* node, void* data);

  s_past_node_t* ReplaceFirstForLoopNest(s_past_node_t* ast,
					 s_past_node_t* tiledCode);

  s_past_node_t* FindFirstForLoop(s_past_node_t* s);

  // Input: Single for loop nest
  s_past_node_t* DriveTiling(s_past_node_t* inputAST,
			     scoplib_scop_p program,
			     s_ptile_options_t* options,
			     int nofuse);

  s_past_node_t* DriveTiling(vector<Expression*> *exprs,
			     s_past_node_t* pointLoops,
			     s_ptile_options_t* options,
			     int nofuse);

};//class Driver



#endif // !PTILE_TILINGDRIVER_H
