#include "./../inc/cub3d.h"

//void	cb_clear_all(t_main *data) // на случай если будем юзать malloc
//{
//	if (data->lodev)
//		free(data->lodev);
//	if (data->plr)
//		free(data->plr);
//	if (data->map)
//	{
//		ft_free_array(&(data->map->map));
//		ft_free_array(&(data->map->xpm));
//		free(data->map);
//	}
//}

void	cb_rendering(t_main *data)
{
	cb_render_floor_ceiling(data);
	cb_render_cub(data);
	cb_render_mini_map(data);
//	mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
//		data->txrs->north->img, 0, 0);
	mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
		data->win->img_ptr, 0, 0);
}

int	main(int argc, char **argv)
{
	t_main	data;
	//t_map	map;
	//t_win	win;
	//t_plr	plr;
	//t_lodev	lodev;

	//data.map = &map;
	//data.win = &win;
	//data.plr = &plr;
	//data.lodev = &lodev;
	cb_init_main_struct(&data);
	parsing(argc, argv[1], &data);
	cb_rendering(&data);
	cb_handle_events(&data);
//	mlx_loop_hook(data.win->mlx_ptr, cb_rendering, &data);//todo с ней отрисовка мерцает
	mlx_loop(data.win->mlx_ptr);
}
