/*
  Pacman remake

  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef GAME_PANEL_H
# define GAME_PANEL_H

# include <QWidget>
# include <QList>
# include <QTime>
# include <QTimer>

# include <audio.H>

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
        {
          panel->stop_game(message);
          Audio::get_instance().stop_intermission();
          Audio::get_instance().stop_chomp();
        }

      if (message == Pacman_Was_Killed)
        Audio::get_instance().play_death();
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
