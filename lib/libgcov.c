/* Routines required for instrumenting a program.  */
/* Compile this one with gcc.  */
/* Copyright (C) 1989, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999,
   2000, 2001, 2002, 2003  Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2, or (at your option) any later
version.

In addition to the permissions in the GNU General Public License, the
Free Software Foundation gives you unlimited permission to link the
compiled version of this file into combinations with other programs,
and to distribute those combinations without any restriction coming
from the use of this file.  (The General Public License restrictions
do apply in other respects; for example, they cover modification of
the file, and distribution when not linked into a combine
executable.)

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.  */

#define GCOV_LINKAGE /* nothing */

#include "gcov-io.h"

/* Chain of per-object gcov structures.  */
struct gcov_info *gcov_list;

/* A program checksum allows us to distinguish program data for an
   object file included in multiple programs.  */
gcov_unsigned_t gcov_crc32;

/* The profile merging function that just adds the counters.  It is given
   an array COUNTERS of N_COUNTERS old counters and it reads the same number
   of counters from the gcov file.  */
void
__gcov_merge_add (gcov_type *counters, unsigned n_counters)
{
  for (; n_counters; counters++, n_counters--)
    *counters += gcov_read_counter ();
}
/* The profile merging function for choosing the most common value.
   It is given an array COUNTERS of N_COUNTERS old counters and it
   reads the same number of counters from the gcov file.  The counters
   are split into 3-tuples where the members of the tuple have
   meanings:
   
   -- the stored candidate on the most common value of the measured entity
   -- counter
   -- total number of evaluations of the value  */
void
__gcov_merge_single (gcov_type *counters, unsigned n_counters)
{
  unsigned i, n_measures;
  gcov_type value, counter, all;

  GCOV_CHECK (!(n_counters % 3));
  n_measures = n_counters / 3;
  for (i = 0; i < n_measures; i++, counters += 3)
    {
      value = gcov_read_counter ();
      counter = gcov_read_counter ();
      all = gcov_read_counter ();

      if (counters[0] == value)
	counters[1] += counter;
      else if (counter > counters[1])
	{
	  counters[0] = value;
	  counters[1] = counter - counters[1];
	}
      else
	counters[1] -= counter;
      counters[2] += all;
    }
}

/* The profile merging function for choosing the most common
   difference between two consecutive evaluations of the value.  It is
   given an array COUNTERS of N_COUNTERS old counters and it reads the
   same number of counters from the gcov file.  The counters are split
   into 4-tuples where the members of the tuple have meanings:
   
   -- the last value of the measured entity
   -- the stored candidate on the most common difference
   -- counter
   -- total number of evaluations of the value  */

void
__gcov_merge_delta (gcov_type *counters, unsigned n_counters)
{
  unsigned i, n_measures;
  gcov_type last, value, counter, all;

  GCOV_CHECK (!(n_counters % 4));
  n_measures = n_counters / 4;
  for (i = 0; i < n_measures; i++, counters += 4)
    {
      last = gcov_read_counter ();
      value = gcov_read_counter ();
      counter = gcov_read_counter ();
      all = gcov_read_counter ();

      if (counters[1] == value)
	counters[2] += counter;
      else if (counter > counters[2])
	{
	  counters[1] = value;
	  counters[2] = counter - counters[2];
	}
      else
	counters[2] -= counter;
      counters[3] += all;
    }
}
