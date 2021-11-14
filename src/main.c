#include "./../inc/cub3d.h"

float	degree_to_ratio(float degree) //todo пригодится
{
	return (degree * acos(-1.0) / 180);
}

void	rendering(t_main *data)
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

	data.map = &map;//todo пусть память выделятся на стеке
	data.win = &win;//todo пусть память выделятся на стеке
	data.plr = &plr;//todo пусть память выделятся на стеке
	cb_init_main_struct(&data);
	parsing(argc, argv[1], &data);
	rendering(&data);
	mlx_put_image_to_window(data.win->mlx_ptr, data.win->win_ptr, data.win->img_ptr, 0, 0);
	cb_handle_events(&data);
	mlx_loop(data.win->mlx_ptr);
}
