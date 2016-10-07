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
# ifndef SPRITE_H
# define SPRITE_H

class QPainter;

# include <QString>

# include <element.H>

enum Sprite_Type
{
  ST_Pacman, ST_Ghost
};

class Sprite : public Element
{
  static constexpr unsigned int Max_Num_Images = 10;

protected:
  unsigned int num_images;
  QString      images_names[Max_Num_Images];
  real         curr_image_idx;
  real         images_speed;

public:
  Sprite();

  Sprite(const Sprite &);

  Sprite(Sprite &&);

  ~Sprite();

  void add_image(const QString &);

  Sprite & operator = (const Sprite &);

  Sprite & operator = (Sprite &&);

  virtual void draw(QPainter &);

  void update(const real &) override;

  virtual Sprite_Type type() const = 0;
};

# endif // SPRITE_H

