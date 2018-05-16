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
#include "../include/carnivore.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

extern FILE *logfile_a;
extern char logname[PATH_MAX];
extern char outputdir[PATH_MAX];

/* Logs directory capture using wevtutil */
int
logscap ()
{
  int done;
  int ch;
  char logsoutdir[PATH_MAX];
  char logsget1[PATH_MAX];
  char logsget2[PATH_MAX];
  char logsget3[PATH_MAX];

  done = FALSE;
  while (!done)
    {
      printf ("Capture event logs? [y/n]\n");
      ch = getchar ();

      if (ch == 'N' || ch == 'n')
	{
	  printf ("Skipping event logs capture...\n\n");
	  gettime ();
	  logfile_a = fopen (logname, "a");
	  fprintf (logfile_a, "        :logs capture skipped.\n");
	  fclose (logfile_a);
	  done = TRUE;
	}
      else if (ch == 'Y' || ch == 'y')
	{
	  printf ("Starting event logs capture ");
	  gettime ();
	  logfile_a = fopen (logname, "a");
	  fprintf (logfile_a, "        :logsget capture started.\n");
	  fclose (logfile_a);

	  /* Create Logs directory on datastore */
	  DIR *dhandle;
	  dhandle = opendir (outputdir);
	  snprintf (logsoutdir, sizeof (logsoutdir), "%s\\EventLogs",
		    outputdir);
	  mkdir (logsoutdir);
	  closedir (dhandle);

	  /* Event logs capture */
	  snprintf (logsget1, sizeof (logsget1),
		    "C:\\Windows\\System32\\wevtutil.exe epl Application \
                    \"%s\\Application.evtx\"", logsoutdir);
	  system (logsget1);
	  snprintf (logsget2, sizeof (logsget2),
		    "C:\\Windows\\System32\\wevtutil.exe epl Security \
                    \"%s\\Security.evtx\"", logsoutdir);
	  system (logsget2);
	  snprintf (logsget3, sizeof (logsget3),
		    "C:\\Windows\\System32\\wevtutil.exe epl System \
                    \"%s\\System.evtx\"", logsoutdir);
	  system (logsget3);

	  printf ("...done.\n\n");
	  gettime ();
	  logfile_a = fopen (logname, "a");
	  fprintf (logfile_a, "        :logsget capture complete.\n");
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
