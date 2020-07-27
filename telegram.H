/*
  Pacman remake

  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef TELEGRAM_H
# define TELEGRAM_H

class Telegram_Listener;

class Telegram
{
  void *              sender;
  int                 message;
  Telegram_Listener * receiver;
  void *              extra_info;
  

public:
  Telegram();

  Telegram(void *, const int &, Telegram_Listener *,
           void * _extra_info = nullptr);

  void * get_sender();

  void set_sender(void *);

  const int & get_message() const;

  void set_message(const int &);

  Telegram_Listener * get_receiver();

  void set_receiver(Telegram_Listener *);

  void * get_extra_info();

  void set_extra_info(void *);
};

# endif // TELEGRAM_H

