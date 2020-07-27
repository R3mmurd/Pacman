/*
  Pacman remake

  Author: Alejandro Mujica (aledrums@gmail.com)
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
  unsigned int curr_image_idx;
  real         timer;
  real         time_interval;

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

