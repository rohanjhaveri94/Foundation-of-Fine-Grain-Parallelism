/*
 * ExpressionLibrary.hpp: This file is part of the Parametric Tiling project.
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

#ifndef PTILE_EXPRESSIONLIBRARY_H
# define PTILE_EXPRESSIONLIBRARY_H

# include <ptile/PtileClasses.hpp>
# include <ptile/Term.hpp>
# include <ptile/Expression.hpp>

// This class will have the general utility functions operating on the expressions
class ExpressionLibrary
{
public:

  static void AddWInterTileLoopIteratorTermInExpression(vector<Expression*> *exprs, string name);
  static Term AddTerms(Term term1, Term term2);
  static void SetSignOfRightMostLoopIterator(Expression *expr, int sign, vector<Expression> MinValues, vector<Expression> MaxValues);

   // Returns +1 if the coefficient of the term is > 0, -1 if negative, 0 if it's 0.
  static int FindSignOfCoefficient(Term term);

  // Returns +1 if the coefficient of the term is > 0, -1 if negative, 0 if it's 0.
  static int FindSignOfCoefficient(Polynomial polynomial);
  static Expression AddExpressions(Expression expr1, Expression expr2);
  static Expression Add_Rows(Expression expr1, Expression expr2, bool *isResultNull);
  static void SetCoefficientOfRightmostIteratorOne(Expression *expr);
  static void MultiplyPolynomialsWithPolynomial(Polynomial *array, int size, Polynomial poly);
  static vector<Expression*>* CopyExpressions(vector<Expression*> *exprs);
  static void PrintExpressions(vector<Expression*> *exprs);
  static void PrintExpressions(vector<Expression> *exprs);
  static  bool ArePolynomialsEqual(Polynomial poly1, Polynomial poly2);
  static void CancelPolynomials(Polynomial *num, Polynomial *denom);
  static void GetCommonPolynomial(Polynomial *poly_array, int size, Polynomial *common);

  // Returns the index of the rightmost loop iterator. If not available returns -1
  static bool AreSetsOfPolynomialsEqual(Polynomial *poly1, int size1, Polynomial *poly2, int size2);

  // This method will take the common terms from the numerator and the denominator and cancel if possible and howmuchever is possible
  static void SimplifyTerm(Term *term);

  // This will compare everything except for the coefficients
  static bool AreTermsEqual(Term term1, Term term2);
  static int Find_Index_Of_RightmostLoopIterator(Expression expr);

  // Passing expression by reference
  static void MultiplyExpressionWithTerm(Expression *expr, Term term);
  static Term MultiplyTerms(Term term1, Term term2);

  // This method assumes that the polynomials to be multiplied are of the same length. This is because while adding the corresponding exponents from the two polynomials, it's essential to ascertain that they refer to the same variable.
  static Polynomial MultiplyPolynomials(Polynomial poly1, Polynomial poly2);
  static void ConvertExpressionsToInequalities(vector<Expression> *exprs);
  static void ConvertExpressionsToInequalities(vector<Expression*> *exprs);
  static float GetCoefficientOfRightmostIterator(Expression *expr);
  static int FindNumberOfTermsOfType(Expression *expr, TypeOfTerm type);
  static void AddItraTileLoopIteratorTermsInExpression(Expression *expr, int count,
						       int NumberOfIterators, int NumberOfParameters, int CurrentLevel, int TotalLevels);
  static string GetTileIteratorSuffix(int CurrentLevel, int TotalLevels);
  static string GetTileSizePrefix(int CurrentLevel, int TotalLevels);
  static void SubstituteIteratorWithIteratorPlusTileSize(vector<Expression*> *exprs, int CurrentLevel, int TotalLevels);
  static void PutTermsInOrder(vector<Expression*> *exprs);
  static void ReplaceIntraTileIteratorWithBounds(vector<Expression*> *exprs);
  static vector<string>* FindIteratorNames(vector<Expression*> *exprs);
  static bool IsPresentInStringVector(vector<string>* strings, string s);
};//class ExpressionLibrary


#endif // !PTILE_EXPRESSIONLIBRARY_H
