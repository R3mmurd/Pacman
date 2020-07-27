/*
  Pacman remake

  Author: Alejandro Mujica (aledrums@gmail.com)
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

