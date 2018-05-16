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

#include <time.h>
#include <limits.h>
#include <stdio.h>
#include "../include/carnivore.h"

extern FILE *logfile_a;
extern char logname[PATH_MAX];

/* Get current system time & log */
int
gettime ()
{
  time_t now;

  time (&now);

  logfile_a = fopen (logname, "a");
  fprintf (logfile_a, "%s", ctime (&now));
  fclose (logfile_a);

  return (0);
}
