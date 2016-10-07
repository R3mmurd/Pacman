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

