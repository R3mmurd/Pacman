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
# include <cassert>

# include <QPainter>
# include <QMessageBox>
# include <QFile>

# include <game_panel.H>
# include <game_map.H>
# include <sprite_factory.H>
# include <telegram_sender.H>

# include <time_manager.H>

Game_Panel::Game_Panel(QWidget * parent)
  : QWidget(parent), ptr_pacman(nullptr)
{
  init_game();

  listener.panel = this;

  setFixedSize(1024, 768);

  connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
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
    Game_Map::get_instance().load();
  }
  catch(const std::exception & e)
  {
    QMessageBox::critical(this, "Error", e.what());
    exit(1);
  }

  Telegram_Sender::get_instance().clear();

  remove_sprites();

  Telegram_Sender::get_instance().add_listener(&listener);

  load_sprites();

  if (sprites.empty())
    {
      QMessageBox::critical(this, "Error", "No hay pacman en el mapa");
      exit(2);
    }

  status = Init;

  message = "Press any key to start.";
}

void Game_Panel::start_game()
{
  status = Running;
  Time_Manager::get_instance().init();
  timer.start(33);
}

void Game_Panel::stop_game(const int & num_message)
{
  timer.stop();
  status = Reinit;
  message = Message_String::get(num_message);
  Time_Manager::get_instance().reset();
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

  Game_Map::get_instance().draw(painter);

  real dt = 0;

  if (status == Running)
    dt = real(DELTA_TIME) / 1000.0;

  for (Sprite * ptr_sprite : sprites)
    {
      if (status == Running)
        {
          ptr_sprite->update(dt);
          Game_Map::get_instance().update(dt);
        }
      ptr_sprite->draw(painter);
    }

  if (status != Running)
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
}

void Game_Panel::keyPressEvent(QKeyEvent * evt)
{

  if (status == Init)
    start_game();
  else if (status == Reinit)
    {
      init_game();
      status = Init;
      repaint();
      return;
    }

  switch (evt->key())
    {
    case Qt::Key_Up:
      ptr_pacman->change_direction(Game_Map::North);
      break;
    case Qt::Key_Down:
      ptr_pacman->change_direction(Game_Map::South);
      break;
    case Qt::Key_Left:
      ptr_pacman->change_direction(Game_Map::West);
      break;
    case Qt::Key_Right:
      ptr_pacman->change_direction(Game_Map::East);
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

  // Primera línea debe ser el pacman principal
  QString line = in.readLine();

  // No haré más nada, pues los fantasmas trabajan en función del pacman
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

