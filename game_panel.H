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
# ifndef GAME_PANEL_H
# define GAME_PANEL_H

# include <QWidget>
# include <QList>
# include <QTime>
# include <QTimer>

# include <pacman.H>
# include <ghost.H>

class Game_Panel : public QWidget
{
  Q_OBJECT
 
  enum class Status { Init, Running, Reinit };

  Status status;

  Pacman * ptr_pacman;

  QList<Sprite *> sprites;

  QString message;

  QTime time;

  QTimer timer;

  void load_sprites();

  struct : public Telegram_Listener
  {
    Game_Panel * panel;

    void on_message_received(const Telegram & telegram)
    {
      const int & message = telegram.get_message();

      if (message == Pacman_Was_Killed or message == Pacman_Got_All_Cookies)
        panel->stop_game(message);
    };

  } listener;

  void remove_sprites();

  void init_game();

  void start_game();

  void stop_game(const int &);

private slots:
  void update();

protected:
  void paintEvent(QPaintEvent *);

  void keyPressEvent(QKeyEvent *);

  void closeEvent(QCloseEvent *);

public:
  Game_Panel(QWidget * parent = nullptr);
};

#endif // GAME_PANEL_H
