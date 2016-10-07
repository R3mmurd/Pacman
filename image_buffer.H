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
# ifndef IMAGE_BUFFER_H
# define IMAGE_BUFFER_H

# include <QMap>
# include <QString>
# include <QPixmap>

# include <singleton.H>

class Image_Buffer : public Singleton<Image_Buffer>
{
  QMap<QString, std::shared_ptr<QPixmap>> buffer;

public:
  QPixmap * ptr_image_for(const QString & name)
  {
    if (buffer.contains(name))
      return buffer[name].get();

    std::shared_ptr<QPixmap> sptr_image(new QPixmap);

    sptr_image->load(name);

    buffer[name] = sptr_image;

    return sptr_image.get();
  }

  QPixmap & image_for(const QString & name)
  {
    return *ptr_image_for(name);
  }

  QPixmap & operator [] (const QString & name)
  {
    return image_for(name);
  }
};

# endif // IMAGE_BUFFER_H

