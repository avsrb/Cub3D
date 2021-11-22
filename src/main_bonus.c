#include "./../inc/cub3d.h"

void	cb_rendering(t_main *data)
{
	cb_render_floor_ceiling(data);
	cb_render_cub(data);
	cb_render_mini_map(data);
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
