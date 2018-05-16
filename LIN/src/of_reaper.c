/* CarnivoreLE (Live Edition)

 Copyright (C) 2017 Hoyt Harness <hoyt.harness@gmail.com>

 This file is part of CarnivoreLE.

 CarnivoreLE is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 CarnivoreLE is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with CarnivoreLE.  If not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 MA 02110-1301, USA.
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/carnivore.h"

int of_r (void);

extern FILE *logfile_a;
extern char logname[PATH_MAX];
extern char outputdir[PATH_MAX];

/* Capture open file data using lsof */
int
of_reaper ()
{
  int done;
  char ch;

  done = FALSE;
  while (!done)
    {
      printf ("Capture data on all open files? /lsof/ [y/n]\n");
      ch = getchar ();

      if (ch == 'N' || ch == 'n')
	{
	  printf ("Skipping open file data...\n\n");
	  gettime ();
	  logfile_a = fopen (logname, "a");
	  fprintf (logfile_a, "        :of_reaper module skipped.\n");
	  fclose (logfile_a);
	  done = TRUE;
	}
      else if (ch == 'Y' || ch == 'y')
	{
	  printf ("Starting open file data capture...");
	  gettime ();
	  logfile_a = fopen (logname, "a");
	  fprintf (logfile_a, "        :of_reaper module started.\n");
	  fclose (logfile_a);

	  /* List all open files */
	  of_r ();

	  printf ("done.\n\n");
	  gettime ();
	  logfile_a = fopen (logname, "a");
	  fprintf (logfile_a, "        :of_reaper module complete.\n");
	  fclose (logfile_a);
	  done = TRUE;
	}
      else
	{
	  printf ("You must enter a 'y' or 'n'\n");
	  fflush (stdin);
	}
    }

  /* Flush input buffer */
  while ((ch = getchar ()) != '\n' && ch != EOF);

  return (0);
}

/* Call to lsof */
int
of_r ()
{
  char ofiles[PATH_MAX];

  /* NOTE: By default, lsof creates a user-readable and user-writable
     device cache file in the home directory of the EID upon execution. */
  snprintf (ofiles, sizeof (ofiles), "/usr/bin/lsof -lnR > %s/openfiles.txt",
	    outputdir);
  system (ofiles);

  return (0);
}
