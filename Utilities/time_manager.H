/*
  This file contains a class definition for managing time and difference
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
# ifndef TIME_MANAGER_H
# define TIME_MANAGER_H

# include <singleton.H>

# define DELTA_TIME (Time_Manager::get_instance().delta_time())

class Time_Manager_Data
{
  unsigned long long prev_time;
  unsigned long long dt;

protected:
  Time_Manager_Data();

public:
  void init();

  void reset();

  const unsigned long long & delta_time();

  const unsigned long long dt_msec() const;

  const unsigned long long dt_sec() const;

  const unsigned long long dt_min() const;

  const unsigned long long dt_hour() const;
};

using Time_Manager = Singleton<Time_Manager_Data>;

# endif // TIME_MANAGER_H

