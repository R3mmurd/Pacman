/*
  Pacman remake

  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef TELEGRAM_LISTENER_H
# define TELEGRAM_LISTENER_H

# include <telegram.H>

class Telegram_Listener
{
public:
  virtual void on_message_received(const Telegram &) = 0;
};

# endif // TELEGRAM_LISTENER_H

