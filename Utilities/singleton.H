/*
  This file contains a reusable and generic implementation of the Singleton
  Pattern.
  Copyright (C) 2012, 2013, 2014, 2015, 2016 by Alejandro J. Mujica

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
# ifndef SINGLETON_H
# define SINGLETON_H

# include <memory>

/** Generic Singleton.
 *
 *  This class was designed in order to being reused for any class which 
 *  requires only one instance.
 *
 *  @param T Base class.
 *
 *  Usage example:
 *
 *  \code{.cpp}
 *  class MySingletonClass : public Singleton<MySingletonClass>
 *  {
 *    friend class Singleton<MySingletonClass>;
 *
 *    // If you need default constructor, make it protected.
 *  protected:
 *    MySingletonClass() { }
 *
 *    // Any attributes or methods;
 *  };
 *
 *  MySingletonClass * ptr_instance = MySingletonClass::get_ptr_instance();
 *
 *  MySingletonClass & instance = MySingletonClass::get_instance();
 *  \endcode
 *
 *  @author: Alejandro J. Mujica
 */         
template <typename T>
class Singleton
{
  static std::unique_ptr<Singleton<T>> instance;

protected:
  Singleton()
  {
    // Empty
  }

  Singleton(const Singleton<T> &) = delete;

  Singleton & operator = (const Singleton<T> &) = delete;

public:

  virtual ~Singleton()
  {
    // Empty
  }

  /** Get a pointer to instance.
   *
   *  @return A pointer to instance.
   */
  static T * get_ptr_instance()
  {
    if (instance.get() == nullptr)
      instance = std::unique_ptr<Singleton<T>>(new T());

    return static_cast<T *>(instance.get());
  }

  /** Get a reference to instance.
   *
   *  @return A reference to instance.
   */
  static T & get_instance()
  {
    return *get_ptr_instance();
  }
};

template <typename T>
std::unique_ptr<Singleton<T>> Singleton<T>::instance =
std::unique_ptr<Singleton<T>>(nullptr);

# endif // SINGLETON_H

