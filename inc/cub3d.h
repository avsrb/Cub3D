#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <sys/errno.h>
# include <stdbool.h>
# include "../inc/colors.h"
# include "../inc/macos_keyboard.h"
# include "../src/libft/inc/libft.h"
# include "../src/minilibx_mms/mlx.h"

# define WIN_WIDTH 1152
# define WIN_HEIGHT 864

typedef struct	s_win //структура для окна
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	void		*addr;
	int			win_width;
	int			win_height;
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

typedef struct	s_lst
{
	char			*val;
	struct s_lst	*next;
}			t_lst;

typedef struct	s_map
{
	char		**map;
	char		**xpm;
	int			floor;
	int			cilling;
	int			width;
	int			height;
	bool		param_done;
	t_lst		*map_l;
}		t_map;

typedef struct	s_main // структура для всего вместе
{
	t_win		*win;
	t_plr		*plr;
	t_map		*map;
}	t_main;

//utils
void	*cb_malloc_x(size_t size);
int		cb_return_nbr(int return_value, char *message);
void	*cb_return_null(char *message);
t_main	*cb_init_main_struct(t_main *data);

//events & keys
int		cb_handle_events(t_win *win);
int		cb_terminate(t_win *win);
int		cb_handle_keyboard(int key, t_main *data);

//parser
int		gnl(int fd, char **line);
void	ft_lstdelone(t_lst *lst);
void	ft_lstclear(t_lst **lst);
void	ft_lstadd_back(t_lst **head, t_lst *new);
t_lst	*ft_lstnew(char *content);
void	ft_error(char *str);
int	parsing(int ac, char *file, t_main *all);

//get_tex_and_color
void	get_tex_and_color(char *str, t_map *m);

// make_map
void	make_map(t_map *data);
char	*spacecutter(char *str);


#endif
