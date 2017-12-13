/*
 * TilingPostProcessor.hpp: This file is part of the Parametric Tiling project.
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

#ifndef PTILE_TILINGPOSTPROCESSOR_H
# define PTILE_TILINGPOSTPROCESSOR_H

# include <ptile/PtileClasses.hpp>
# include <ptile/VariableExtractor.hpp>

class TilingPostProcessor
{

public:
  static void WriteMinMaxMacros(FILE *parametricallyTiledFile)
  {
    fprintf (parametricallyTiledFile, "#define max(i,j) ((i)>(j)?(i):(j))\n");
    fprintf (parametricallyTiledFile, "#define min(i,j) ((i)<(j)?(i):(j))\n");
  }// static void WriteMinMaxMacros(FILE *parametricallyTiledFile)


  static void WriteStatementMacros(FILE *parametricallyTiledFile, scoplib_scop_p program)
  {
    //printf("Printing the defines begins\n");  
    int st_count = 1;
    scoplib_statement_p stm;
    int i;
    int nb_scatt = 0;
    for (stm = program->statement; stm; stm = stm->next)
      {
	fprintf (parametricallyTiledFile, "#define S%d(", st_count++);
	for (i = 0; i < stm->nb_iterators; ++i)
	  {
	    fprintf (parametricallyTiledFile, "%s", stm->iterators[i]);
	    if (i < stm->nb_iterators - 1)
	      fprintf (parametricallyTiledFile, ",");
	  }
	fprintf (parametricallyTiledFile, ") %s\n", stm->body);
	nb_scatt = stm->schedule->NbRows > nb_scatt ?
	  stm->schedule->NbRows : nb_scatt;
      }

    //printf("Printing the defines ends\n");
  }// static void WriteStatementMacros(FILE *foo, scoplib_scop_p program)

  static void DeclareVariablesCreated(FILE *parametricallyTiledFile, struct ext_clast_stmt *root, struct ext_clast_stmt *primitive_root)
  {

    VariableExtractor variableExtractor;
    //printf("Calling ExtractVariablesFrom_ext_clast_stmt()\n");
    set<string*, GeneralUtilityClass::StringComparator> variables = variableExtractor.ExtractVariablesFrom_ext_clast_stmt(root);
    //printf("Returned from ExtractVariablesFrom_ext_clast_stmt()\n");

    // Collect the variables which already existed in the untiled loop nest. Should NOT declare them again.
    VariableExtractor variableExtractor2;
    set<string*, GeneralUtilityClass::StringComparator> alreadyDeclaredVariables = variableExtractor2.ExtractVariablesFrom_ext_clast_stmt(primitive_root);
	    

    //printf("Testing the size of variables set\n");
    if (variables.size() == 0)
      {
	return;
      }// if (variables.size() == 0)

    //printf("The size of variables set is non-zero\n");

    //printf("Printing int keyword\n");
    fprintf(parametricallyTiledFile, "%s ", (GeneralUtilityClass::GetIntegerKeyword()).c_str());
    //printf("Printed int keyword\n");

    set<string*, GeneralUtilityClass::StringComparator>::iterator it;
    set<string*, GeneralUtilityClass::StringComparator>::iterator it2;
    //printf("For loop beginning\n");  
    for ( it=variables.begin() ; it != variables.end(); )
      {
	bool alreadyDeclared = false;
	it2 = alreadyDeclaredVariables.find(*it);
	if (it2 != alreadyDeclaredVariables.end())
	  {
	    alreadyDeclared = true;
	  }// if (it2 != alreadyDeclaredVariables.end())

	if (alreadyDeclared == false)
	  {
	    fprintf(parametricallyTiledFile, "%s", (**it).c_str());
	  }// if (alreadyDeclared == false)

	it++;
	if (it != variables.end() && alreadyDeclared == false)
	  {
	    fprintf(parametricallyTiledFile, ", ");
	  }// if ((it + 1) != variables.end())
      }// for ( it=variables.begin() ; it != variables.end(); it++ )
	
    fprintf(parametricallyTiledFile, ";\n");
    //cout<<endl;
  }// static void DeclareVariablesCreated(struct ext_clast_stmt *root)

  static void PostProcess(FILE *parametricallyTiledFile, scoplib_scop_p program, struct ext_clast_stmt *root, struct ext_clast_stmt *primitive_root, int indent, CloogOptions *options)
  {
    WriteMinMaxMacros(parametricallyTiledFile);
    WriteStatementMacros(parametricallyTiledFile, program);
    //printf("Calling DeclareVariablesCreated()\n");
    DeclareVariablesCreated(parametricallyTiledFile, root, primitive_root);
    //printf("Returning from DeclareVariablesCreated()\n");
  }// static PostProcess(FILE *foo, scoplib_scop_p program, struct ext_clast_stmt *root, int indent, CloogOptions *options)
}; // class TilingPostProcessor


#endif // !PTILE_TILINGPOSTPROCESSOR_H
