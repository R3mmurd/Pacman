/*
  Pacman remake

  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <telegram.H>

Telegram::Telegram()
  : sender(nullptr), receiver(nullptr), extra_info(nullptr)
{
  // Empty
}

Telegram::Telegram(void * _sender, const int & _message,
                   Telegram_Listener * _receiver, void * _extra_info)
  : sender(_sender), message(_message), receiver(_receiver),
    extra_info(_extra_info)
{
  // Empty
}

void * Telegram::get_sender()
{
  return sender;
}

void Telegram::set_sender(void * _sender)
{
  sender = _sender;
}

const int & Telegram::get_message() const
{
  return message;
}

void Telegram::set_message(const int & _message)
{
  message = _message;
}

Telegram_Listener * Telegram::get_receiver()
{
  return receiver;
}

void Telegram::set_receiver(Telegram_Listener * _receiver)
{
  receiver = _receiver;
}

void * Telegram::get_extra_info()
{
  return extra_info;
}

void Telegram::set_extra_info(void * _extra_info)
{
  extra_info = _extra_info;
}

