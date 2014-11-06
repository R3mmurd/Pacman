QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += Utilities

CONFIG += warn_off

HEADERS += \
    element.H \
    sprite.H \
    segment_follower.H \
    game_panel.H \
    game_map.H \
    pacman.H \
    image_buffer.H \
    sprite_factory.H \
    ghost.H \
    find_path.H \
    find_path_breadth_first.H \
    telegram.H \
    telegram_listener.H \
    telegram_sender.H \
    Utilities/def.H \
    Utilities/functions.H \
    Utilities/vector_2D.H \
    Utilities/time_manager.H \
    Utilities/singleton.H

SOURCES += \
    element.C \
    sprite.C \
    main.C \
    segment_follower.C \
    game_panel.C \
    game_map.C \
    pacman.C \
    sprite_factory.C \
    ghost.C \
    telegram.C \
    telegram_sender.C \
    Utilities/functions.C \
    Utilities/vector_2D.C \
    Utilities/time_manager.C \

RESOURCES += \
    images.qrc

OTHER_FILES += \
    Text_Files/map_1.txt \
    Text_Files/map_2.txt \
    Text_Files/current_map.txt \
    Text_Files/sprites.txt
