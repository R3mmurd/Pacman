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

