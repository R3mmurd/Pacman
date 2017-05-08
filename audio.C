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
# include <audio.H>

Audio::Audio()
{
  intro = new QSound(":/audio/beginning");
  chomp = new QSound(":/audio/chomp");
  death = new QSound(":/audio/death");
  eat_ghost = new QSound(":/audio/eatghost");
  intermission = new QSound(":/audio/intermission");

  chomp->setLoops(QSound::Infinite);
  intermission->setLoops(QSound::Infinite);
}

void Audio::play_intro()
{
  intro->play();
}

void Audio::play_chomp()
{
  chomp->play();
}

void Audio::stop_chomp()
{
  chomp->stop();
}

void Audio::play_death()
{
  death->play();
}

void Audio::play_eat_ghost()
{
  eat_ghost->play();
}

void Audio::play_intermission()
{
  intermission->play();
}

void Audio::stop_intermission()
{
  intermission->stop();
}
