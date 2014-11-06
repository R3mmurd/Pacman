/*
  This file contains macros to define some mathematical values and some data
  types.
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
# ifndef DEF_H
# define DEF_H

# define A_ZERO               0.0
# define A_PI_2               M_PI_2
# define A_3_PI_2             (3 * A_PI_2)
# define A_PI_DEGREES         180.0
# define A_2_PI_DEGREES       A_PI_DEGREES * 2.0
# define A_PI_2_DEGREES       A_PI_DEGREES / 2.0
# define RADIANS_2_DEGREES(t) (((t) * A_PI_DEGREES) / M_PI)
# define DEGREES_2_RADIANS(t) (((t) * M_PI) / A_PI_DEGREES)

typedef double real;

# endif /* DEF_H */

