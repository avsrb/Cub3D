NAME			=	cub3D

NAME_BONUS		=	cub3D_bonus

SRCS			=	./src/main.c \
					./src/parsing/cb_check.c					./src/parsing/cb_utils.c \
					./src/parsing/ft_error.c					./src/parsing/ft_lst.c \
					./src/parsing/get_tex_and_color.c			./src/parsing/gnl.c \
					./src/parsing/make_map.c					./src/parsing/parsing.c \
					./src/utils/cb_init_main_struct.c			./src/utils/cb_malloc_x.c \
					./src/utils/cb_return_error.c				./src/utils/ft_degree_to_ratio.c \
					./src/events/cb_handle_events.c				./src/events/cb_handle_keyboard.c \
					./src/rendering/cb_mlx_pixel_put.c			./src/rendering/cb_render_cub.c \
					./src/rendering/cb_render_floor_ceiling.c \

SRCS_BONUS		=	./src/main_bonus.c \
					./src/parsing/cb_check.c					./src/parsing/cb_utils.c \
					./src/parsing/ft_error.c					./src/parsing/ft_lst.c \
					./src/parsing/get_tex_and_color.c			./src/parsing/gnl.c \
					./src/parsing/make_map.c					./src/parsing/parsing.c \
					./src/utils/cb_init_main_struct.c			./src/utils/cb_malloc_x.c \
					./src/utils/cb_return_error.c				./src/utils/ft_degree_to_ratio.c \
					./src/events/cb_handle_events.c				./src/events/cb_handle_keyboard.c \
					./src/rendering/cb_mlx_pixel_put.c			./src/rendering/cb_render_cub.c \
					./src/rendering/cb_render_floor_ceiling.c \
					./src/rendering/cb_render_mini_map.c \

OBJS			=	$(SRCS:.c=.o)

OBJS_BONUS		=	$(SRCS_BONUS:.c=.o)

HEADERS			=	-I./inc/ -I.src/minilibx_mms/ -I.src/libft/inc/

CC				=	gcc

RM				=	rm -rfv

CFLAGS			=	-Wall -Wextra -Werror

LIBS			=	./libmlx.dylib ./src/libft/libft.a

all:			$(NAME)

%.o:			%.c
				$(CC) $(CFLAGS) -c -g $< -o $@ $(HEADERS)

$(NAME):		$(OBJS) ./inc/cub3d.h
				$(MAKE) -C src/libft/
				$(MAKE) -C src/minilibx_mms/
				cp src/minilibx_mms/libmlx.dylib .
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

bonus:			$(NAME_BONUS)

$(NAME_BONUS):	$(OBJS_BONUS) ./inc/cub3d.h
				$(MAKE) -C src/libft/
				$(MAKE) -C src/minilibx_mms/
				cp src/minilibx_mms/libmlx.dylib .
				$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS) $(LIBS)

clean:
				$(MAKE) clean -C ./src/libft/
				$(RM) $(OBJS) $(OBJS_BONUS)
				@echo "\033[36;1m\nCleaning succeed\n\033[0m"

fclean:			clean
				$(MAKE) fclean -C ./src/libft/
				$(MAKE) clean -C ./src/minilibx_mms/
				$(RM) libmlx.dylib
				$(RM) $(NAME) $(NAME_BONUS)
				@echo "\033[32;1m\nAll created files were deleted\n\033[0m"

re:				fclean $(NAME)
				@echo "\033[35;1m\nRemake done\n\033[0m"

rebonus:		fclean $(NAME_BONUS)
				@echo "\033[35;1m\nRemake with bonus part done\n\033[0m"

.PHONY:			all clean fclean re rebonus bonus