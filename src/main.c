#include "./../inc/cub3d.h"

void	cb_rendering(t_main *data)
{
	cb_render_floor_ceiling(data);
	cb_render_cub(data);
	cb_render_mini_map(data);
}

int	main(int argc, char **argv)
{
	t_main	data;
	t_map	map;
	t_win	win;
	t_plr	plr;

	data.map = &map;
	data.win = &win;
	data.plr = &plr;
	cb_init_main_struct(&data);
	parsing(argc, argv[1], &data);
	cb_handle_events(&data);
	cb_rendering(&data);
	mlx_put_image_to_window(data.win->mlx_ptr, data.win->win_ptr, data.win->img_ptr, 0, 0);
	mlx_loop(data.win->mlx_ptr);
}
