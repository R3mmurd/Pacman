/*
  Pacman remake

  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <telegram_sender.H>

void Telegram_Sender::add_listener(Telegram_Listener * listener)
{
  listeners.append(listener);
}

void Telegram_Sender::del_listener(Telegram_Listener * listener)
{
  listeners.removeOne(listener);
}

void Telegram_Sender::clear()
{
  listeners.clear();
}

void Telegram_Sender::send_global_message(void * sender,
                                               const int & message,
                                               void * extra_info)
{
  Telegram telegram(sender, message, nullptr, extra_info);

  for (Telegram_Listener * listener : listeners)
    listener->on_message_received(telegram);
}

void Telegram_Sender::send_direct_message(void * sender,
                                               const int & message,
                                               Telegram_Listener * listener,
                                               void * extra_info)
{
  Telegram telegram(sender, message, listener, extra_info);

  listener->on_message_received(telegram);
}

