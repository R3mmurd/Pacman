/*
  Pacman remake

  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <pacman.H>

bool Pacman::may_go_straight() const
{
  Vector_2D position_in_map =
    Game_Board::get_instance().position_in_map(get_position());

  if (curr_direction == Game_Board::North and
      CELL(position_in_map.get_y() - 1, position_in_map.get_x()) != '#' and
      IS_IN_RANGE(position_in_map.get_y() - 1, position_in_map.get_x()))
    return true;

  if (curr_direction == Game_Board::South and
      CELL(position_in_map.get_y() + 1, position_in_map.get_x()) != '#' and
      IS_IN_RANGE(position_in_map.get_y() + 1, position_in_map.get_x()))
    return true;

  if (curr_direction == Game_Board::East and
      CELL(position_in_map.get_y(), position_in_map.get_x() + 1) != '#' and
      IS_IN_RANGE(position_in_map.get_y(), position_in_map.get_x() + 1))
    return true;

  if (curr_direction == Game_Board::West and
      CELL(position_in_map.get_y(), position_in_map.get_x() - 1) != '#' and
      IS_IN_RANGE(position_in_map.get_y(), position_in_map.get_x() - 1))
    return true;

  return false;
}

Pacman::Pacman()
  : Segment_Follower(),
    curr_direction(Game_Board::Num_Directions), next_direction(curr_direction)
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
    Game_Board::get_instance().position_in_map(get_src());

  switch (next_direction)
    {
    case Game_Board::North:
      if (CELL(position_in_map.get_y() - 1, position_in_map.get_x()) != '#')
        {
          dir.set_x(0);
          dir.set_y(-1);
          curr_direction = next_direction;
        }


      break;

    case Game_Board::South:
      if (CELL(position_in_map.get_y() + 1, position_in_map.get_x()) != '#')
        {
          dir.set_x(0);
          dir.set_y(1);
          curr_direction = next_direction;
        }

      break;

    case Game_Board::East:
      if (CELL(position_in_map.get_y(), position_in_map.get_x() + 1) != '#')
        {
          dir.set_x(1);
          dir.set_y(0);
          curr_direction = next_direction;
        }

      break;

    case Game_Board::West:
      if (CELL(position_in_map.get_y(), position_in_map.get_x() - 1) != '#')
        {
          dir.set_x(-1);
          dir.set_y(0);
          curr_direction = next_direction;
        }

      break;
    default:
      break;
    }

  set_tgt(get_src() + dir * SCALE);
}

void Pacman::change_direction(const Game_Board::Direction & _direction)
{
  next_direction = _direction;
}

void Pacman::handle_target_arrive()
{
  Vector_2D position_in_map =
    Game_Board::get_instance().position_in_map(get_position());
  EAT(position_in_map.get_y(), position_in_map.get_x());
}

Sprite_Type Pacman::type() const
{
  return ST_Pacman;
}

