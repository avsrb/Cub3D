NAME			= 	cub3D

SRCS			=	./src/main.c \
					$(wildcard ./src/parsing/*.c) \
					$(wildcard ./src/rendering/*.c) \
					$(wildcard ./src/utils/*.c) \
					$(wildcard ./src/events/*.c)

OBJS			=	$(SRCS:.c=.o)

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

clean:
				$(MAKE) clean -C ./src/libft/
				$(RM) $(OBJS)
				@echo "\033[36;1m\nCleaning succeed\n\033[0m"

fclean:			clean
				$(MAKE) fclean -C ./src/libft/
				$(MAKE) clean -C ./src/minilibx_mms/
				$(RM) libmlx.dylib
				$(RM) $(NAME)
				@echo "\033[32;1m\nAll created files were deleted\n\033[0m"

re:				fclean $(NAME)
				@echo "\033[35;1m\nRemake done\n\033[0m"

.PHONY:			all clean fclean re