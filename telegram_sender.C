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

