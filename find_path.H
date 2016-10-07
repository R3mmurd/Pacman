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
# ifndef FIND_PATh_H
# define FIND_PATh_H

# include <QList>

# include <game_board.H>

enum Path_Find_Type
{
  FPT_Breadth_First, FPT_Depth_First, Num_Path_Find_Type
};

class Find_Path
{
public:
  virtual QList<Vector_2D>
  find_path(const Vector_2D &, const Vector_2D &, const int &) = 0;
};

# endif // FIND_PATh_H

