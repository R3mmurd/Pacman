/*
  Pacman remake

  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <cassert>

# include <QApplication>
# include <QPainter>
# include <QMessageBox>
# include <QFile>
# include <QKeyEvent>
# include <QTextStream>

# include <game_panel.H>
# include <game_board.H>
# include <sprite_factory.H>
# include <telegram_sender.H>

Game_Panel::Game_Panel(QWidget * parent)
  : QWidget(parent), ptr_pacman(nullptr)
{
  init_game();

  listener.panel = this;

  setFixedSize(1024, 768);

  connect(&timer, SIGNAL(timeout()), this, SLOT(update()));

  Audio::get_instance().play_intro();
}

void Game_Panel::remove_sprites()
{
  while (not sprites.empty())
    delete sprites.takeFirst();
}

void Game_Panel::init_game()
{
  try
  {
    Game_Board::get_instance().load();
  }
  catch(const std::exception & e)
  {
    QMessageBox::critical(this, "Error", e.what());
    QApplication::exit(EXIT_FAILURE);
  }

  Telegram_Sender::get_instance().clear();

  remove_sprites();

  Telegram_Sender::get_instance().add_listener(&listener);

  load_sprites();

  if (sprites.empty())
    {
      QMessageBox::critical(this, "Error", "There is not Pacman in the map");
      QApplication::exit(EXIT_FAILURE);
    }

  status = Status::Init;

  message = "Press any key to start.";
}

void Game_Panel::start_game()
{
  status = Status::Running;
  timer.start(33);
  time.start();
  Audio::get_instance().play_chomp();
}

void Game_Panel::stop_game(const int & num_message)
{
  timer.stop();
  status = Status::Reinit;
  message = Message_String::get(num_message);
}

void Game_Panel::update()
{
  repaint();
}

void Game_Panel::paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  // FIXME: Screen scrolling is not working when map is smaller than panel.
  qreal dx = 0;
  qreal dy = 0;

  qreal w_2 = width() / 2;
  qreal h_2 = height() / 2;

  qreal x_off_set = SCALED_MAP_WIDTH - ptr_pacman->get_position().get_x();
  qreal y_off_set = SCALED_MAP_HEIGHT - ptr_pacman->get_position().get_y();

  if (ptr_pacman->get_position().get_x() > w_2 and x_off_set > w_2)
    dx = -ptr_pacman->get_position().get_x() + w_2;
  else if (x_off_set < w_2)
    dx = -(SCALED_MAP_WIDTH - width());

  if (ptr_pacman->get_position().get_y() > h_2 and y_off_set > h_2)
    dy = -ptr_pacman->get_position().get_y() + h_2;
  else if (y_off_set < h_2)
    dy = -(SCALED_MAP_HEIGHT - height());

  painter.translate(dx, dy);

  painter.fillRect(0, 0, SCALED_MAP_WIDTH, SCALED_MAP_HEIGHT, Qt::lightGray);

  real dt = 0;

  if (status == Status::Running)
    {
      dt = real(time.elapsed()) / 1000.0;
      Game_Board::get_instance().update(dt);
    }

  Game_Board::get_instance().draw(painter);

  for (Sprite * ptr_sprite : sprites)
    {
      if (status == Status::Running)
        ptr_sprite->update(dt);
          
      ptr_sprite->draw(painter);
    }

  if (status != Status::Running)
    {
      painter.setPen(Qt::red);
      QFont font("Helvetica");
      font.setPointSize(64);
      painter.setFont(font);
      QFontMetrics metrics = painter.fontMetrics();
      QSize size = metrics.size(Qt::TextSingleLine, message);
      QRect rect(QPoint((-dx + width() / 2) - (size.width() / 2),
                        (-dy + height() / 2) - (size.height() / 2)), size);
      painter.drawText(rect, Qt::TextSingleLine, message);
    }

  time.start();
}

void Game_Panel::keyPressEvent(QKeyEvent * evt)
{

  if (status == Status::Init)
    start_game();
  else if (status == Status::Reinit)
    {
      init_game();
      status = Status::Init;
      repaint();
      return;
    }

  switch (evt->key())
    {
    case Qt::Key_Up:
      ptr_pacman->change_direction(Game_Board::North);
      break;
    case Qt::Key_Down:
      ptr_pacman->change_direction(Game_Board::South);
      break;
    case Qt::Key_Left:
      ptr_pacman->change_direction(Game_Board::West);
      break;
    case Qt::Key_Right:
      ptr_pacman->change_direction(Game_Board::East);
      break;
    }
}

void Game_Panel::closeEvent(QCloseEvent *)
{
  remove_sprites();
}

void Game_Panel::load_sprites()
{
  QFile file("Text_Files/sprites.txt");

  if(not file.open(QIODevice::ReadOnly)) 
    QMessageBox::information(0, "error", file.errorString());

  QTextStream in(&file);

  // The first line of the file must be Pacman
  QString line = in.readLine();

  // If the first line is not Pacman, I can't play the game.
  if (line.at(0) == '#' or line.at(0) != '0')
    return;

  QStringList attr = line.split(",");    
  sprites.append(Sprite_Factory::get_instance().build_sprite(attr));

  ptr_pacman = static_cast<Pacman *>(sprites.last());

  Ghost::ptr_pacman = ptr_pacman;

  assert(Ghost::ptr_pacman != nullptr);

  while(not in.atEnd())
    {
      QString line = in.readLine();

      if (line.at(0) == '#')
        continue;

      QStringList attr = line.split(",");    
      sprites.append(Sprite_Factory::get_instance().build_sprite(attr));
    }

  file.close();
}

