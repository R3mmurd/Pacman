/*
  Pacman remake

  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef SPRITE_FACTORY_H
# define SPRITE_FACTORY_H

# include <QStringList>

# include <singleton.H>
# include <sprite.H>

class Sprite_Factory : public Singleton<Sprite_Factory>
{
public:
  Sprite * build_sprite(QStringList &);
};

# endif // SPRITE_FACTORY_H

