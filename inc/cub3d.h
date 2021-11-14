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

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define FOV 60
# define ROTATION_STEP 0.10F
# define STEP 0.20F

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

typedef struct	s_plr
{
	float		x;
	float		y;
	float		plane_x;
	float		plane_y;
	float		dir_x;
	float		dir_y;
	float		angle;
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
	t_lst		*map_l;
	int			floor;
	int			ceiling;
	int			width;
	int			height;
	bool		param_done;
	bool		map_done;
}		t_map;


typedef struct	s_main
{
	t_win		*win;
	t_plr		*plr;
	t_map		*map;
	int			zoom;
}	t_main;

//utils
void	*cb_malloc_x(size_t size);
int		cb_return_nbr(int return_value, char *message);
void	*cb_return_null(char *message);
void	cb_init_main_struct(t_main *data);

float	degree_to_ratio(float degree);

//rendering
void	my_mlx_pixel_put(t_win *win, int x, int y, int color);
void	rendering(t_main *data);
void	cb_render_floor_ceiling(t_main *data);
void	cb_render_cub(t_main *data);
void	cb_render_mini_map(t_main *data);

//events & keys
int		cb_handle_events(t_main *data);
int		cb_handle_keyboard(int key, t_main *data);
void	cb_handle_ad_keys(int key, t_main *data);
void	cb_handle_ws_keys(int key, t_main *data);
void	cb_handle_arrows(int key, t_main *data);
int		cb_terminate(t_main *data);

//parsing
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
