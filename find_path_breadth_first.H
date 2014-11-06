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
# ifndef FIND_PATH_BREADTH_FIRST_H
# define FIND_PATH_BREADTH_FIRST_H

# include <QQueue>

# include <find_path.H>

class Find_Path_Breadth_First_Data : public Find_Path
{
  void insert_in_queue(const Vector_2D & p,
                       QQueue<QList<Vector_2D>> & path_queue,
                       QList<Vector_2D> * ptr_curr_path = nullptr)
  {
    QList<Vector_2D> new_path;

    if (ptr_curr_path != nullptr)
      new_path = *ptr_curr_path;

    new_path.append(p);

    path_queue.enqueue(std::move(new_path));
  }

public:

  QList<Vector_2D> find_path(const Vector_2D & src, const Vector_2D & tgt,
                             const int & tag)
  {
    RESET_ALL_TAGS;

    QQueue<QList<Vector_2D>> path_queue;

    QList<Vector_2D> current_path;

    insert_in_queue(src, path_queue);

    while (not path_queue.empty())
      {
        current_path = path_queue.dequeue();

        Vector_2D & p = current_path.last();

        if (CELL(p.get_y(), p.get_x()) == '#')
          continue;

        if (IS_TAGGED(p.get_y(), p.get_x(), tag))
          continue;

        if (p == tgt)
          {
            RESET_TAG(tag);
            return current_path;
          }

        TAG(p.get_y(), p.get_x(), tag);

        insert_in_queue(Vector_2D(p.get_x() - 1, p.get_y()), path_queue,
                        &current_path);
        insert_in_queue(Vector_2D(p.get_x() + 1, p.get_y()), path_queue,
                        &current_path);
        insert_in_queue(Vector_2D(p.get_x(), p.get_y() + 1), path_queue,
                        &current_path);
        insert_in_queue(Vector_2D(p.get_x(), p.get_y() - 1), path_queue,
                        &current_path);
      }

    current_path.clear();

    return current_path;
  }
};

using Find_Path_Breadth_First = Singleton<Find_Path_Breadth_First_Data>;

# endif // FIND_PATH_BREADTH_FIRST_H

