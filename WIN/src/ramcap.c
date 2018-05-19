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
#include "../include/carnivore.h"
#include <stdio.h>
#include <stdlib.h>

extern FILE *logfile_a;
extern char logname[PATH_MAX];
extern char outputdir[PATH_MAX];

/* RAM forensic logical imager using AFF4 */
int
ramcap ()
{
  int done;
  int ch;
  char ramname[PATH_MAX];

  done = FALSE;
  while (!done)
    {
      printf ("Image RAM? [y/n]\n");
      ch = getchar ();

      if (ch == 'N' || ch == 'n')
        {
          printf ("Skipping RAM imaging...\n\n");
          gettime ();
          logfile_a = fopen (logname, "a");
          fprintf (logfile_a, "        :RAM capture skipped.\n");
          fclose (logfile_a);
          done = TRUE;
        }
      else if (ch == 'Y' || ch == 'y')
        {
          printf ("Starting RAM imaging ");
          printf ("(may take several minutes!)...\n");
          printf ("Files that are already in use may be locked and produce \
warnings.\n\n");
          gettime ();
          logfile_a = fopen (logname, "a");
          fprintf (logfile_a, "        :RAM imaging started.\n");
          fclose (logfile_a);

          /* Ram capture */
          snprintf (ramname, sizeof (ramname), ".\\thirdparty\\winpmem.exe \
                    -o %s\\img_logical.aff4 -c snappy", outputdir);
          system (ramname);

          printf ("...done.\n\n");
          gettime ();
          logfile_a = fopen (logname, "a");
          fprintf (logfile_a, "        :RAM imaging complete.\n");
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
