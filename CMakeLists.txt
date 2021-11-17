cmake_minimum_required(VERSION 3.20)
project(Cub3D C)

set(CMAKE_C_STANDARD 99)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/libft/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/minilibx_mms/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/inc)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/minisrc/minilibx_mms)


FILE(GLOB SRC
        "src/main.c"
        "src/parsing/*.c"
        "src/utils/*.c"
        "src/events/*.c"
        "src/rendering/*.c")


#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall")
add_executable(Cub3D ${SRC})

target_link_libraries (Cub3D ${CMAKE_CURRENT_SOURCE_DIR}/src/libft/libft.a)
target_link_libraries (Cub3D ${CMAKE_CURRENT_SOURCE_DIR}/src/minilibx_mms/libmlx.dylib)

