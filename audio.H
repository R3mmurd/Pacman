/*
  Pacman remake

  Author: Alejandro Mujica (aledrums@gmail.com)
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
