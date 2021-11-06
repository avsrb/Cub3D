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
# define DEBUG

typedef struct	s_win
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	void		*addr;
	int			win_width;
	int			win_height;
	int			line_length;
	int			bpp;
	int			endian;
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
	float		player_size;
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
	int			ceiling;
	int			width;
	int			height;
	bool		param_done;
	bool		map_done;
	t_lst		*map_l;
}		t_map;

typedef struct	s_main // структура для всего вместе
{
	t_win		*win;
	t_plr		*plr;
	t_map		*map;
	int			zoom;
}	t_main;

//utils
void	my_mlx_pixel_put(t_win *win, int x, int y, int color);
void	*cb_malloc_x(size_t size);
int		cb_return_nbr(int return_value, char *message);
void	*cb_return_null(char *message);
void	cb_init_main_struct(t_main *data);
void	cb_put_flat_map(t_main *data);

//events & keys
int		cb_handle_events(t_main *data);
int		cb_handle_keyboard(int key, t_main *data);
int		cb_terminate(t_main *data);

//parser
int		gnl(int fd, char **line);
void	ft_lstdelone(t_lst *lst);
void	ft_lstclear(t_lst **lst);
void	ft_lstadd_back(t_lst **head, t_lst *new);
t_lst	*ft_lstnew(char *content);
void	ft_error(char *str);
int		cb_strchr(const char *str, int c);
int		parsing(int ac, char *file, t_main *all);
void	init(t_map *m);
char	*spacecutter(char *str);

int		check_wall(char **map, int y, int x);
int		check_double_player(t_map *m);
void	check_map(t_map *m);
void	check_simbol(t_lst *map_l);
int		check_file(int ac, char *file);

void	get_tex_and_color(char *str, t_map *m);

// make_map
void	make_map(t_map *data);
char	*spacecutter(char *str);


#endif
