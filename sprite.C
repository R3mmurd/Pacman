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
# include <QPainter>

# include <sprite.H>
# include <image_buffer.H>
# include <game_map.H>

Sprite::Sprite()
  : Element(), num_images(0), curr_image_idx(0), images_speed(30)
{
  // Empty
}

Sprite::Sprite(const Sprite & sprite)
  : Element(sprite), num_images(sprite.num_images),
    curr_image_idx(sprite.curr_image_idx), images_speed(sprite.images_speed)
{
  for (int i = 0; i < num_images; ++i)
    images_names[i] = sprite.images_names[i];
}

Sprite::Sprite(Sprite && sprite)
  : Element(std::move(sprite)), num_images(0), curr_image_idx(0),
    images_speed(30)
{
  std::swap(num_images, sprite.num_images);
  std::swap(images_names, sprite.images_names);
  std::swap(curr_image_idx, sprite.curr_image_idx);
  std::swap(images_speed, sprite.images_speed);
}

Sprite::~Sprite()
{
  // Empty
}

void Sprite::draw(QPainter & painter)
{
  if (curr_image_idx == num_images)
    throw std::overflow_error("Image index out of range");

  Image_Buffer & buffer = Image_Buffer::get_instance();

  painter.drawPixmap(get_position().get_x() - SCALE / 2,
                     get_position().get_y() - SCALE / 2,
                     buffer[images_names[int(curr_image_idx)]]);
}

void Sprite::add_image(const QString & name)
{
  if (num_images == Max_Num_Images)
    return;

  images_names[num_images++] = name;
}

void Sprite::update(const real & dt)
{
  curr_image_idx += images_speed * dt;

  if (curr_image_idx >= num_images)
    curr_image_idx -= num_images * int(curr_image_idx / num_images);

  Element::update(dt);
}

Sprite & Sprite::operator = (const Sprite & sprite)
{
  if (this == &sprite)
    return *this;

  (Element &) (*this) = sprite;

  num_images = sprite.num_images;

  for (int i = 0; i < num_images; ++i)
    images_names[i] = sprite.images_names[i];

  curr_image_idx = sprite.curr_image_idx;
  images_speed = sprite.images_speed;

  return *this;  
}

Sprite & Sprite::operator = (Sprite && sprite)
{
  (Element &) (*this) = std::move(sprite);

  std::swap(num_images, sprite.num_images);
  std::swap(images_names, sprite.images_names);
  std::swap(curr_image_idx, sprite.curr_image_idx);
  std::swap(images_speed, sprite.images_speed);

  return *this;
}

