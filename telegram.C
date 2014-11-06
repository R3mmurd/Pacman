/*
  This file is part of Pacman game.
  Copyright (C) 2014 by Alejandro J. Mujica

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  Any user request of this software, write to 

  Alejandro Mujica

  aledrums@gmail.com
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

