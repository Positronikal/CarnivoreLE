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
char imglogs[PATH_MAX];

/* Logs directory forensic logical imager using AFF4 */
int
logscap ()
{
  int done;
  int ch;
  char logsdir1[PATH_MAX];
  char logsdir2[PATH_MAX];

  done = FALSE;
  while (!done)
    {
      printf ("Image logs directories? [y/n]\n");
      ch = getchar ();

      if (ch == 'N' || ch == 'n')
	{
	  printf ("Skipping logs directories imaging...\n\n");
	  gettime ();
	  logfile_a = fopen (logname, "a");
	  fprintf (logfile_a, "        :logsdirs imaging skipped.\n");
	  fclose (logfile_a);
	  done = TRUE;
	}
      else if (ch == 'Y' || ch == 'y')
	{
	  printf ("Starting logs directories imaging ");
	  printf ("(may take several minutes!)...\n");
	  printf ("Files that are already in use may be locked and produce \
warnings.\n\n");
	  gettime ();
	  logfile_a = fopen (logname, "a");
	  fprintf (logfile_a, "        :logsdirs imaging started.\n");
	  fclose (logfile_a);

	  /* Image logs directory */
	  snprintf (logsdir1, sizeof (logsdir1), "/usr/bin/sudo /bin/sh \
                    -c \'/usr/bin/find /private/var/log -type f | \
                    ./thirdparty/osxpmem.app/osxpmem -i @ \
                    -o %s/img_logical.aff4 -c snappy\'", outputdir);
	  system (logsdir1);
	  snprintf (logsdir2, sizeof (logsdir2), "/usr/bin/sudo /bin/sh \
                    -c \'/usr/bin/find /library/logs -type f | \
                    ./thirdparty/osxpmem.app/osxpmem -i @ \
                    -o %s/img_logical.aff4 -c snappy\'", outputdir);
	  system (logsdir2);

	  printf ("...done.\n\n");
	  gettime ();
	  logfile_a = fopen (logname, "a");
	  fprintf (logfile_a, "        :logsdirs imaging complete.\n");
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
