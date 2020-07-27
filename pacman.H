/*
  Pacman remake

  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef PACMAN_H
# define PACMAN_H

# include <game_board.H>
# include <segment_follower.H>
# include <telegram_sender.H>

class Pacman : public Segment_Follower
{
  Game_Board::Direction curr_direction;
  Game_Board::Direction next_direction;

  bool may_go_straight() const;

public:
  Pacman();

  void select_next_target() override;

  void change_direction(const Game_Board::Direction &);

  void handle_target_arrive() override;

  Sprite_Type type() const override;
};

# endif // PACMAN_H

