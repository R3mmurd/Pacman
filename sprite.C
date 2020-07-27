/*
  Pacman remake

  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <stdexcept>

# include <QPainter>

# include <sprite.H>
# include <image_buffer.H>
# include <game_board.H>

Sprite::Sprite()
  : Element(), num_images(0), curr_image_idx(0), timer(0), time_interval(0.02)
{
  // Empty
}

Sprite::Sprite(const Sprite & sprite)
  : Element(sprite), num_images(sprite.num_images),
    curr_image_idx(sprite.curr_image_idx), timer(sprite.timer),
    time_interval(sprite.time_interval)
{
  for (unsigned int i = 0; i < num_images; ++i)
    images_names[i] = sprite.images_names[i];
}

Sprite::Sprite(Sprite && sprite)
  : Element(std::move(sprite)), num_images(0), curr_image_idx(0), timer(0),
    time_interval(0.2)
{
  std::swap(num_images, sprite.num_images);
  std::swap(images_names, sprite.images_names);
  std::swap(curr_image_idx, sprite.curr_image_idx);
  std::swap(timer, sprite.timer);
  std::swap(time_interval, sprite.time_interval);
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
  if (num_images > 1)
    {
      timer += dt;

      if (timer > time_interval)
        {
          timer = module(timer, time_interval);
          curr_image_idx = (curr_image_idx + 1) % num_images;
        }
    }
  Element::update(dt);
}

Sprite & Sprite::operator = (const Sprite & sprite)
{
  if (this == &sprite)
    return *this;

  (Element &) (*this) = sprite;

  num_images = sprite.num_images;

  for (unsigned int i = 0; i < num_images; ++i)
    images_names[i] = sprite.images_names[i];

  curr_image_idx = sprite.curr_image_idx;
  timer = sprite.timer;
  time_interval = sprite.time_interval;

  return *this;  
}

Sprite & Sprite::operator = (Sprite && sprite)
{
  (Element &) (*this) = std::move(sprite);

  std::swap(num_images, sprite.num_images);
  std::swap(images_names, sprite.images_names);
  std::swap(curr_image_idx, sprite.curr_image_idx);
  std::swap(timer, sprite.timer);
  std::swap(time_interval, sprite.time_interval);

  return *this;
}

