/*
 * ConvexHullFormer.hpp: This file is part of the Parametric Tiling project.
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

#ifndef PTILE_CONVEXHULLFORMER_H
# define PTILE_CONVEXHULLFORMER_H

# include <ptile/PtileClasses.hpp>


class ConvexHullFormer
{

private:
  static  void ScoplibStatementToCloogDomain(scoplib_statement_p scopStatement, CloogDomain** cloogDomain);  
  static  void CreateDefaultCloogDomainForContext(scoplib_statement_p scopStatement, CloogDomain** cloogDomain);    
  static int ScoplibToCloogDomains(scoplib_scop_p inputScop, CloogDomain*** cloogDomains);    
  static int* cloog_domain_to_ints(CloogDomain* convex_domain);
  static int* ExtractIteratorInequalities(int *domain, scoplib_scop_p inputScop);
  static int* ExtractIteratorInequalities2(int *domain, scoplib_scop_p inputScop);
  static int* ArrangeDomainInOrder(int *domain, scoplib_scop_p inputScop);
  static scoplib_scop_p cloog_domain_to_scoplib(int* convex_domain,
						scoplib_scop_p inputScop);	
  static scoplib_scop_p cloog_domain_to_scoplib(CloogDomain* convex_domain, scoplib_scop_p inputScop);

public:
  static scoplib_scop_p CreateConvexHull(scoplib_scop_p inputScop);
};//class ConvexHullFormer

#endif //  !PTILE_CONVEXHULLFORMER_H
