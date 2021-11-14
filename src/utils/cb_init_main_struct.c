#include "../../inc/cub3d.h"

static void	init_mlx(t_win *win)
{
	win->win_width = WIN_WIDTH;
	win->win_height = WIN_HEIGHT;
	win->mlx_ptr = mlx_init();
	if (win->mlx_ptr == NULL)
	{
//		free(win->mlx_ptr); //todo зачем фришить если она не выделилась
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	win->win_ptr = mlx_new_window(win->mlx_ptr, win->win_width,
			win->win_height, "cub3D");
	if (win->win_ptr == NULL)
	{
//		free(win->win_ptr);//todo зачем фришить если она не выделилась
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	win->img_ptr = mlx_new_image(win->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	win->addr = mlx_get_data_addr(win->img_ptr, &win->bpp, &win->line_length,
								&win->endian);
}

static void	init_player(t_main *data)
{
	data->plr->x = 0.0F;
	data->plr->y = 0.0F;
	data->plr->plane_x = 0.0F;
	data->plr->plane_y = 0.0F;
	data->plr->dir_x = 0.0F;
	data->plr->dir_y = 0.0F;
	data->plr->angle = 0.0F;
}

static void	init_map(t_map *m)
{
	int	i;

	i = -1;
	m->param_done = false;
	m->map_done = false;
	m->map = NULL;
	m->floor = -1;
	m->ceiling = -1;
	m->width = 0;
	m->height = 0;
	m->map_l = NULL;
	m->xpm = malloc(sizeof(char *) * 4);
	if (!m->xpm)
		ft_error(NULL);
	while (++i < 5)
		m->xpm[i] = NULL;
}

void	cb_init_main_struct(t_main *data)
{
	data->zoom = 8;
//	data->win = cb_malloc_x(sizeof(t_win));
	init_mlx(data->win);
//	data->plr = cb_malloc_x(sizeof(t_plr));
	init_player(data);
//	data->map = cb_malloc_x(sizeof(t_map));
	init_map(data->map);
}
