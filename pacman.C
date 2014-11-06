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
# include <pacman.H>

bool Pacman::may_go_straight() const
{
  Vector_2D position_in_map =
    Game_Map::get_instance().position_in_map(get_position());

  if (curr_direction == Game_Map::North and
      CELL(position_in_map.get_y() - 1, position_in_map.get_x()) != '#' and
      IS_IN_RANGE(position_in_map.get_y() - 1, position_in_map.get_x()))
    return true;

  if (curr_direction == Game_Map::South and
      CELL(position_in_map.get_y() + 1, position_in_map.get_x()) != '#' and
      IS_IN_RANGE(position_in_map.get_y() + 1, position_in_map.get_x()))
    return true;

  if (curr_direction == Game_Map::East and
      CELL(position_in_map.get_y(), position_in_map.get_x() + 1) != '#' and
      IS_IN_RANGE(position_in_map.get_y(), position_in_map.get_x() + 1))
    return true;

  if (curr_direction == Game_Map::West and
      CELL(position_in_map.get_y(), position_in_map.get_x() - 1) != '#' and
      IS_IN_RANGE(position_in_map.get_y(), position_in_map.get_x() - 1))
    return true;

  return false;
}

Pacman::Pacman()
  : Segment_Follower(),
    curr_direction(Game_Map::Num_Directions), next_direction(curr_direction)
{
  // Empty
}

void Pacman::select_next_target()
{
  Vector_2D dir(0, 0);

  if (may_go_straight())
    {
      dir = get_velocity();
      dir.normalize();
    }

  Vector_2D position_in_map =
    Game_Map::get_instance().position_in_map(get_src());

  switch (next_direction)
    {
    case Game_Map::North:
      if (CELL(position_in_map.get_y() - 1, position_in_map.get_x()) != '#')
        {
          dir.set_x(0);
          dir.set_y(-1);
          curr_direction = next_direction;
        }


      break;

    case Game_Map::South:
      if (CELL(position_in_map.get_y() + 1, position_in_map.get_x()) != '#')
        {
          dir.set_x(0);
          dir.set_y(1);
          curr_direction = next_direction;
        }

      break;

    case Game_Map::East:
      if (CELL(position_in_map.get_y(), position_in_map.get_x() + 1) != '#')
        {
          dir.set_x(1);
          dir.set_y(0);
          curr_direction = next_direction;
        }

      break;

    case Game_Map::West:
      if (CELL(position_in_map.get_y(), position_in_map.get_x() - 1) != '#')
        {
          dir.set_x(-1);
          dir.set_y(0);
          curr_direction = next_direction;
        }

      break;
    }

  set_tgt(get_src() + dir * SCALE);
}

void Pacman::change_direction(const Game_Map::Direction & _direction)
{
  next_direction = _direction;
}

void Pacman::handle_target_arrive()
{
  Vector_2D position_in_map =
    Game_Map::get_instance().position_in_map(get_position());
  EAT(position_in_map.get_y(), position_in_map.get_x());
}

Sprite_Type Pacman::type() const
{
  return ST_Pacman;
}

