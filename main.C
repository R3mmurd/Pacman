/*
  Pacman remake

  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <QApplication>
# include <game_panel.H>

int main(int argc, char * argv[])
{
  QApplication app(argc, argv);

  Audio::get_instance();

  Game_Panel panel;
  panel.show();

  return app.exec();
}

