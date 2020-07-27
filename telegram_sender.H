/*
  Pacman remake

  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef TELEGRAM_SENDER_H
# define TELEGRAM_SENDER_H

# include <QList>

# include <singleton.H>
# include <telegram_listener.H>
# include <messages.H>

class Telegram_Sender : public Singleton<Telegram_Sender>
{
  QList<Telegram_Listener *> listeners;

public:
  void add_listener(Telegram_Listener *);

  void del_listener(Telegram_Listener *);

  void clear();

  void send_global_message(void *, const int &, void * extra_info = nullptr);

  void send_direct_message(void *, const int &, Telegram_Listener * receiver,
                           void * extra_info = nullptr);
};

# endif // TELEGRAM_SENDER_H

