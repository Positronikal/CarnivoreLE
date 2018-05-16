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

int hw_r (void);

extern FILE *logfile_a;
extern char logname[PATH_MAX];
extern char outputdir[PATH_MAX];

/* Capture hardware inventory using lshw */
int
hw_reaper ()
{
  int done;
  char ch;

  done = FALSE;
  while (!done)
    {
      printf ("Capture hardware inventory? /sudo, lshw/ [y/n]\n");
      ch = getchar ();

      if (ch == 'N' || ch == 'n')
	{
	  printf ("Skipping hardware inventory...\n\n");
	  gettime ();
	  logfile_a = fopen (logname, "a");
	  fprintf (logfile_a, "        :hw_reaper module skipped.\n");
	  fclose (logfile_a);
	  done = TRUE;
	}
      else if (ch == 'Y' || ch == 'y')
	{
	  printf ("Starting hardware inventory...");
	  gettime ();
	  logfile_a = fopen (logname, "a");
	  fprintf (logfile_a, "        :hw_reaper module started.\n");
	  fclose (logfile_a);

	  /* List hardware inventory in plain text */
	  hw_r ();

	  printf ("done.\n\n");
	  gettime ();
	  logfile_a = fopen (logname, "a");
	  fprintf (logfile_a, "        :hw_reaper module complete.\n");
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

/* Call to lshw */
int
hw_r ()
{
  char allhw[PATH_MAX];

  snprintf (allhw, sizeof (allhw), "/usr/bin/sudo /usr/bin/lshw > \
            %s/hardware.txt", outputdir);
  system (allhw);

  return (0);
}
