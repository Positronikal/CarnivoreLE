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

int us_r (void);

extern FILE *logfile_a;
extern char logname[PATH_MAX];
extern char outputdir[PATH_MAX];

/* Capture user account info using dscl */
int
us_reaper ()
{
  int done;
  int ch;

  done = FALSE;
  while (!done)
    {
      printf ("Capture all user accounts/UID data? /dscl/ [y/n]\n");
      ch = getchar ();

      if (ch == 'N' || ch == 'n')
        {
          printf ("Skipping all user accounts/UID data...\n\n");
          gettime ();
          logfile_a = fopen (logname, "a");
          fprintf (logfile_a, "        :us_reaper module skipped.\n");
          fclose (logfile_a);
          done = TRUE;
        }
      else if (ch == 'Y' || ch == 'y')
        {
          printf ("Starting all user accounts/UID data capture...");
          gettime ();
          logfile_a = fopen (logname, "a");
          fprintf (logfile_a, "        :us_reaper module started.\n");
          fclose (logfile_a);

          /* List all user accounts/UIDs */
          us_r ();

          printf ("done.\n\n");
          gettime ();
          logfile_a = fopen (logname, "a");
          fprintf (logfile_a, "        :us_reaper module complete.\n");
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
  while ((ch = getchar ()) != '\n' && ch != EOF);

  return (0);
}

/* Call to dscl */
int
us_r ()
{
  char allusers[PATH_MAX];

  snprintf (allusers, sizeof (allusers),
	    "/usr/bin/dscl . list /users UniqueID >> %s/useraccounts.txt",
	    outputdir);
  system (allusers);

  return (0);
}
