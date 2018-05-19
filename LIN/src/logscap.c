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

#include <stdio.h>
#include <limits.h>
#include "../include/carnivore.h"
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
  char imglogs[PATH_MAX];

  done = FALSE;
  while (!done)
    {
      printf ("Image logs directory? [y/n]\n");
      ch = getchar ();

      if (ch == 'N' || ch == 'n')
	      {
	        printf ("Skipping logs directory imaging...\n\n");
	        gettime ();
	        logfile_a = fopen (logname, "a");
	        fprintf (logfile_a, "        :logscap imaging skipped.\n");
	        fclose (logfile_a);
	        done = TRUE;
	      }
      else if (ch == 'Y' || ch == 'y')
	      {
	        printf ("Starting logs directory imaging ");
	        printf ("(may take several minutes!)...\n");
	        printf ("Files that are already in use may be locked and produce \
warnings.\n\n");
	        gettime ();
	        logfile_a = fopen (logname, "a");
	        fprintf (logfile_a, "        :logscap imaging started.\n");
	        fclose (logfile_a);

	        /* Image logs directory */
	        snprintf (imglogs, sizeof (imglogs),
                   "/usr/bin/sudo /usr/bin/find /var/log -type f | \
                   ./thirdparty/linpmem -i @ -o %s/img_logical.aff4 \
                   -c snappy", outputdir);
          system (imglogs);

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
