/*
  This file contains a definition of mathematical vector.
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
# ifndef VECTOR_2D_H
# define VECTOR_2D_H

# include <cmath>
# include <sstream>
# include <def.H>

class Vector_2D
{
  real x;

  real y;

public:
  Vector_2D();

  Vector_2D(const real & _x, const real & _y);

  const real & get_x() const;

  void set_x(const real & _x);

  const real & get_y() const;

  void set_y(const real & _y);

  void clear();

  real square_magnitude() const;

  real magnitude() const;

  void normalize();

  bool is_opposite(const Vector_2D & vector) const;

  void add_scaled_vector(const Vector_2D & vector, const real & scale);

  real dot_product(const Vector_2D & vector) const;

  real scalar_product(const Vector_2D & vector) const;

  Vector_2D component_product(const Vector_2D & vector) const;

  Vector_2D operator * (const real & scalar) const;

  friend Vector_2D operator * (const real & scalar, const Vector_2D & vector);

  real operator * (const Vector_2D & vector) const;

  void operator *= (const real & scalar);

  Vector_2D operator + (const Vector_2D & vector) const;

  void operator += (const Vector_2D & vector);

  Vector_2D operator - (const Vector_2D & vector) const;

  void operator -= (const Vector_2D & vector);

  bool operator == (const Vector_2D & vector) const;

  bool operator != (const Vector_2D & vector) const;

  std::string to_string() const;

  static void make_orthonormal_basis(Vector_2D & a, Vector_2D & b);
};

# endif // VECTOR_2D_H

