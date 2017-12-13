/*
 * Polynomial.hpp: This file is part of the Parametric Tiling project.
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

#ifndef PTILE_POLYNOMIAL_H
# define PTILE_POLYNOMIAL_H

# include <string>

using namespace std;

class Polynomial
{
public:
  int size;
  float coefficient;
  int *exponents;
  string *names;

  Polynomial(int size);
  Polynomial();
  Polynomial(int size, string *exponent_names);
  void AllocateMemory();
  void CopyExponentNames(string *param_names);
  void CloneFrom(Polynomial poly);
  Polynomial GetIdentityPolynomial(string *exponent_names);
  void SetCoefficientAt(int position, int coefficient);
  void Print();
};

#endif // !PTILE_POLYNOMIAL_H
