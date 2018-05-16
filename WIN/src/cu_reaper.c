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

#include <windows.h>
#include <limits.h>
#include <stdio.h>
#include "../include/carnivore.h"
#include <stdlib.h>

int cu_r (void);
extern FILE *logfile_a;
extern char logname[PATH_MAX];
extern char outputdir[PATH_MAX];

/* Capture current users using whoami */
int
cu_reaper ()
{
  int done;
  int ch;

  done = FALSE;
  while (!done)
    {
      printf ("\nCapture current user details? /whoami.exe/ [y/n]\n");
      ch = getchar ();

      if (ch == 'N' || ch == 'n')
	{
	  printf ("Skipping current user details...\n\n");
	  gettime ();
	  logfile_a = fopen (logname, "a");
	  fprintf (logfile_a, "        :cu_reaper module skipped.\n");
	  fclose (logfile_a);
	  done = TRUE;
	}
      else if (ch == 'Y' || ch == 'y')
	{
	  printf ("Starting current user details capture...");
	  gettime ();
	  logfile_a = fopen (logname, "a");
	  fprintf (logfile_a, "        :cu_reaper module started.\n");
	  fclose (logfile_a);

	  /* List currently logged on users */
	  cu_r ();

	  printf ("done.\n\n");
	  gettime ();
	  logfile_a = fopen (logname, "a");
	  fprintf (logfile_a, "        :cu_reaper module complete.\n");
	  fclose (logfile_a);
	  done = TRUE;
	}
      else
	{
	  printf ("You must enter a 'y' or 'n'\n");
	  while ((ch = getchar ()) != '\n' && ch != EOF);
	}
    }

  /* Flush input buffer */
  while ((ch = getchar ()) != '\n' && ch != EOF)
    /* discard */ ;

  return (0);
}

/* Call to whoami */
int
cu_r ()
{
  char currentuser[PATH_MAX];

  snprintf (currentuser, sizeof (currentuser),
	    "C:\\Windows\\System32\\whoami.exe /all > %s\\currentuser.txt",
	    outputdir);
  system (currentuser);

  return (0);
}
