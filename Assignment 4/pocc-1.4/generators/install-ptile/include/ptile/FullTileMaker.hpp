/*
 * FullTileMaker.hpp: This file is part of the Parametric Tiling project.
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

#ifndef PTILE_FULLTILEMAKER_H
# define PTILE_FULLTILEMAKER_H

# include <ptile/PtileClasses.hpp>
# include <ptile/GenericUtility.hpp>

class FullTileMaker
{

public:
  static s_past_node_t* FullTileMakerDriver(s_past_node_t* point_loops, s_ptile_options_t* ptileOptions);

static s_past_node_t* BuildIfElseList (s_past_node_t* fullTiles, s_past_node_t* point_loops);

static s_past_node_t* BuildExclusivityConditionsForCurrentLevelForLoopNest (s_past_node_t* pointLoops, s_past_node_t* currentLoop, vector<string>* iteratorNames);

static s_past_node_t* CombineConditions (s_past_node_t* condition1, s_past_node_t* condition2);

static s_past_node_t* GetFullTile (s_past_node_t* prefixBody, s_past_node_t* currentLoop, s_ptile_options_t* ptileOptions);

static s_past_node_t* GenerateFullTileLoopNest (s_past_node_t* forLoopNest, s_past_node_t* body);

  
static s_past_node_t* BuildFullTiles(s_past_node_t* pointLoops, vector<string>* iteratorNames,
		 s_past_node_t* fullTileConditionPrefix,
		 s_past_node_t* fullTilePrefix, s_ptile_options_t* ptileOptions);

}; // class FullTileMaker


#endif // !PTILE_FULLTILEMAKER_H
