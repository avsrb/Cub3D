NAME			= 	cub3D

SRCS			=	./src/main.c \
					$(wildcard ./src/parser/*.c) \
					$(wildcard ./src/utils/*.c)

OBJS			=	$(SRCS:.c=.o)

HEADERS			=	-I./inc/ -I.src/minilibx_opengl/ -I.src/libft/inc/

CC				=	gcc

RM				=	rm -rfv

CFLAGS			=	-Wall -Wextra -Werror

LXFLAGS			=	-lmlx -framework OpenGL -framework AppKit

LIBS			=	./src/minilibx_opengl/libmlx.a ./src/libft/libft.a

all:			$(NAME)

%.o:			%.c
				$(CC) $(CFLAGS) -c -g $< -o $@ $(HEADERS)

$(NAME):		$(OBJS) ./inc/cub3d.h ./src/minilibx_opengl/mlx.h ./src/libft/inc/libft.h
				cd ./src/libft/ && $(MAKE)
				cd ./src/minilibx_opengl/ && $(MAKE)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) $(LXFLAGS) $(HEADERS)

clean:
				$(MAKE) clean -C ./src/libft/
				$(RM) $(OBJS)
				@echo "\033[36;1m\nCleaning succeed\n\033[0m"

fclean:			clean
				$(MAKE) fclean -C ./src/libft/
				$(MAKE) clean -C ./src/minilibx_opengl/
				$(RM) $(NAME)
				@echo "\033[32;1m\nAll created files were deleted\n\033[0m"

re:				fclean $(NAME)
				@echo "\033[35;1m\nRemake done\n\033[0m"

.PHONY:			all clean fclean re