cmake_minimum_required(VERSION 3.20)
project(Cub3D C)

set(CMAKE_C_STANDARD 99)
#SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY /Users/mshmelly/21/Cub3D)
SET(CMAKE_C_FLAGS "-lz")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/libft/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/minilibx/)
include(${CMAKE_CURRENT_SOURCE_DIR}/src/minilibx/mlx.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/inc)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/minisrc/minilibx)


FILE(GLOB SRC
        "src/main.c"
        "src/parsing/*.c"
        "src/utils/*.c"
        "src/events/*.c")


#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall")
add_executable(Cub3D ${SRC} )

target_link_libraries (Cub3D ${CMAKE_CURRENT_SOURCE_DIR}/src/libft/libft.a)
target_link_libraries (Cub3D ${CMAKE_CURRENT_SOURCE_DIR}/src/minilibx/libmlx.a)

