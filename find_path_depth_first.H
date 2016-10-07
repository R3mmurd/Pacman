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
# ifndef FIND_PATH_DEPTH_FIRST_H
# define FIND_PATH_DEPTH_FIRST_H

# include <find_path.H>

class Find_Path_Depth_First :
    public Singleton<Find_Path_Depth_First>,
    public Find_Path
{
  bool find_path_rec(const Vector_2D & src, const Vector_2D & tgt,
                     const int & tag, QList<Vector_2D> & path)
  {
    if (IS_TAGGED(src.get_y(), src.get_x(), tag) or
        CELL(src.get_y(), src.get_x()) == '#')
      return false;

    TAG(src.get_y(), src.get_x(), tag);

    path.append(src);

    if (src == tgt)
      return true;

    Vector_2D p;

    p.set_x(src.get_x());
    p.set_y(src.get_y() - 1);

    if (not IS_TAGGED(p.get_y(), p.get_x(), tag) and
        CELL(p.get_y(), p.get_x()) != '#')
      if (find_path_rec(p, tgt, tag, path))
        return true;

    p.set_x(src.get_x() + 1);
    p.set_y(src.get_y());

    if (not IS_TAGGED(p.get_y(), p.get_x(), tag) and
        CELL(p.get_y(), p.get_x()) != '#')
      if (find_path_rec(p, tgt, tag, path))
        return true;


    p.set_x(src.get_x());
    p.set_y(src.get_y() + 1);

    if (not IS_TAGGED(p.get_y(), p.get_x(), tag) and
        CELL(p.get_y(), p.get_x()) != '#')
      if (find_path_rec(p, tgt, tag, path))
        return true;

    p.set_x(src.get_x() - 1);
    p.set_y(src.get_y());

    if (not IS_TAGGED(p.get_y(), p.get_x(), tag) and
        CELL(p.get_y(), p.get_x()) != '#')
      if (find_path_rec(p, tgt, tag, path))
        return true;

    path.takeLast();

    return false;
  }

public:

  QList<Vector_2D> find_path(const Vector_2D & src, const Vector_2D & tgt,
                             const int & tag)
  {
    RESET_TAG(tag);

    QList<Vector_2D> path;

    path.append(src);

    TAG(src.get_y(), src.get_x(), tag);

    Vector_2D p;

    p.set_x(src.get_x());
    p.set_y(src.get_y() - 1);

    if (not IS_TAGGED(p.get_y(), p.get_x(), tag) and
        CELL(p.get_y(), p.get_x()) != '#')
      if (find_path_rec(p, tgt, tag, path))
        return path;

    p.set_x(src.get_x() + 1);
    p.set_y(src.get_y());

    if (not IS_TAGGED(p.get_y(), p.get_x(), tag) and
        CELL(p.get_y(), p.get_x()) != '#')
      if (find_path_rec(p, tgt, tag, path))
        return path;

    p.set_x(src.get_x());
    p.set_y(src.get_y() + 1);

    if (not IS_TAGGED(p.get_y(), p.get_x(), tag) and
        CELL(p.get_y(), p.get_x()) != '#')
      if (find_path_rec(p, tgt, tag, path))
        return path;

    p.set_x(src.get_x() - 1);
    p.set_y(src.get_y());

    if (not IS_TAGGED(p.get_y(), p.get_x(), tag) and
        CELL(p.get_y(), p.get_x()) != '#')
      if (find_path_rec(p, tgt, tag, path))
        return path;

    path.clear();

    return path;
  }
};

# endif // FIND_PATH_DEPTH_FIRST_H

