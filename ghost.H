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
# ifndef GHOST_H
# define GHOST_H

# include <pacman.H>
# include <find_path.H>

class Ghost : public Segment_Follower
{
  static int next_id;

  enum Status { Attacking, Running_Away };

  struct : public Telegram_Listener
  {
    Ghost * ptr_ghost;

    real    old_speed;

    void on_message_received(const Telegram & telegram)
    {
      switch (telegram.get_message())
        {
        case Pacman_Got_Big_Cookie:

          if (ptr_ghost->status == Running_Away)
            return;

          ptr_ghost->status = Running_Away;
          old_speed = ptr_ghost->get_speed();
          ptr_ghost->set_speed(50);
          ptr_ghost->path_to_follow.empty();
          ptr_ghost->current_path_point = 0;
          ptr_ghost->max_path_size_to_follow = 0;

          break;

        case Big_Cookie_Time_Over:

          if (ptr_ghost->status == Attacking)
            return;

          ptr_ghost->status = Attacking;
          ptr_ghost->set_speed(old_speed);
        }
    }
  } listener;

public:
  static Pacman * ptr_pacman;

private:
  int              id;
  int              max_path_size_to_follow;
  int              current_path_point;
  real             path_size_proportion;
  Find_Path *      ptr_find_path_algorithm;
  QList<Vector_2D> path_to_follow;
  Status           status;

  void search_path();

public:
  Ghost(const real & _path_size_proportion = 1.0);

  void select_next_target();

  Sprite_Type type() const;

  void update(const real &);

  Find_Path *& find_path_algorithm() { return ptr_find_path_algorithm; }
};

# endif // GHOST_H

