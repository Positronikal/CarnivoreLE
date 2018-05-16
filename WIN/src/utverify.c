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
#include <stdlib.h>

extern FILE *logfile_a;
extern char logname[PATH_MAX];
extern char outputdir[PATH_MAX];

/* Hash verification of system utilities using hashdeep */
int
utverify ()
{
  char utaudit[PATH_MAX];

  printf ("\nVerifying integrity of system utilities... ");
  gettime ();
  logfile_a = fopen (logname, "a");
  fprintf (logfile_a, "        :Utility audit started.\n");
  fclose (logfile_a);

  snprintf (utaudit, sizeof (utaudit), ".\\thirdparty\\hashdeep64.exe -k \
            .\\config\\uthashes-win.txt -f .\\config\\utlist-win.txt -aEvvv > \
            %s\\utaudit.txt", outputdir);
  system (utaudit);

  logfile_a = fopen (logname, "a");
  fprintf (logfile_a, "        ... Utility audit finished.\n");
  fclose (logfile_a);

  printf ("done.\n");
  printf ("Make note of any utilities that failed the audit.\n");

  return (0);
}
