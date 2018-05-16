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
#include <getopt.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../include/carnivore.h"
#include <sys/unistd.h>
#include <time.h>

/* Global variables */
char outputdir[PATH_MAX];
char logname[PATH_MAX];
FILE *logfile;
FILE *logfile_a;

/* Main function */
int
main (int argc, char *argv[])
{
  /* Check command line options */
  while (1)
    {
      int option_index = 0;
      static struct option long_options[] = {
	{"version", no_argument, 0, 'v'},
	{"help", no_argument, 0, 'h'},
	{0, 0, 0, 0}
      };

      /* int getopt_long (int argc, char * const argv[],
         const char *optstring,
         const struct option *longopts,
         int *longindex); */
      int c = getopt_long (argc, argv, "vh", long_options, &option_index);
      if (c == -1)
	break;

      switch (c)
	{
	case 'v':
	  version ();
	  exit (0);

	case 'h':
	  usage ();
	  exit (0);

	default:
	  break;
	}
    }

  /* Welcome message */
  printf ("\n*** CarnivoreLE (Live Edition) ***\n");
  printf ("CAUTION: You are running this application on a live computer!\n");
  printf ("Leave all networks and peripheral devices connected.\n");
  printf ("Initializing operations, please standby...\n\n");

  /* Find EVIDENCE volume, create datastore directory */
  DIR *dhandle;

  char drvltr[2];
  char prefix[32];
  char evdrv[24];

  if (drvltr == NULL)
    {
      printf ("Not enough memory available.\n");
      return (1);
    }

  printf ("Please enter the drive letter of the EVIDENCE drive (Ex. F): \n");
  fgets (drvltr, 2, stdin);

  snprintf (evdrv, sizeof (evdrv), "%s:", drvltr);

  snprintf (prefix, sizeof (prefix), "%s:\\CARN_WIN_", drvltr);

  dhandle = opendir (evdrv);
  if (dhandle == NULL)
    {
      printf ("EVIDENCE volume NOT FOUND! Exiting...\n");
      return (1);
    }

  time_t serialt;
  time (&serialt);

  snprintf (outputdir, sizeof (outputdir), "%s_%d", prefix, (int) serialt);

  struct stat st = { 0 };
  if (stat (outputdir, &st) == -1)
    mkdir (outputdir);

  printf ("...datastore created on EVIDENCE volume\n\n");

  closedir (dhandle);

  /* Create & initialize log */
  snprintf (logname, sizeof (logname), "%s\\history.log", outputdir);

  logfile = fopen (logname, "w");
  if (!logfile)
    {
      printf ("Error creating history log!\n");
      return (1);
    }

  fprintf (logfile, "%s\nALL TIMES ARE LOCAL\n\n", PROGNAME);
  fclose (logfile);

  gettime ();
  logfile_a = fopen (logname, "a");
  fprintf (logfile_a, "        :Carnivore LE initiated, logging started.\n");
  fclose (logfile_a);

  /* Image RAM */
  ramcap ();

  /* Add case data = agent, number, title, notes (1024B max) */
  casedata ();

  /* Verify integrity of system utilities to be called */
  utverify ();

  /* Capture open network connections */
  net_reaper ();

  /* Capture open files with IP addresses */
  ofip_reaper ();

  /* Capture logged in users */
  cu_reaper ();

  printf ("***NETWORK CONNECTIONS CAN BE DISCONNECTED NOW***\n\n");
  gettime ();
  logfile_a = fopen (logname, "a");
  fprintf (logfile_a, "        :Networks can be disconnected now.\n");
  fclose (logfile_a);

  /* Detail OS information */
  os_reaper ();

  /* List all running processes */
  rp_reaper ();

  /* List all open files */
  of_reaper ();

  /* Detail network configuration */
  nc_reaper ();

  /* List all user accounts/UIDs */
  us_reaper ();

  /* List hardware inventory in plain text */
  sys_reaper ();

  /* List software inventory in plain text */
  sw_reaper ();

  // Encryption checks go here

  /* Image users home directory */
  homecap ();

  /* Image logs directory */
  logscap ();

  /* Time verification */
  vertime ();

  /* Close and exit */
  printf ("\nAll operations have completed. A complete shutdown of the \n");
  printf ("computer system is recommended. Continue processing after \n");
  printf ("controlled booting using Carnivore PM.\n\n");

  gettime ();
  logfile_a = fopen (logname, "a");
  fprintf (logfile_a, "        :Operations complete... exiting.\n\n");
  fclose (logfile_a);

  return (0);
}

/* Option -v, --version */
void
version (void)
{
  printf ("CarnivoreLE %s\n", PROGVERS);
}

/* Option -h, --help */
void
usage (void)
{
  printf ("USAGE:\n");
  printf ("Run without arguments for normal execution.\n");
  printf ("$ carnivore [-v, --version]\n\t-displays program version and \
exits.\n");
  printf ("$ carnivore [-h, --help]\n\t-displays this help and exits.\n");
  printf ("On scene, run:\n");
  printf ("\"$ man ./docs/carnivore.1\" from a terminal\n");
  printf ("or see the manual under docs/ on a controlled computer.\n");
}
