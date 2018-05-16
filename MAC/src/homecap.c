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
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

extern FILE *logfile_a;
extern char logname[PATH_MAX];
extern char outputdir[PATH_MAX];
char *dirpath;
char imghome[PATH_MAX];

/* Home directory forensic logical imager using AFF4 */
int
homecap ()
{
  int done;
  int ch;

  done = FALSE;
  while (!done)
    {
      printf ("Image user's home directory? [y/n]\n");
      ch = getchar ();

      if (ch == 'N' || ch == 'n')
	{
	  printf ("Skipping home directory imaging...\n\n");
	  gettime ();
	  logfile_a = fopen (logname, "a");
	  fprintf (logfile_a, "        :homedir imaging skipped.\n");
	  fclose (logfile_a);
	  done = TRUE;
	}
      else if (ch == 'Y' || ch == 'y')
	{
	  printf ("Starting home directory imaging ");
	  printf ("(may take several minutes!)...\n");
	  printf ("Files that are already in use may be locked and produce \
warnings.\n\n");
	  gettime ();
	  logfile_a = fopen (logname, "a");
	  fprintf (logfile_a, "        :homedir imaging started.\n");
	  fclose (logfile_a);

	  /* Get user home directory */
	  if ((dirpath = getenv ("HOME")) == NULL)
	    dirpath = getpwuid (getuid ())->pw_dir;

	  /* Image home directory */
	  snprintf (imghome, sizeof (imghome), "/usr/bin/sudo /bin/sh \
                    -c \'/usr/bin/find %s -type f | \
                    ./thirdparty/osxpmem.app/osxpmem -i @ \
                    -o %s/img_logical.aff4 -c snappy\'", dirpath, outputdir);
	  system (imghome);

	  printf ("...done.\n\n");
	  gettime ();
	  logfile_a = fopen (logname, "a");
	  fprintf (logfile_a, "        :homedir imaging complete.\n");
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
