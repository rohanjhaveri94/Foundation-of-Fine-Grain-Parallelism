/*
 * Term.hpp: This file is part of the Parametric Tiling project.
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

#ifndef PTILE_TERM_H
# define PTILE_TERM_H

# include <ptile/Polynomial.hpp>
# include <string>

using namespace std;
enum TypeOfTerm {loop_iterator, parameter, constant, intraTile_loop_iterator, interTile_loop_iterator};

class Term
{
public:
  // Data members
  TypeOfTerm type;
  float coefficient;
  string name;

  // Both numerator and denominator can be expressed as sum of polynomials
  int num_polynomials_in_numerator;
  Polynomial* numerator;

  int num_polynomials_in_denominator;
  Polynomial* denominator;

  // Change this to store a pointer to the variable in ROSE
  char var;

  // Methods

  Term();
  Term(int num_count, int denom_count);
  void SetIdentityNumeratorDenominator();
  void SetIdentityNumeratorDenominator(int exponentsInPolynomial, string *exponent_names);
  void SetNumeratorDenominator(int num_polynomials_in_numerator,
			       Polynomial* numerator,
			       int num_polynomials_in_denominator,
			       Polynomial* denominator);
  void SetIdentityTermFrom(Term term);
  void SetTypeOfTerm(TypeOfTerm type);
  void CloneFrom(Term term);
  void AllocateMemory();
  TypeOfTerm GetType(int inputType);
  int GetTypeFromTypeOfTerm(TypeOfTerm inputType);
  string GetTypeStringFromTypeOfTerm(TypeOfTerm inputType);
  void MakeReciprocal(Term term);
  void Print();
}; // class Term ends


#endif // !PTILE_TERM_H
