/*
 * Expression.hpp: This file is part of the Parametric Tiling project.
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

#ifndef PTILE_EXPRESSION_H
# define PTILE_EXPRESSION_H

# include <ptile/Term.hpp>
# include <ptile/Expression.hpp>

class Expression
{
  // An expression will have n + k + l Terms. n- loop iterators,
  // k - total number of parameters, l -> constant terms without a multiplier term

  /*
    Let there be it and jt loop iterators and s1, s2 tile sizes, N global parameter.

    -it + N/s2 + (-1)/s2
    is represented as:

    -1 [000/000], 1[000/010], -1[000/010]

  */

public:
  int size;
  Term *terms;

  Expression(int size);
  Expression();
  void AllocateMemory();
  void CloneFrom(Expression expr);
  int GetSize();
  void Print();
};

#endif // !PTILE_EXPRESSION_H
