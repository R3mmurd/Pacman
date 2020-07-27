/*
  Pacman remake

  Author: Alejandro Mujica (aledrums@gmail.com)
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

