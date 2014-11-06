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
# ifndef GAME_MAP_H
# define GAME_MAP_H

# include <singleton.H>
# include <vector_2D.H>

# define IS_IN_RANGE(i, j)     (Game_Map::get_instance().is_in_range(i, j))
# define CELL(i, j)            (Game_Map::get_instance().element_at(i, j))
# define EAT(i, j)             (Game_Map::get_instance().eat(i, j))
# define SCALE                 (Game_Map::get_instance().get_scale())
# define MAP_WIDTH             (Game_Map::get_instance().get_width())
# define MAP_HEIGHT            (Game_Map::get_instance().get_height())
# define SCALED_MAP_WIDTH      (MAP_WIDTH * SCALE)
# define SCALED_MAP_HEIGHT     (MAP_HEIGHT * SCALE)
# define TAG(i, j, val)        (Game_Map::get_instance().tag(i, j, val))
# define UNTAG(i, j, val)      (Game_Map::get_instance().untag(i, j, val))
# define IS_TAGGED(i, j, val)  (Game_Map::get_instance().is_tagged(i, j, val))
# define RESET_TAG(val)        (Game_Map::get_instance().reset_tag(val))
# define RESET_ALL_TAGS        (Game_Map::get_instance().reset_all_tags())

class QPainter;

class Game_Map_Data
{
  struct Cell
  {
    char element;
    int  tag;

    Cell()
      : element(' '), tag(0)
    {
      // Empty
    }
  };

  enum Status { Default_Status, Counting_Time_For_Big_Cookie };

  static constexpr real Max_Time_For_Big_Cookie = 100.0;

  size_t  width;
  size_t  height;
  real    scale;
  Cell ** map;
  size_t  num_cookies;
  real    current_time_big_cookie;
  Status  status;

  void destroy_map();

protected:
  Game_Map_Data();

public:
  enum Direction { North, South, East, West, Num_Directions };

  ~Game_Map_Data();

  void load();

  void draw(QPainter &);

  bool is_cell_visited_for(const int &);

  char & element_at(const size_t &, const size_t &);

  const size_t & get_width() const;

  const size_t & get_height() const;

  const real & get_scale() const;

  void tag(const size_t &, const size_t &, const int &);

  bool is_tagged(const size_t &, const size_t &, const int &) const;

  void untag(const size_t &, const size_t &, const int &);

  void reset_tag(const int &);

  void reset_all_tags();

  void eat(const size_t &, const size_t &);

  bool is_in_range(const int &, const int &) const;

  Vector_2D position_in_map(const Vector_2D &);

  Vector_2D real_position(const Vector_2D &);

  void update(const real &);
};

using Game_Map = Singleton<Game_Map_Data>;

# endif // GAME_MAP_H

