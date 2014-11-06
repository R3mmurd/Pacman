/*
  This file is part of Pacman game.
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
# ifndef ELEMENT_H
# define ELEMENT_H

# include <vector_2D.H>

class Element
{
  real      inverse_mass;
  Vector_2D position;
  Vector_2D velocity;
  Vector_2D acceleration;
  Vector_2D force_accumulator;

public:
  Element();

  virtual ~Element();

  const real & get_inverse_mass() const;

  void set_inverse_mass(const real &);

  real get_mass() const;

  void set_mass(const real &);

  const Vector_2D & get_position() const;

  void set_position(const Vector_2D &);

  const Vector_2D & get_velocity() const;

  void set_velocity(const Vector_2D &);

  const Vector_2D & get_acceleration() const;

  void set_acceleration(const Vector_2D &);

  void add_force(const Vector_2D &);

  virtual void update(const real &);
};

# endif // ELEMENT_H

