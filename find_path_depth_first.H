/*
  Pacman remake

  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef FIND_PATH_DEPTH_FIRST_H
# define FIND_PATH_DEPTH_FIRST_H

# include <find_path.H>

class Find_Path_Depth_First :
    public Singleton<Find_Path_Depth_First>,
    public Find_Path
{
  bool find_path_rec(const Vector_2D & src, const Vector_2D & tgt,
                     const int & tag, QList<Vector_2D> & path)
  {
    if (IS_TAGGED(src.get_y(), src.get_x(), tag) or
        CELL(src.get_y(), src.get_x()) == '#')
      return false;

    TAG(src.get_y(), src.get_x(), tag);

    path.append(src);

    if (src == tgt)
      return true;

    Vector_2D p;

    p.set_x(src.get_x());
    p.set_y(src.get_y() - 1);

    if (not IS_TAGGED(p.get_y(), p.get_x(), tag) and
        CELL(p.get_y(), p.get_x()) != '#')
      if (find_path_rec(p, tgt, tag, path))
        return true;

    p.set_x(src.get_x() + 1);
    p.set_y(src.get_y());

    if (not IS_TAGGED(p.get_y(), p.get_x(), tag) and
        CELL(p.get_y(), p.get_x()) != '#')
      if (find_path_rec(p, tgt, tag, path))
        return true;


    p.set_x(src.get_x());
    p.set_y(src.get_y() + 1);

    if (not IS_TAGGED(p.get_y(), p.get_x(), tag) and
        CELL(p.get_y(), p.get_x()) != '#')
      if (find_path_rec(p, tgt, tag, path))
        return true;

    p.set_x(src.get_x() - 1);
    p.set_y(src.get_y());

    if (not IS_TAGGED(p.get_y(), p.get_x(), tag) and
        CELL(p.get_y(), p.get_x()) != '#')
      if (find_path_rec(p, tgt, tag, path))
        return true;

    path.takeLast();

    return false;
  }

public:

  QList<Vector_2D> find_path(const Vector_2D & src, const Vector_2D & tgt,
                             const int & tag)
  {
    RESET_TAG(tag);

    QList<Vector_2D> path;

    path.append(src);

    TAG(src.get_y(), src.get_x(), tag);

    Vector_2D p;

    p.set_x(src.get_x());
    p.set_y(src.get_y() - 1);

    if (not IS_TAGGED(p.get_y(), p.get_x(), tag) and
        CELL(p.get_y(), p.get_x()) != '#')
      if (find_path_rec(p, tgt, tag, path))
        return path;

    p.set_x(src.get_x() + 1);
    p.set_y(src.get_y());

    if (not IS_TAGGED(p.get_y(), p.get_x(), tag) and
        CELL(p.get_y(), p.get_x()) != '#')
      if (find_path_rec(p, tgt, tag, path))
        return path;

    p.set_x(src.get_x());
    p.set_y(src.get_y() + 1);

    if (not IS_TAGGED(p.get_y(), p.get_x(), tag) and
        CELL(p.get_y(), p.get_x()) != '#')
      if (find_path_rec(p, tgt, tag, path))
        return path;

    p.set_x(src.get_x() - 1);
    p.set_y(src.get_y());

    if (not IS_TAGGED(p.get_y(), p.get_x(), tag) and
        CELL(p.get_y(), p.get_x()) != '#')
      if (find_path_rec(p, tgt, tag, path))
        return path;

    path.clear();

    return path;
  }
};

# endif // FIND_PATH_DEPTH_FIRST_H

