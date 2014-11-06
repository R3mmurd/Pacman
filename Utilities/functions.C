/*
  This file contains implementation of some mathematical functions.
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
# include <functions.H>

real compute_angle_between(const Vector_2D & p1, const Vector_2D & p2)
{
  if (p1.get_x() == p2.get_x())
    if (p1.get_y() > p2.get_y())
      return RADIANS_2_DEGREES(A_3_PI_2);
    else if (p1.get_y() < p2.get_y())
      return RADIANS_2_DEGREES(A_PI_2);
    else
      return A_ZERO;

  real m = real(p2.get_y() - p1.get_y()) / real(p2.get_x() - p1.get_x());

  real angle = RADIANS_2_DEGREES(atan(m));

  if (p1.get_x() > p2.get_x())
    return A_PI_DEGREES + angle;

  return angle;
}

