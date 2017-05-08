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
# ifndef AUDIO_H
# define AUDIO_H

# include <QSound>

# include <singleton.H>

class Audio : public Singleton<Audio>
{
  QSound * intro;
  QSound * chomp;
  QSound * death;
  QSound * eat_ghost;
  QSound * intermission;

public:
  Audio();

  void play_intro();

  void play_chomp();

  void stop_chomp();

  void play_death();

  void play_eat_ghost();

  void play_intermission();

  void stop_intermission();
};

# endif // AUDIO_H
