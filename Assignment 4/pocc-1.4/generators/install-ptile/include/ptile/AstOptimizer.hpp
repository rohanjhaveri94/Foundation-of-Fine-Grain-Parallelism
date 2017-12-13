/*
 * AstOptimizer.hpp: This file is part of the Parametric Tiling project.
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

#ifndef PTILE_ASTOPTIMIZER_H
# define PTILE_ASTOPTIMIZER_H

# include <ptile/PtileClasses.hpp>

class AstOptimizer
{

public: 
  static void HoistExpressionsInForLoops(s_past_node_t* node);
  static void TraverseToHoistLoopBoundExpressions (s_past_node_t* node, void* data);
  static s_past_node_t* HoistLoopBoundExpressions (s_past_for_t* forLoop);
  static s_past_node_t* HoistLoopBoundExpressionsWithoutDeclaration (s_past_for_t* forLoop);

};// class ASTOptimizer

#endif // !PTILE_ASTOPTIMIZER_H
