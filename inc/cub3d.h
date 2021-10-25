#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <sys/errno.h>
# include "../inc/colors.h"
# include "../inc/macos_keyboard.h"
# include "../src/libft/inc/libft.h"
# include "../src/minilibx_mms/mlx.h"

# define WIN_WIDTH 1152
# define WIN_HEIGHT 864

typedef struct	s_win //структура для окна
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*addr;
	int			line_l;
	int			bpp;
	int			en;
}	t_win;

typedef struct	s_point // структура для точки
{
	int			x;
	int			y;
}	t_point;

typedef struct	s_plr //структура для игрока и луча
{
	float		x;
	float		y;
	float		dir;
	float		start;
	float		end;
}	t_plr;

typedef struct	s_main // структура для всего вместе
{
	t_win		*win;
	t_plr		*plr;
	char		**map;
}	t_main;

//utils
void	*cb_malloc_x(size_t size);
int		cb_return_nbr(int return_value, char *message);
void	*cb_return_null(char *message);
t_main	*cb_init_main_struct(t_main *data);
int		cb_handle_events(t_win *win);

//parser


#endif
