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

int ofip_r (void);

extern FILE *logfile_a;
extern char logname[PATH_MAX];
extern char outputdir[PATH_MAX];

/* Capture open file data with IP addresses assigned using netstat */
int
ofip_reaper ()
{
  int done;
  int ch;

  done = FALSE;
  while (!done)
    {
      printf ("\nCapture data on all open files assigned IP addresses? \
/NETSTAT.EXE/ [y/n]\n");
      ch = getchar ();

      if (ch == 'N' || ch == 'n')
        {
          printf ("Skipping all open files assigned IP addresses...\n\n");
          gettime ();
          logfile_a = fopen (logname, "a");
          fprintf (logfile_a, "        :ofip_reaper module skipped.\n");
          fclose (logfile_a);
          done = TRUE;
        }
      else if (ch == 'Y' || ch == 'y')
        {
          printf ("Starting all open files assigned IP addresses data \
capture...");
          gettime ();
          logfile_a = fopen (logname, "a");
          fprintf (logfile_a, "        :ofip_reaper module started.\n");
          fclose (logfile_a);

          /* List all open files w/ IP addresses */
          ofip_r ();

          printf ("done.\n");
          gettime ();
          logfile_a = fopen (logname, "a");
          fprintf (logfile_a, "        :ofip_reaper module complete.\n");
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

/* Call to netstat */
int
ofip_r ()
{
  char openfiles[PATH_MAX];

  snprintf (openfiles, sizeof (openfiles),
            "C:\\Windows\\System32\\NETSTAT.EXE -b > %s\\openfiles_ip.txt",
            outputdir);
  system (openfiles);

  return (0);
}
