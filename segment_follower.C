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
# include <QPainter>

# include <segment_follower.H>
# include <game_map.H>

void Segment_Follower::compute_velocity()
{
  direction = tgt - src;
  direction.normalize();
  set_velocity(speed * direction);
}

void Segment_Follower::set_tgt(const Vector_2D & _tgt)
{
  tgt = _tgt;
}

Segment_Follower::Segment_Follower()
  : Sprite(), speed(0.0), angle(0.0), src(), tgt(), direction()
{
  // Empty
}

Segment_Follower::Segment_Follower(const Segment_Follower & sf)
  : Sprite(sf), speed(sf.speed), angle(sf.angle), src(sf.src), tgt(sf.tgt),
    direction(sf.direction)
{
  // Empty
}

Segment_Follower::Segment_Follower(Segment_Follower && sf)
  : Sprite(std::move(sf)), speed(0.0), angle(0.0), src(), tgt(), direction()
{
  std::swap(speed, sf.speed);
  std::swap(angle, sf.angle);
  std::swap(src, sf.src);
  std::swap(tgt, sf.tgt);
  std::swap(direction, sf.direction);
}

const real & Segment_Follower::get_speed() const
{
  return speed;
}

const Vector_2D & Segment_Follower::get_src() const
{
  return src;
}

const Vector_2D & Segment_Follower::get_tgt() const
{
  return tgt;
}

void Segment_Follower::set_speed(const real & _speed)
{
  speed = _speed;
}

void Segment_Follower::update(const real & dt)
{
  Sprite::update(dt);

  if (src != tgt)
    angle = compute_angle_between(src, tgt);

  real expected_distance = (tgt - src).magnitude();

  real distance = (get_position() - src).magnitude();

  real error = distance - expected_distance;

  while (error >= 0)
    {
      set_position(tgt);

      handle_target_arrive();

      src = get_position();

      select_next_target();
      
      Vector_2D dir = tgt - src;
      dir.normalize();
      set_position(get_position() + dir * error);

      compute_velocity();

      expected_distance = (tgt - src).magnitude();

      distance = (get_position() - src).magnitude();

      error = distance - expected_distance;

      if (src != tgt)
        angle = compute_angle_between(src, tgt);

      if (error == 0)
        break;
    }
}

void Segment_Follower::draw(QPainter & painter)
{

  QPoint pos(get_position().get_x(), get_position().get_y());

  QMatrix prev_matrix = painter.matrix();

  QMatrix matrix = painter.matrix();

  matrix.translate(pos.x(), pos.y());
  matrix.rotate(angle);
  matrix.translate(-pos.x(), -pos.y());
  painter.setMatrix(matrix);
  Sprite::draw(painter);
  painter.setMatrix(prev_matrix);
}

void Segment_Follower::init(const Vector_2D & init_pos, const real & _speed)
{
  set_position(Game_Map::get_instance().real_position(init_pos));

  set_inverse_mass(0.1);
  speed = _speed;
  src   = get_position();

  select_next_target();

  compute_velocity();
}

void Segment_Follower::handle_target_arrive()
{
  // Empty
}

Segment_Follower & Segment_Follower::operator = (const Segment_Follower & sf)
{
  if (&sf == this)
    return *this;

  (Sprite &) (*this) = sf;

  speed     = sf.speed;
  angle     = sf.angle;
  src       = sf.src;
  tgt       = sf.tgt;
  direction = sf.direction;

  return *this;
}

Segment_Follower & Segment_Follower::operator = (Segment_Follower && sf)
{
  (Sprite &) (*this) = std::move(sf);

  std::swap(speed, sf.speed);
  std::swap(angle, sf.angle);
  std::swap(src, sf.src);
  std::swap(tgt, sf.tgt);
  std::swap(direction, sf.direction);

  return *this;
}

