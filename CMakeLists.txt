cmake_minimum_required(VERSION 3.20)
project(Cub3D C)

set(CMAKE_C_STANDARD 99)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/libft/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/minilibx_mms/)

#FILE(GLOB SRC
#        "src/main.c"
#        "src/parsing/*.c")


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall")
add_executable(Cub3D src/parsing/ft_error.c src/parsing/parsing.c src/parsing/ft_lst.c src/parsing/get_tex_and_color.c src/parsing/make_map.c)

target_link_libraries (Cub3D ${CMAKE_CURRENT_SOURCE_DIR}/src/libft/libft.a)

