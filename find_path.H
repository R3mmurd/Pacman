/*
  Pacman remake

  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef FIND_PATh_H
# define FIND_PATh_H

# include <QList>

# include <game_board.H>

enum Path_Find_Type
{
  FPT_Breadth_First, FPT_Depth_First, Num_Path_Find_Type
};

class Find_Path
{
public:
  virtual QList<Vector_2D>
  find_path(const Vector_2D &, const Vector_2D &, const int &) = 0;
};

# endif // FIND_PATh_H

