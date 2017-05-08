#  This file is part of Pacman game.
#  Copyright (C) 2014 by Alejandro J. Mujica

#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.

#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.

#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#  Any user request of this software, write to

#  Alejandro Mujica

#  aledrums@gmail.com

QMAKE_CXX = clang++

CONFIG += c++14

QT += core widgets multimedia

INCLUDEPATH += Utilities

HEADERS += \
    element.H \
    sprite.H \
    segment_follower.H \
    game_panel.H \
    pacman.H \
    image_buffer.H \
    sprite_factory.H \
    ghost.H \
    find_path.H \
    find_path_breadth_first.H \
    find_path_depth_first.H  \
    telegram.H \
    telegram_listener.H \
    telegram_sender.H \
    Utilities/def.H \
    Utilities/functions.H \
    Utilities/vector_2D.H \
    Utilities/singleton.H \
    game_board.H \
    audio.H

SOURCES += \
    element.C \
    sprite.C \
    main.C \
    segment_follower.C \
    game_panel.C \
    pacman.C \
    sprite_factory.C \
    ghost.C \
    telegram.C \
    telegram_sender.C \
    Utilities/functions.C \
    Utilities/vector_2D.C \
    game_board.C \
    audio.C

RESOURCES += \
    multimedia.qrc

OTHER_FILES += \
    Text_Files/map_1.txt \
    Text_Files/map_2.txt \
    Text_Files/current_map.txt \
    Text_Files/sprites.txt

