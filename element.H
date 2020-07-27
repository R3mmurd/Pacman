/*
  Pacman remake

  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef ELEMENT_H
# define ELEMENT_H

# include <vector_2D.H>

class Element
{
  real      inverse_mass;
  Vector_2D position;
  Vector_2D velocity;
  Vector_2D acceleration;
  Vector_2D force_accumulator;

public:
  Element();

  virtual ~Element();

  const real & get_inverse_mass() const;

  void set_inverse_mass(const real &);

  real get_mass() const;

  void set_mass(const real &);

  const Vector_2D & get_position() const;

  void set_position(const Vector_2D &);

  const Vector_2D & get_velocity() const;

  void set_velocity(const Vector_2D &);

  const Vector_2D & get_acceleration() const;

  void set_acceleration(const Vector_2D &);

  void add_force(const Vector_2D &);

  virtual void update(const real &);
};

# endif // ELEMENT_H

