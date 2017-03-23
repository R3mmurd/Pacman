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
