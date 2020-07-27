/*
  Pacman remake

  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef FIND_PATH_BREADTH_FIRST_H
# define FIND_PATH_BREADTH_FIRST_H

# include <QQueue>

# include <find_path.H>

class Find_Path_Breadth_First :
    public Singleton<Find_Path_Breadth_First>,
    public Find_Path
{
  void insert_in_queue(const Vector_2D & p,
                       QQueue<QList<Vector_2D>> & path_queue,
                       QList<Vector_2D> * ptr_curr_path = nullptr)
  {
    QList<Vector_2D> new_path;

    if (ptr_curr_path != nullptr)
      new_path = *ptr_curr_path;

    new_path.append(p);

    path_queue.enqueue(std::move(new_path));
  }

public:

  QList<Vector_2D> find_path(const Vector_2D & src, const Vector_2D & tgt,
                             const int & tag)
  {
    RESET_ALL_TAGS;

    QQueue<QList<Vector_2D>> path_queue;

    QList<Vector_2D> current_path;

    insert_in_queue(src, path_queue);

    while (not path_queue.empty())
      {
        current_path = path_queue.dequeue();

        Vector_2D & p = current_path.last();

        if (CELL(p.get_y(), p.get_x()) == '#')
          continue;

        if (IS_TAGGED(p.get_y(), p.get_x(), tag))
          continue;

        if (p == tgt)
          {
            RESET_TAG(tag);
            return current_path;
          }

        TAG(p.get_y(), p.get_x(), tag);

        insert_in_queue(Vector_2D(p.get_x() - 1, p.get_y()), path_queue,
                        &current_path);
        insert_in_queue(Vector_2D(p.get_x() + 1, p.get_y()), path_queue,
                        &current_path);
        insert_in_queue(Vector_2D(p.get_x(), p.get_y() + 1), path_queue,
                        &current_path);
        insert_in_queue(Vector_2D(p.get_x(), p.get_y() - 1), path_queue,
                        &current_path);
      }

    current_path.clear();

    return current_path;
  }
};

# endif // FIND_PATH_BREADTH_FIRST_H

