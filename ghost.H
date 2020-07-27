/*
  Pacman remake

  Author: Alejandro Mujica (aledrums@gmail.com)
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

  void handle_target_arrive() override;

  void select_next_target() override;

  Sprite_Type type() const override;

  void update(const real &) override;

  Find_Path *& find_path_algorithm() { return ptr_find_path_algorithm; }
};

# endif // GHOST_H

