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

extern FILE *logfile_a;
extern char logname[PATH_MAX];
extern char outputdir[PATH_MAX];

/* Logs directory forensic logical imager using AFF4 */
int
logscap ()
{
  int done;
  int ch;
  char caplogs1[PATH_MAX];
  char caplogs2[PATH_MAX];
  char caplogs3[PATH_MAX];

  done = FALSE;
  while (!done)
    {
      printf ("Capture system logs /tar, log/? [y/n]\n");
      ch = getchar ();

      if (ch == 'N' || ch == 'n')
	      {
	        printf ("Skipping system logs capture...\n\n");
	        gettime ();
	        logfile_a = fopen (logname, "a");
	        fprintf (logfile_a, "        :logscap capture skipped.\n");
	        fclose (logfile_a);
	        done = TRUE;
	      }
      else if (ch == 'Y' || ch == 'y')
	      {
	        printf ("Starting system logs capture ");
	        printf ("(may take several minutes!)...\n");
	        printf ("Files that are missing or in use may be locked and ");
	        printf ("produce warnings. Capture uses /log/ which is only ");
	        printf ("present on MacOS 10.12 and later. Running Carnivore ");
	        printf ("on earlier systems will produce warnings. The two main ");
	        printf ("logs locations will still be captured.\n\n");
	        gettime ();
	        logfile_a = fopen (logname, "a");
	        fprintf (logfile_a, "        :logscap capture started.\n");
	        fclose (logfile_a);

	        /* Capture system logs */
	        snprintf (caplogs1, sizeof (caplogs1), "/usr/bin/sudo /usr/bin/tar \
                   -jcvf %s/logscap_pvl.tar.bz2 /private/var/log", outputdir);
	        system (caplogs1);
	        snprintf (caplogs2, sizeof (caplogs2), "/usr/bin/sudo /usr/bin/tar \
                   -jcvf %s/logscap_ll.tar.bz2 /library/logs", outputdir);
	        system (caplogs2);
	        /* MacOS 10.12 & later */
	        printf ("Capture using /log/ is only present on MacOS 10.12 and later. This module may produce warnings ");
	        snprintf (caplogs3, sizeof (caplogs3), "/usr/bin/sudo /usr/bin/log \
                   collect --output %s", outputdir);
	        system (caplogs3);

	        printf ("...done.\n\n");
	        gettime ();
	        logfile_a = fopen (logname, "a");
	        fprintf (logfile_a, "        :logscap imaging complete.\n");
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
