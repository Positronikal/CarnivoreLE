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

#ifndef CARNIVORE_H_INCLUDED
#define CARNIVORE_H_INCLUDED

/* Constants */
#define PROGNAME "CarnivoreLE for Macintosh"
#define PROGVERS "0.1.17"
#define FALSE 0
#define TRUE !FALSE

/* Function declarations */
void version (void);
void usage (void);
int gettime (void);
int ramcap (void);
int utverify (void);
int casedata (void);
int net_reaper (void);
int ofip_reaper (void);
int lu_reaper (void);
int rp_reaper (void);
int of_reaper (void);
int nc_reaper (void);
int us_reaper (void);
int sys_reaper (void);
int homecap (void);
int logscap (void);
int vertime (void);

#endif // CARNIVORE_H_INCLUDED
