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
# ifndef MESSAGES_H
# define MESSAGES_H

# include <QString>

enum Message
{
  Pacman_Got_All_Cookies,
  Pacman_Got_Big_Cookie,
  Pacman_Was_Killed,
  Big_Cookie_Time_Over
};

class Message_String
{
  Message_String() { }

public:
  static QString get(const int & message)
  {
    switch(message)
      {
      case Pacman_Got_All_Cookies: return "You Win! :)";
      case Pacman_Got_Big_Cookie:  return "Run Away Ghosts!";
      case Pacman_Was_Killed:      return "You Lose! :(";
      case Big_Cookie_Time_Over:   return "Take care Pacman!";
      }
    return "";
  }
};

# endif // MESSAGES_H

