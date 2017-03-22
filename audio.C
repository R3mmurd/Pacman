# include <audio.H>

Audio::Audio()
{
  intro = new QSound("Audio/pacman_beginning.wav");
  chomp = new QSound("Audio/pacman_chomp.wav");
  death = new QSound("Audio/pacman_death.wav");
  eat_ghost = new QSound("Audio/pacman_eatghost.wav");
  intermission = new QSound("Audio/pacman_intermission.wav");

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
