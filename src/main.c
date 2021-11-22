#include "./../inc/cub3d.h"

static void	init_mlx(t_win *win)
{
	win->win_width = WIN_WIDTH;
	win->win_height = WIN_HEIGHT;
	win->mlx_ptr = mlx_init();
	if (win->mlx_ptr == NULL)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	win->win_ptr = mlx_new_window(win->mlx_ptr, win->win_width,
			win->win_height, "cub3D");
	if (win->win_ptr == NULL)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	win->img_ptr = mlx_new_image(win->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	win->addr = mlx_get_data_addr(win->img_ptr, &win->bpp, &win->line_length,
			&win->endian);
}

void	cb_rendering(t_main *data)
{
	cb_render_floor_ceiling(data);
	cb_render_cub(data);
	mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
		data->win->img_ptr, 0, 0);
}

int	main(int argc, char **argv)
{
	t_main	data;
	t_map	map;
	t_win	win;
	t_plr	plr;
	t_lodev	lodev;

	data.map = &map;
	data.win = &win;
	data.plr = &plr;
	data.lodev = &lodev;
	parsing(argc, argv[1], &data);
	cb_init_main_struct(&data);
	cb_rendering(&data);
	cb_handle_events(&data);
	mlx_loop(data.win->mlx_ptr);
}
