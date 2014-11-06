/*
  This file contains an class implementation for managing time and difference
  between two time instants.
  Copyright (C) 2014 by Alejandro J. Mujica

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  Any user request of this software, write to 

  Alejandro Mujica

  aledrums@gmail.com
*/
# include <sys/time.h>

# include <time_manager.H>

Time_Manager_Data::Time_Manager_Data()
  : prev_time(0)
{
  // Empty
}

void Time_Manager_Data::reset()
{
  prev_time = 0;
}

unsigned long long Time_Manager_Data::delta_time()
{
  struct timeval now;

  gettimeofday(&now, 0);

  curr_time = now.tv_sec * 1000 + now.tv_usec / 1000;

  unsigned long long dt = 0;

  if (prev_time != 0)
    dt = curr_time - prev_time;

  prev_time = curr_time;

  return dt;
}

