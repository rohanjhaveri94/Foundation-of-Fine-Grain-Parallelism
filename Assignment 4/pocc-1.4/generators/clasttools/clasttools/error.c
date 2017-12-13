/*
 * error.c: this file is part of the ClastTools project.
 * 
 * ClastTools, a set of extensions to the standard CLAST hierarchy
 * 
 * Copyright (C) 2010 Louis-Noel Pouchet
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
 * Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
 */
#if HAVE_CONFIG_H
# include <clasttools/config.h>
#endif

#include <clasttools/common.h>
#include <clasttools/error.h>

static void error (int exit_status, const char *mode, 
		   const char *message);

const char *program_name = NULL;

void
set_program_name (const char *path)
{
  if (! program_name)
    program_name = xstrdup (basename (path));
}

static void
error (int exit_status, const char *mode, const char *message)
{
  fprintf (stderr, "%s: %s: %s.\n", program_name, mode, message);

  if (exit_status >= 0)
    exit (exit_status);
}

void
clasttools_warning (const char *message)
{
  error (-1, "warning", message);
}

void
clasttools_error (const char *message)
{
  error (-1, "ERROR", message);
}

void
clasttools_fatal (const char *message)
{
  error (EXIT_FAILURE, "FATAL", message);
}
