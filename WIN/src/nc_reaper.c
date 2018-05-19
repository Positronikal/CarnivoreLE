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

int nc_r (void);

extern FILE *logfile_a;
extern char logname[PATH_MAX];
extern char outputdir[PATH_MAX];

/* Capture network configuration using ifconfig */
int
nc_reaper ()
{
  int done;
  int ch;

  done = FALSE;
  while (!done)
    {
      printf ("Capture detailed network configuration data? /ipconfig.exe/ \
[y/n]\n");
      ch = getchar ();

      if (ch == 'N' || ch == 'n')
        {
          printf ("Skipping detailed network configuration data...\n\n");
          gettime ();
          logfile_a = fopen (logname, "a");
          fprintf (logfile_a, "        :nc_reaper module skipped.\n");
          fclose (logfile_a);
          done = TRUE;
        }
      else if (ch == 'Y' || ch == 'y')
        {
          printf ("Starting detailed network configuration data capture...");
          gettime ();
          logfile_a = fopen (logname, "a");
          fprintf (logfile_a, "        :nc_reaper module started.\n");
          fclose (logfile_a);

          /* Detail network configuration */
          nc_r ();

          printf ("done.\n\n");
          gettime ();
          logfile_a = fopen (logname, "a");
          fprintf (logfile_a, "        :nc_reaper module complete.\n");
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

/* Call to ipconfig */
int
nc_r ()
{
  char netconf[PATH_MAX];

  snprintf (netconf, sizeof (netconf), "C:\\Windows\\System32\\ipconfig.exe \
            /all > %s\\netconfig.txt", outputdir);
  system (netconf);

  return (0);
}
