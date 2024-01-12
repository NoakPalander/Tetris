cmake_minimum_required(VERSION 3.28)
project(tetris CXX)

add_subdirectory(${CMAKE_SOURCE_DIR}/ext)

set(TETRIS_MODULES
    src/tetris/tetris.ixx
    src/tetris/events.ixx
    src/tetris/tetromino.ixx
    src/settings.ixx
    src/tetris/direction.ixx
    src/tetris/type.ixx
    src/tetris/color.ixx
    src/utils/utils.ixx
    src/utils/map.ixx
    src/tetris/bag.ixx
    src/tetris/turn.ixx
    src/tetris/board.ixx)

add_executable(tetris src/main.cpp ${TETRIS_MODULES})
target_sources(tetris PUBLIC FILE_SET CXX_MODULES FILES ${TETRIS_MODULES})
target_compile_features(tetris PRIVATE cxx_std_23)
target_link_libraries(tetris PRIVATE fmt::fmt sfml-graphics)