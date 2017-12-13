/*
 * Tiler.hpp: This file is part of the Parametric Tiling project.
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

#ifndef PTILE_TILER_H
# define PTILE_TILER_H

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


struct TileLoops
{
  s_past_node_t* tileLoops;
  s_past_node_t* rsfmeLoops;
}; // struct TileLoops


class Tiler
{

public:   

  struct RSFME_Expressions
  {
    vector<Expression> *Lo;
    vector<Expression> *Uo;
    vector<Expression> *Lw;
    vector<Expression> *Uw;
    vector<Expression> *MinValues;
    vector<Expression> *MaxValues;	 	 	 			
  };// struct RSFME_Expressions

 
public:
         
  vector<Expression>* ConstructLwUw(vector<Expression*> *exprs, int CoefficientOfFirstIterator, string name);

  struct RSFME_Expressions PrepareRSFME_ExpressionsFromExpressions(vector<Expression*> *exprs);
   
  struct TileLoops Tile(vector<Expression*> *exprs,
			s_ptile_options_t* ptileOptions, int CurrentLevel, int TotalLevels);
};//class Tiler


#endif // !PTILE_TILER_H
