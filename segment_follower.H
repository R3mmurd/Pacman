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
# ifndef SEGMENT_FOLLOWER_H
# define SEGMENT_FOLLOWER_H

# include <sprite.H>
# include <functions.H>

class Segment_Follower : public Sprite
{
  real      speed;
  real      angle;
  Vector_2D src;
  Vector_2D tgt;
  Vector_2D direction;

  void compute_velocity();

protected:
  void set_tgt(const Vector_2D &);

public:

  Segment_Follower();

  Segment_Follower(const Segment_Follower &);

  Segment_Follower(Segment_Follower &&);

  const real & get_speed() const;

  void set_speed(const real &);

  const Vector_2D & get_src() const;

  const Vector_2D & get_tgt() const;

  virtual void init(const Vector_2D &, const real &);

  void draw(QPainter &) override;

  void update(const real &) override;

  virtual void handle_target_arrive() = 0;

  virtual void select_next_target() = 0;

  Segment_Follower & operator = (const Segment_Follower &);

  Segment_Follower & operator = (Segment_Follower &&);
};

# endif // SEGMENT_FOLLOWER_H

