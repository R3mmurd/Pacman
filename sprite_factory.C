/*
  Pacman remake

  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <stdexcept>

# include <sprite_factory.H>

# include <pacman.H>
# include <ghost.H>

# include <find_path_breadth_first.H>
# include <find_path_depth_first.H>

Sprite * Sprite_Factory::build_sprite(QStringList & attributes)
{
  int type = attributes.at(0).toInt();

  switch(type)
    {
    case ST_Pacman:
      {
        std::unique_ptr<Pacman> ptr_pacman(new Pacman);

        int num_images = attributes.at(1).toInt();

        QString bn = ":/images/pacman/";

        for (int i = 0; i < num_images; ++i)
          {
            QString name = bn + QString::number(i + 1);
            ptr_pacman->add_image(name);
          }

        int x0 = attributes.at(2).toInt();

        int y0 = attributes.at(3).toInt();

        real speed = attributes.at(4).toFloat();

        Vector_2D init_pos(x0, y0);

        ptr_pacman->init(init_pos, speed);

        Sprite * ret_val = ptr_pacman.get();

        ptr_pacman.release();

        return ret_val;
      }

    break;

    case ST_Ghost:
      {
        real prop = attributes.at(7).toFloat();

        std::unique_ptr<Ghost> ptr_ghost(new Ghost(prop));

        int num_images = attributes.at(1).toInt();

        QString bn = ":/images/tux/";
        bn.append(attributes.at(2));
        bn.append("/");

        for (int i = 0; i < num_images; ++i)
          {
            QString name = bn + QString::number(i + 1);
            ptr_ghost->add_image(name);
          }

        int x0 = attributes.at(3).toInt();

        int y0 = attributes.at(4).toInt();

        real speed = attributes.at(5).toFloat();

        Vector_2D init_pos(x0, y0);

        int algo = attributes.at(6).toInt();

        switch(algo)
          {
          case FPT_Breadth_First:
            ptr_ghost->find_path_algorithm() =
              Find_Path_Breadth_First::get_ptr_instance();
            break;
          case FPT_Depth_First:
            ptr_ghost->find_path_algorithm() =
              Find_Path_Depth_First::get_ptr_instance();
            break;
          }

        ptr_ghost->init(init_pos, speed);

        Sprite * ret_val = ptr_ghost.get();

        ptr_ghost.release();

        return ret_val;
      }

    break;

    default:
      throw std::logic_error("Error in sprite type");
    }

  return nullptr;
}

