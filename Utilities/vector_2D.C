/*
  This file contains an implementation of mathematical vector.
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
# include <vector_2D.H>

Vector_2D::Vector_2D()
  : x(0), y(0)
{
  // Empty
}

Vector_2D::Vector_2D(const real & _x, const real & _y)
  : x(_x), y(_y)
{
  // Empty
}

const real & Vector_2D::get_x() const
{
  return x;
}

void Vector_2D::set_x(const real & _x)
{
  x = _x;
}

const real & Vector_2D::get_y() const
{
  return y;
}

void Vector_2D::set_y(const real & _y)
{
  y = _y;
}

void Vector_2D::clear()
{
  x = y = 0;
}

real Vector_2D::square_magnitude() const
{
  return x * x + y * y;
}

real Vector_2D::magnitude() const
{
  return std::sqrt(square_magnitude());
}

void Vector_2D::normalize()
{
  real length = magnitude();

  if (length == 0)
    return;

  (*this) *= 1 / length;
}

bool Vector_2D::is_opposite(const Vector_2D & vector) const
{
  Vector_2D a = *this;
  Vector_2D b = vector;

  a.normalize();
  b.normalize();

  return a.x == -b.x and a.y == -b.y;
}

void Vector_2D::add_scaled_vector(const Vector_2D & vector, const real & scale)
{
  x += vector.x * scale;
  y += vector.y * scale;
}

Vector_2D Vector_2D::component_product(const Vector_2D & vector) const
{
  Vector_2D ret_val;

  ret_val.x = x * vector.x;
  ret_val.y = y * vector.y;

  return ret_val;
}

real Vector_2D::dot_product(const Vector_2D & vector) const
{
  return x * vector.x + y * vector.y;
}

real Vector_2D::scalar_product(const Vector_2D & vector) const
{
  return dot_product(vector);
}

Vector_2D Vector_2D::operator * (const real & scalar) const
{
  Vector_2D ret_val;

  ret_val.x = x * scalar;
  ret_val.y = y * scalar;

  return ret_val;
}

Vector_2D operator * (const real & scalar, const Vector_2D & vector)
{
  Vector_2D ret_val;

  ret_val.x = vector.x * scalar;
  ret_val.y = vector.y * scalar;

  return ret_val;
}

real Vector_2D::operator * (const Vector_2D & vector) const
{
  return dot_product(vector);
}

void Vector_2D::operator *= (const real & scalar)
{
  x *= scalar;
  y *= scalar;
}

Vector_2D Vector_2D::operator + (const Vector_2D & vector) const
{
  Vector_2D ret_val;

  ret_val.x = x + vector.x;
  ret_val.y = y + vector.y;

  return ret_val;
}

void Vector_2D::operator += (const Vector_2D & vector)
{
  x += vector.x;
  y += vector.y;
}

Vector_2D Vector_2D::operator - (const Vector_2D & vector) const
{
  Vector_2D ret_val;

  ret_val.x = x - vector.x;
  ret_val.y = y - vector.y;

  return ret_val;
}

void Vector_2D::operator -= (const Vector_2D & vector)
{
  x -= vector.x;
  y -= vector.y;
}

bool Vector_2D::operator == (const Vector_2D & vector) const
{
  return x == vector.x and y == vector.y;
}

bool Vector_2D::operator != (const Vector_2D & vector) const
{
  return not(*this == vector);
}

std::string Vector_2D::to_string() const
{
  std::stringstream sstr;

  sstr << "(" << x << "," << y << ")";

  return sstr.str();
}

void Vector_2D::make_orthonormal_basis(Vector_2D & a, Vector_2D & b)
{
  a.normalize();

  b.set_y(-1 * a.get_x());
  b.set_x(a.get_y());
}

