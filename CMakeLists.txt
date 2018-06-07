cmake_minimum_required(VERSION 3.7)
project(progbase3)

set(CMAKE_C_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${progbase3_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(src)

include_directories(include)
include_directories(include/collections)

include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR})



set(SOURCE_FILES main.c include/macros.h include/render.h src/render.c include/collections/vector.h include/collections/sector.h include/collections/player.h include/collections/game.h src/data_loader.c include/data_loader.h src/player_func.c include/player_func.h)


add_executable(progbase3 ${SOURCE_FILES})

target_link_libraries(progbase3 ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES})
