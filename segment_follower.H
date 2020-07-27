/*
  Pacman remake

  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef SEGMENT_FOLLOWER_H
# define SEGMENT_FOLLOWER_H

# include <sprite.H>
# include <functions.H>

class Segment_Follower : public Sprite
{
  real      speed;
  real      angle;
  Vector_2D src;
  Vector_2D tgt;
  Vector_2D direction;

  void compute_velocity();

protected:
  void set_tgt(const Vector_2D &);

public:

  Segment_Follower();

  Segment_Follower(const Segment_Follower &);

  Segment_Follower(Segment_Follower &&);

  const real & get_speed() const;

  void set_speed(const real &);

  const Vector_2D & get_src() const;

  const Vector_2D & get_tgt() const;

  virtual void init(const Vector_2D &, const real &);

  void draw(QPainter &) override;

  void update(const real &) override;

  virtual void handle_target_arrive() = 0;

  virtual void select_next_target() = 0;

  Segment_Follower & operator = (const Segment_Follower &);

  Segment_Follower & operator = (Segment_Follower &&);
};

# endif // SEGMENT_FOLLOWER_H

