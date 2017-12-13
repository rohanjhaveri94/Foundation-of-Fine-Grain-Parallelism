/*
 * TilingDriver.hpp: This file is part of the Parametric Tiling project.
 *
 * Parametric Tiling: A CLAST-to-CLAST parametric tiling software
 *
 * Copyright (C) 2011
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

#ifndef PTILE_EVOLVETILE_H
# define PTILE_EVOLVETILE_H

#include <past/past.h>
# include <ptile/GenericUtility.hpp>

class EvolveTileGenerator
{

public:
        static void CollectOuterMostIteratorName (s_past_node_t* node, void* data);
	static void CollectOuterMostIteratorLowerBound (s_past_node_t* node, void* data);
	static void AddGlobalMinConstraintToOuterLoop (s_past_node_t* node, void* data);
	static s_past_node_t* EvolveTileCodeGenerateForOuterParallelLoop(s_past_node_t* pointLoops, s_past_node_t* tileLoops, 
								s_past_node_t* tiledCode, s_ptile_options_t* options);
        static s_past_node_t* CreateStripMinedOuterLoop (s_past_node_t* tileLoops, s_past_node_t* pointLoops, s_ptile_options_t* options);
	static s_past_node_t* PrepareOuterParallelEvolveCode (s_past_node_t* stripminedOuterLoop, 
					s_past_node_t* pointLoops, s_past_node_t* tileLoops, s_past_node_t* tiledCode, s_ptile_options_t* options);
	static void AddGlobalMinConstraint (s_past_node_t* pointLoops, s_past_node_t* evolvedCode);
	static s_past_node_t* GenerateSwitchCode (s_past_node_t* pointLoops, s_past_node_t* stripminedOuterLoop, string outerPointIteratorName, s_ptile_options_t* options);
	static s_past_node_t* FormGuardConditionToSwitchCode (string outerPointIteratorName, s_ptile_options_t* options);
	static void FillSwitchCodeBody (s_past_node_t* pointLoops, s_past_node_t* stripminedOuterLoop, string outerPointIteratorName, s_past_node_t* ifCondition, s_ptile_options_t* options);
	static s_past_node_t* GetSelfAssignmentStatement (string str);
}; // class EvolveTileGenerator

#endif // PTILE_EVOLVETILE_H
