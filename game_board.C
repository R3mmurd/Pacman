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
# include <stdexcept>

# include <QString>
# include <QFile>
# include <QTextStream>
# include <QPainter>

# include <game_board.H>
# include <telegram_sender.H>
# include <messages.H>

Game_Board::Game_Board()
  : width(0), height(0), scale(0.0), map(nullptr), num_cookies(0),
    status(Default_Status)
{
  // Empty
}

Game_Board::~Game_Board()
{
  destroy_map();
}

void Game_Board::load()
{
  destroy_map();

  QString file_name = "Text_Files/current_map.txt";

  QFile file(file_name);

  if(not file.open(QIODevice::ReadOnly)) 
    throw std::logic_error("Current map file doesn't exist");

  QTextStream in(&file);

  QString map_name = in.readLine();

  file.close();

  if (map_name.size() == 0)
    throw std::logic_error("No current map selected");

  file.setFileName(map_name);

  if(not file.open(QIODevice::ReadOnly)) 
    {
      QString msg = map_name + " doesn't exist";
      throw std::logic_error(msg.toStdString().c_str());
    }

  in >> width >> height >> scale;

  assert(width > 0 and height > 0 and scale > 0.0);

  map = new Cell * [height];

  for (size_t i = 0; i < height; ++i)
    {
      map[i] = new Cell[width];

      for (size_t j = 0; j < width; ++j)
        {
          char c = in.read(1).at(0).toLatin1();

          if (c == '\n')
            {
              --j;
              continue;
            }

          map[i][j].element = c;
          map[i][j].tag = 0;

          if (c == '.' or c == '*')
            ++num_cookies;
        }
    }
  file.close();
}

void Game_Board::draw(QPainter & painter)
{
  QPen pen = painter.pen();
  QBrush brush = painter.brush();

  for (size_t i = 0; i < height; ++i)
    for (size_t j = 0; j < width; ++j)
      {
        switch(map[i][j].element)
          {
          case '#':
            painter.fillRect(j * scale, i * scale, scale, scale, Qt::darkBlue);
            break;
          case '*':
            painter.setPen(Qt::darkBlue);
            painter.setBrush(Qt::darkBlue);
            painter.drawEllipse(QPoint(j * scale + scale / 2,
                                       i * scale + scale / 2),
                                10, 10);
            break;
          case '.':
            painter.setPen(Qt::darkBlue);
            painter.setBrush(Qt::darkBlue);
            painter.drawEllipse(QPoint(j * scale + scale / 2,
                                       i * scale + scale / 2),
                                2, 2);
            break;
          }
      }
  painter.setPen(pen);
  painter.setBrush(brush);
}

void Game_Board::destroy_map()
{
  if (map == nullptr)
    return;

  for (size_t i = 0; i < height; ++i)
    delete [] map[i];

  delete [] map;

  num_cookies = 0;
}

char & Game_Board::element_at(const size_t & i, const size_t & j)
{
  return map[i][j].element;
}

const size_t & Game_Board::get_width() const
{
  return width;
}

const size_t & Game_Board::get_height() const
{
  return height;
}

const real & Game_Board::get_scale() const
{
  return scale;
}

void Game_Board::tag(const size_t & i, const size_t & j, const int & value)
{
  map[i][j].tag |= value;
}

bool Game_Board::is_tagged(const size_t & i, const size_t & j,
                              const int & value) const
{
  return (map[i][j].tag & value) == value;
}

void Game_Board::untag(const size_t & i, const size_t & j, const int & value)
{
  map[i][j].tag &= ~value;
}

void Game_Board::reset_tag(const int & value)
{
  for (size_t i = 0; i < height; ++i)
    for (size_t j = 0; j < width; ++j)
      untag(i, j, value);
}

void Game_Board::reset_all_tags()
{
  for (size_t i = 0; i < height; ++i)
    for (size_t j = 0; j < width; ++j)
      map[i][j].tag = 0;
}

void Game_Board::eat(const size_t & i, const size_t & j)
{
  if (map[i][j].element == ' ')
    return;

  char c = map[i][j].element;

  map[i][j].element = ' ';
  --num_cookies;

  if (num_cookies == 0)
    {
      Telegram_Sender::get_instance().
        send_global_message(this, Pacman_Got_All_Cookies);
      return;
    }

  if (c == '*')
    {
      status = Counting_Time_For_Big_Cookie;
      current_time_big_cookie = 0;

      Telegram_Sender::get_instance().
        send_global_message(this, Pacman_Got_Big_Cookie);
    }
}

bool Game_Board::is_in_range(const size_t & i, const size_t & j) const
{
  return i < height and j < width;
}

Vector_2D Game_Board::position_in_map(const Vector_2D & position)
{
  int x = int(position.get_x() / SCALE);
  int y = int(position.get_y() / SCALE);

  return Vector_2D(x, y);
}

Vector_2D Game_Board::real_position(const Vector_2D & position)
{
  int x = position.get_x() * SCALE + SCALE / 2.0;
  int y = position.get_y() * SCALE + SCALE / 2.0;

  return Vector_2D(x, y);
}

void Game_Board::update(const real & dt)
{
  if (status == Default_Status)
    return;

  current_time_big_cookie += dt;

  if (current_time_big_cookie < Max_Time_For_Big_Cookie)
    return;

  current_time_big_cookie = 0;
  status = Default_Status;
  Telegram_Sender::get_instance().send_global_message(this,
                                                      Big_Cookie_Time_Over);
}

