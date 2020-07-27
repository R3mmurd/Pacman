/*
  Pacman remake

  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <limits>
# include <stdexcept>

# include <element.H>

Element::Element()
  : inverse_mass(0), position(), velocity(), acceleration(), force_accumulator()
{
  // Empty
}

Element::~Element()
{
  // Empty
}

const real & Element::get_inverse_mass() const
{
  return inverse_mass;
}

void Element::set_inverse_mass(const real & _inverse_mass)
{
  inverse_mass = _inverse_mass;
}

real Element::get_mass() const
{
  if (inverse_mass == 0)
    return std::numeric_limits<real>::max();

  return 1 / inverse_mass;
}

void Element::set_mass(const real & mass)
{
  if (mass == 0)
    throw std::logic_error("May not set mass = 0 to objects");

  inverse_mass = 1 / mass;
}

const Vector_2D & Element::get_position() const
{
  return position;
}

void Element::set_position(const Vector_2D & _position)
{
  position = _position;
}

const Vector_2D & Element::get_velocity() const
{
  return velocity;
}

void Element::set_velocity(const Vector_2D & _velocity)
{
  velocity = _velocity;
}

const Vector_2D & Element::get_acceleration() const
{
  return acceleration;
}

void Element::set_acceleration(const Vector_2D & _acceleration)
{
  acceleration = _acceleration;
}

void Element::add_force(const Vector_2D & force)
{
  force_accumulator += force;
}

void Element::update(const real & dt)
{
  if (inverse_mass == 0 or dt == 0)
    return;

  position.add_scaled_vector(velocity, dt);

  Vector_2D resulting_acceleration = acceleration;

  resulting_acceleration.add_scaled_vector(force_accumulator, inverse_mass);

  velocity.add_scaled_vector(resulting_acceleration, dt);

  force_accumulator.clear();
}

