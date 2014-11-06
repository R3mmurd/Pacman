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
# ifndef PACMAN_H
# define PACMAN_H

# include <game_map.H>
# include <segment_follower.H>
# include <telegram_sender.H>

class Pacman : public Segment_Follower
{
  Game_Map::Direction curr_direction;
  Game_Map::Direction next_direction;

  bool may_go_straight() const;

public:
  Pacman();

  void select_next_target();

  void change_direction(const Game_Map::Direction &);

  void handle_target_arrive();

  Sprite_Type type() const;
};

# endif // PACMAN_H

