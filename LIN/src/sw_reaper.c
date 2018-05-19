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
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include "../include/carnivore.h"

int sw_r (void);

extern FILE *logfile_a;
extern char logname[PATH_MAX];
extern char outputdir[PATH_MAX];

/* Capture software inventory using dpkg or rpm */
int
sw_reaper ()
{
  int done;
  int ch;

  done = FALSE;
  while (!done)
    {
      printf ("Capture software inventory? /dpkg, rpm/ [y/n]\n");
      ch = getchar ();

      if (ch == 'N' || ch == 'n')
        {
          printf ("Skipping software inventory...\n\n");
          gettime ();
          logfile_a = fopen (logname, "a");
          fprintf (logfile_a, "        :sw_reaper module skipped.\n");
          fclose (logfile_a);
          done = TRUE;
        }
      else if (ch == 'Y' || ch == 'y')
        {
          printf ("Starting software inventory...");
          gettime ();
          logfile_a = fopen (logname, "a");
          fprintf (logfile_a, "        :sw_reaper module started.\n");
          fclose (logfile_a);

          /* List software inventory in plain text */
          sw_r ();

          printf ("done.\n\n");
          gettime ();
          logfile_a = fopen (logname, "a");
          fprintf (logfile_a, "        :sw_reaper module complete.\n");
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

/* Call to either dpkg or rpm */
int
sw_r ()
{
  char allsw[PATH_MAX];

  DIR *dir;
  struct dirent *entry;

  dir = opendir ("/usr/bin");
  if (dir == NULL)
    {
      printf ("/usr/bin NOT FOUND! Exiting...\n");
      return (1);
    }

  errno = 0;
  while ((entry = readdir (dir)) != NULL)
    {
      if (strcmp (entry->d_name, "dpkg") == 0)
        {
          snprintf (allsw, sizeof (allsw), "/usr/bin/dpkg -l > \
                    %s/software.txt", outputdir);
          system (allsw);
        }
      else if (strcmp (entry->d_name, "rpm") == 0)
        {
          snprintf (allsw, sizeof (allsw),
                    "usr/bin/rpm -qa > %s/software.txt", outputdir);
          system (allsw);
        }
    }

  if (errno && !entry)
    {
      perror ("readdir");
      printf ("***Software Reaper skipped: DEB and RPM systems only***\n");
      logfile_a = fopen (logname, "a");
      fprintf (logfile_a,
	       "***sw_reaper skipped... DEB and RPM systems only***\n");
      fclose (logfile_a);
    }

  closedir (dir);

  return (0);
}
