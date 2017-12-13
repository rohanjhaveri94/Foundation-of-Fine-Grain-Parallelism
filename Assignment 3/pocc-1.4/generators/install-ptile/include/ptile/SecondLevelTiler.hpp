/*
 * SecondLevelTiler.hpp: This file is part of the Parametric Tiling project.
 * 
 * Parametric Tiling: A CLAST-to-CLAST parametric tiling software
 * 
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

#ifndef SECONDLEVELTILER_HPP
# define SECONDLEVELTILER_HPP

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
# include <ptile/TilingDriver.hpp>



class SecondLevelTiler
{

public:   

  static struct TileLoops Tile(vector<Expression*> *exprs, s_ptile_options_t* options);
  static vector<Expression*>* ConstructTiledIterationExpressions (vector<Expression*> *exprs);
  static s_past_node_t* InsertTileLoops(s_past_node_t* point_loops,
		  struct TileLoops tileLoopsStruct1, struct TileLoops tileLoopsStruct2,
		  s_ptile_options_t* ptileOptions);
  static void ModifyBoundsOfPointLoops(s_past_node_t* PointLoops);
  static void ModifyIncrementSize (s_past_node_t* node, void* args);
  static void ModifyBoundsOfPointLoopsOuterTileLoopChecks(s_past_node_t* PointLoops);
// Distributes the statements - doesn't fuse
  static s_past_node_t* InsertTileLoopsInOriginalLoopOrder(s_past_node_t* point_loops,
		  struct TileLoops tileLoopsStruct1, struct TileLoops tileLoopsStruct2,
		  s_ptile_options_t* ptileOptions);

  static void ModifyBoundsOfPointLoopsForTwoLevelTiling(s_past_node_t* point_loops);
};//class SecondLevelTiler


#endif // !SECONDLEVELTILER_HPP
