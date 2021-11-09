NAME			= 	cub3D

SRCS_FILES		=	main.c\
					parsing/cb_check.c parsing/cb_utils.c parsing/ft_error.c parsing/ft_lst.c\
					parsing/get_tex_and_color.c parsing/gnl.c parsing/make_map.c parsing/parsing.c\
					utils/cb_init_main_struct.c utils/cb_malloc_x.c utils/cb_put_flat_map.c utils/cb_return_error.c\
					events/cb_handle_events.c events/cb_handle_keyboard.c\

SRCS_DIR		=	src/
HEADER			=	./inc/cub3d.h ./inc/colors.h ./inc/macos_keyboard.h ./src/libft/inc/libft.h\
					./src/minilibx/mlx.h ./src/minilibx/mlx_int.h ./src/minilibx/mlx_new_window.h\
					./src/minilibx/mlx_opengl.h ./src/minilibx/mlx_png.h


SRCS			= 	$(addprefix $(SRCS_DIR),$(SRCS_FILES))
OBJS			=	$(patsubst %.c,%.o,$(SRCS))

INCLUDES		=	-I./inc/ \
					-I./src/libft/ \
					-I./src/minilibx/

FRAMEWORK		=	-framework OpenGL -framework AppKit
CC				=	gcc
RM				=	rm -rfv
CFLAGS			=	-Wall -Wextra -Werror
LIBS			=	ar rcs

#COLORS
GREEN			=	\033[0;32m
RED				=	\033[0;31m
RESET			=	\033[0m

MLX				=	./src/minilibx/libmlx.a
LIB				=	./src/libft/libft.a

all:			$(NAME)

%.o:			%.c $(HEADER)
				$(CC) $(CFLAGS) $(INCLUDES) -c -g $< -o $@

$(NAME):		$(OBJS)
				$(MAKE) -C $(dir $(MLX))
				$(MAKE) -C $(dir $(LIB))
				@$(CC) $(INCLUDES) $(OBJS) $(LIB) $(MLX) -o $(NAME) $(FRAMEWORK)
				@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
				@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

clean:
				@make -C $(dir $(MLX)) clean
				@make -C $(dir $(LIB)) clean
				$(RM) $(OBJS)
				@echo "\033[36;1m\nCleaning succeed\n\033[0m"

fclean:			clean
				$(MAKE) fclean -C ./src/libft/
				$(MAKE) clean -C ./src/minilibx/
				$(RM) $(NAME)
				@echo "\033[32;1m\nAll created files were deleted\n\033[0m"

re:				fclean $(NAME)
				@echo "\033[35;1m\nRemake done\n\033[0m"

.PHONY:			all clean fclean re
