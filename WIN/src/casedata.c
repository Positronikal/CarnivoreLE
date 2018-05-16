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

extern FILE *logfile_a;
extern char logname[PATH_MAX];

/* Log basic case data */
int
casedata ()
{
  char *ename = malloc (32);
  char *agency = malloc (64);
  char *num = malloc (32);
  char *sname = malloc (32);

  /* Examiner's name */
  if (ename == NULL)
    {
      printf ("Not enough memory available.\n");
      return (1);
    }
  printf ("Examiner's Name:\n");
  fgets (ename, 32, stdin);
  if ((strlen (ename) > 0) && (ename[strlen (ename) - 1] == '\n'))
    ename[strlen (ename) - 1] = '\0';
  logfile_a = fopen (logname, "a");
  fprintf (logfile_a, "EXAMINER: %s\n", ename);
  free (ename);

  /* Examiner's agency */
  if (agency == NULL)
    {
      printf ("Not enough memory available.\n");
      return (1);
    }
  printf ("Agency:\n");
  fgets (agency, 64, stdin);
  if ((strlen (agency) > 0) && (agency[strlen (agency) - 1] == '\n'))
    agency[strlen (agency) - 1] = '\0';
  fprintf (logfile_a, "AGENCY: %s\n", agency);
  free (agency);

  /* Case number */
  if (num == NULL)
    {
      printf ("Not enough memory available.\n");
      return (1);
    }
  printf ("Case Number:\n");
  fgets (num, 32, stdin);
  if ((strlen (num) > 0) && (num[strlen (num) - 1] == '\n'))
    num[strlen (num) - 1] = '\0';
  fprintf (logfile_a, "CASE NUMBER: %s\n", num);
  free (num);

  /* Subject's name */
  if (sname == NULL)
    {
      printf ("Not enough memory available.\n");
      return (1);
    }
  printf ("Subject's Name:\n");
  fgets (sname, 32, stdin);
  if ((strlen (sname) > 0) && (sname[strlen (sname) - 1] == '\n'))
    sname[strlen (sname) - 1] = '\0';
  fprintf (logfile_a, "SUBJECT: %s\n", sname);
  free (sname);

  fclose (logfile_a);

  return (0);
}
