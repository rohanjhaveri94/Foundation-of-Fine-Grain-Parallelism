/*
 * PtileClasses.h: This file is part of the Parametric Tiling
 * project.
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

#ifndef PTILE_PTILECLASSES_H
# define PTILE_PTILECLASSES_H


#include <stdio.h>
#include <stdlib.h>

#include<string>
#include<iostream>
#include<vector>
#include <set>
#include<sstream>


#include <scoplib/scop.h>

// #include <cloog/isl/domain.h>
#include <scoptools/clast2scop.h>

#include <past/past.h>
#include <past/pprint.h>



# include <ptile/PTile.hpp>


# include <ptile/AstGenerator.hpp>
// # include <ptile/AstOptimizer.hpp>
# include <ptile/ConvexHullFormer.hpp>
# include <ptile/ExpressionLibrary.hpp>
// # include <ptile/FullTileMaker.hpp>
# include <ptile/GenericUtility.hpp>
# include <ptile/InputReaderParser.hpp>
//# include <ptile/Parallelizer.hpp>
# include <ptile/Polynomial.hpp>
# include <ptile/RSFME.hpp>
# include <ptile/ScoplibToExpressionConverter.hpp>
# include <ptile/Term.hpp>
# include <ptile/TileLoopInserter.hpp>
# include <ptile/Tiler.hpp>
# include <ptile/TilingDriver.hpp>
// # include <ptile/TilingPostProcessor.hpp>
// # include <ptile/VariableExtractor.hpp>



/// Ugly global to hold the symbol table...
extern s_symbol_table_t* g_ptil_symb_table;


#endif // ! PTILE_PTILECLASSES_H
