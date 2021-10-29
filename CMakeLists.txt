cmake_minimum_required(VERSION 3.20)
project(Cub3D C)

set(CMAKE_C_STANDARD 99)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/libft/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/minilibx_mms/)
#include(${CMAKE_CURRENT_SOURCE_DIR}/src/minilibx_mms/mlx.h)

FILE(GLOB SRC
        "src/main.c"
        "src/parsing/*.c"
        "src/utils/*.c"
        "src/events/*.c")

#set(LIBMLX_SOURCES
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#        )
#add_library(mlx STATIC ${LIBMLX_SOURCES})
#target_link_libraries(mlx my ${X11_LIBRARIES})


#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall")
add_executable(Cub3D ${SRC}
        src/minilibx_mms/mlx_clear_window.c\
        src/minilibx_mms/mlx_draw.c\
        src/minilibx_mms/mlx_hook.c\
        src/minilibx_mms/mlx_hooks.c\
        src/minilibx_mms/mlx_image.c\
        src/minilibx_mms/mlx_image_data.c\
        src/minilibx_mms/mlx_init.c\
        src/minilibx_mms/mlx_int_get_visual.c\
        src/minilibx_mms/mlx_int_hooks.c\
        src/minilibx_mms/mlx_loop.c\
        src/minilibx_mms/mlx_mouse.c\
        src/minilibx_mms/mlx_shm_image.c\
        src/minilibx_mms/mlx_util.c\
        src/minilibx_mms/mlx_window.c\)

target_link_libraries (Cub3D ${CMAKE_CURRENT_SOURCE_DIR}/src/libft/libft.a)
target_link_libraries (Cub3D ${CMAKE_CURRENT_SOURCE_DIR}/src/minilibx_mms)

