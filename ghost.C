/*
  Pacman remake

  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <ghost.H>
# include <messages.H>
# include <telegram_sender.H>
# include <audio.H>

int Ghost::next_id = 1;

Pacman * Ghost::ptr_pacman = nullptr;

void Ghost::search_path()
{
  current_path_point = 0;

  if (ptr_pacman == nullptr)
    return;

  Game_Board & map = Game_Board::get_instance();

  Vector_2D ghost_position = map.position_in_map(get_position());

  Vector_2D pacman_position = map.position_in_map(ptr_pacman->get_position());

  path_to_follow = ptr_find_path_algorithm->find_path(ghost_position,
                                                      pacman_position, id);
  if (path_to_follow.empty())
    return;

  path_to_follow.takeFirst();

  max_path_size_to_follow =
    real(path_to_follow.size()) / path_size_proportion;
}

Ghost::Ghost(const real & _path_size_proportion)
  : Segment_Follower(),
    max_path_size_to_follow(0), current_path_point(0),
    path_size_proportion(_path_size_proportion),
    ptr_find_path_algorithm(nullptr), path_to_follow(),
    status(Attacking)
{
  id = next_id;
  next_id = next_id << 1;

  listener.ptr_ghost = this;
  Telegram_Sender::get_instance().add_listener(&listener);
}

void Ghost::handle_target_arrive()
{
  // Empty
}

void Ghost::select_next_target()
{
  if (status == Attacking)
    {
      if (current_path_point >= max_path_size_to_follow)
        search_path();

      if (path_to_follow.empty())
        return;

      Vector_2D _tgt = path_to_follow.takeFirst();

      set_tgt(Game_Board::get_instance().real_position(_tgt));

      ++current_path_point;
    }
  else
    {
      Vector_2D position_in_map =
        Game_Board::get_instance().position_in_map(get_position());

      QList<Vector_2D> targets;

      Vector_2D p;

      p.set_x(position_in_map.get_x());
      p.set_y(position_in_map.get_y() - 1);

      if (CELL(p.get_y(), p.get_x()) != '#')
        targets.append(p);

      p.set_x(position_in_map.get_x());
      p.set_y(position_in_map.get_y() + 1);

      if (CELL(p.get_y(), p.get_x()) != '#')
        targets.append(p);

      p.set_x(position_in_map.get_x() - 1);
      p.set_y(position_in_map.get_y());

      if (CELL(p.get_y(), p.get_x()) != '#')
        targets.append(p);

      p.set_x(position_in_map.get_x() + 1);
      p.set_y(position_in_map.get_y());

      if (CELL(p.get_y(), p.get_x()) != '#')
        targets.append(p);

      real max = 0;

      Vector_2D pacman_position =
        Game_Board::get_instance().position_in_map(ptr_pacman->get_position());

      for (const Vector_2D & t : targets)
        {
          Vector_2D v = pacman_position - t;

          real d = v.magnitude();

          if (d > max)
            {
              max = d;
              set_tgt(Game_Board::get_instance().real_position(t));
            }
        }        
    }
}

Sprite_Type Ghost::type() const
{
  return ST_Ghost;
}

void Ghost::update(const real & dt)
{
  Vector_2D v = ptr_pacman->get_position() - get_position();

  if (v.magnitude() < SCALE)
    {
      if (status == Attacking)
        Telegram_Sender::get_instance().send_global_message(this,
                                                            Pacman_Was_Killed);
      else
        {
          Audio::get_instance().play_eat_ghost();
          init(Vector_2D(1, 1), listener.old_speed);
          listener.old_speed = get_speed();
          status = Running_Away;
          set_speed(50);
          path_to_follow.empty();
          current_path_point = 0;
          max_path_size_to_follow = 0;
        }
    }

  Segment_Follower::update(dt);
}

