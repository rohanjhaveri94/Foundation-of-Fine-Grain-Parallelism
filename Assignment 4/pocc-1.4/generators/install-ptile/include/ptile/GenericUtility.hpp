/*
 * GenericUtility.hpp: This file is part of the Parametric Tiling project.
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

#ifndef PTILE_GENERICUTILITY_H
# define PTILE_GENERICUTILITY_H

#if HAVE_CONFIG_H
# include <ptile/config.h>
#endif

#include <past/past.h>
# include <ptile/PTile.hpp>
# include <ptile/AstGenerator.hpp>
# include <ptile/ConvexHullFormer.hpp>
# include <ptile/Expression.hpp>
# include <ptile/ExpressionLibrary.hpp>
# include <ptile/InputReaderParser.hpp>
# include <ptile/Polynomial.hpp>
# include <ptile/RSFME.hpp>
# include <ptile/Term.hpp>
# include <ptile/TileLoopInserter.hpp>
# include <ptile/Tiler.hpp>
# include <ptile/TilingDriver.hpp>

using namespace std;



class GeneralUtilityClass
{
public:

  struct StringComparator
  {
    bool operator()(string* s1, string* s2) const;
  };

  static void RemoveDuplicatesInStringVector (vector<string>* names);
  static s_past_for_t* CreateForLoop (char* iterator, s_past_node_t* lb, s_past_node_t* ub, s_ptile_options_t* options);
  static char* GetTileIteratorFromIterator (char *iterator, int CurrentLevel, int TotalLevels);
  static string NumberToString ( int Number );
  static string GetIntegerKeyword();
  static string GetArrayAppendixString();
  static string GetPartitionString();
  static string GetTempString();
  static string GetIdString();
  static string GetTileString();
  static string GetRangeString();
  static char* StringToChar(string s);
  static string GetEstimatedTilesString();
  static string GetNumberOfPartitionsString();
  static string GetIteratorString();
  static CloogStride* GetDefaultStride();
  static string GetMaxNumberOfPartitionsString();
  static string GetTotalEstimatedTilesString();
  static string GetStrideString();
  static s_past_node_t* GetLastNode(s_past_node_t* head);
  static string GetGlobalEstimateWavefrontName();
  static string GetCurrentEstimatePrefix();
  static string GetGlobalEstimateSuffix();
  static string GetGlobalEstimatePrefix();
  static string GetLocalEstimatePrefix();
  static string GetGlobalEstimateMin_suffix();
  static string GetGlobalEstimateMax_suffix();
  static string GetOld_suffix();
  static string GetGlobalEstimateFull_suffix();
  static string GetGlobalEstimateInflection_suffix();
  static string GetGlobalEstimateMin_prefix();
  static string GetGlobalEstimateMax_prefix();

  static s_past_node_t* GetPastNodeFromString (string str, s_ptile_options_t* options);
  static s_past_node_t* past_clone_WithSameCloogStatements (s_past_node_t* node);
  static void StoreCloogStatments (s_past_node_t* node, void* data);
  static void ReplaceCloogStatments (s_past_node_t* node, void* data);
  static s_past_node_t*
  GetTileBoundForIterator(char *iteratorName,
			  int boundType, int purpose, int prefix);
  static bool IsPresentInNames(vector<string>* iteratorNames, char *name);
  static void test();
  struct gu_args;  
  static
  void traverse_tree_replace_iter(s_past_node_t* node, void* data);  
  static s_past_node_t*
  GetBoundEliminatingPointLoopIterators(s_past_node_t* e, int boundType,
					vector<string>* iteratorNames, 
					int purpose, int prefix);  
  static void
  traverse_collect_iterator_names(s_past_node_t* node, void* data);

  static vector<string>* CollectIteratorNames(s_past_node_t* pointLoops);
  static s_past_node_t* FindInnermostForLoopInLoopNest(s_past_node_t* tileLoops);
  static int getIndex2D(int i1, int i2, int n2);
  static int getIndex3D(int i1, int i2, int n2, int i3, int n3);
  static int getIndex4D(int i1, int i2, int n2, int i3, int n3, int i4, int n4);
  static vector<Expression*>* FormExpressions(int *StatementDomains, int len, int DomainRows, int DomainColumns,
					      int NumberOfIterators, int NumberOfParameters,
					      int ParamNamesSet, string* ParamNames, int IteratorNamesSet, string* IteratorNames);
  static int NumberForLoopHierarchy (s_past_node_t* stmt, int id, int skip_otl);
  static void DeNumberForLoopHierarchy (s_past_node_t* stmt);
  static s_past_node_t* HoistUpperBoundOfForLoop (s_past_for_t* forLoop, s_ptile_options_t* options);
  static s_past_node_t* HoistBoundsOfForLoop (s_past_for_t* forLoop, s_ptile_options_t* options);
}; //static class GeneralUtilityClass


#endif // !PTILE_GENERICUTILITY_H
