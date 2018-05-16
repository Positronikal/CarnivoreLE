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
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "../include/carnivore.h"

extern FILE *logfile_a;
extern char logname[PATH_MAX];

/* Compare system time with externally verified time */
int
vertime ()
{
  char *vtime = malloc (9);

  printf
    ("\nCarnivore checks system time directly. To calculate the error\n");
  printf ("offset of this machine, verify the time via a reliable source,\n");
  printf ("such as time.nist.gov, and enter it next. The faster you're\n");
  printf
    ("able to enter the last time digit and press \"ENTER\", the more\n");
  printf ("accurate this comparison will be. Both your timestamp and that\n");
  printf
    ("of Carnivore will be recorded in the history log. Enter time in\n");
  printf ("24-hour format: HH:MM:SS (ex: 16:32:45)\n\n");
  printf ("Enter time when ready: ");

  fgets (vtime, 9, stdin);

  if ((strlen (vtime) > 0) && (vtime[strlen (vtime) - 1] == '\n'))
    vtime[strlen (vtime) - 1] = '\0';

  gettime ();
  logfile_a = fopen (logname, "a");
  fprintf (logfile_a, "        :VERIFIED TIME (HH:MM:SS): %s\n", vtime);
  fclose (logfile_a);

  free (vtime);

  return (0);
}
