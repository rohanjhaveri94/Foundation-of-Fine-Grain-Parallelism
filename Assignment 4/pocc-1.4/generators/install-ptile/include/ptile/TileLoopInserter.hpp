/*
 * TileLoopInserter.hpp: This file is part of the Parametric Tiling project.
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

#ifndef PTILE_TILELOOPINSERTER_H
# define PTILE_TILELOOPINSERTER_H

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
# include <ptile/SecondLevelTiler.hpp>

class TileLoopInserter
{

public:

  s_past_node_t* GetTaskBodyForPath (s_past_node_t* pointLoops, string path, string IteratorsInPath);

  void InsertPointLoopsInsideTileLoops (s_past_node_t* tileLoops, s_past_node_t* pointLoops, string path, string iteratorsInPath, 
                                        s_ptile_options_t* ptileOptions, s_past_node_t* innerTileLoops);
  void InsertPointLoopsInsideTileLoops (s_past_node_t* tileLoops, s_past_node_t* pointLoops, s_ptile_options_t* ptileOptions, s_past_node_t* innerTileLoops = NULL);

  void CombineCorrespondingLoops (s_past_node_t* loop1, s_past_node_t* loops2);

  s_past_node_t* CombineTileLoopsAndRSFMELoopsInOrder (s_past_node_t* rsfmeLoops, s_past_node_t* tileLoops);

  s_past_node_t* ReturnForLoopCorrespondingToIterator (char *iteratorName, s_past_node_t* loops, int clone);

  s_past_node_t* BuildTileLoopsFromPointLoopStructure (s_past_node_t* pointLoops, s_past_node_t* tileLoops, s_ptile_options_t* ptileOptions, int tileLevel, int totalTileLevels);

  s_past_node_t* CombineExpressions(s_past_node_t* expr1, s_past_node_t* expr2,
				    int type);

  s_past_node_t* CombineTileLoopsAndRSFMELoops(struct TileLoops tileLoopsStruct);

  s_past_node_t*
  InsertTileLoops(s_past_node_t* point_loops,
		  struct TileLoops tileLoopsStruct,
		  s_ptile_options_t* ptileOptions);
	
  s_past_node_t*
  InsertTileLoopsInOriginalLoopOrder(s_past_node_t* point_loops,
		  struct TileLoops tileLoopsStruct,
		  s_ptile_options_t* ptileOptions, s_past_node_t* innerTileLoops = NULL);

  void ModifyBoundsOfPointLoops(s_past_node_t* PointLoops);
  s_past_node_t* GetInnerTileLoopsForPath (s_past_node_t* innerTileLoops, string IteratorsInPath);
};


#endif // !PTILE_TILELOOPINSERTER_H
