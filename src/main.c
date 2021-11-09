#include "./../inc/cub3d.h"

//static void	cd_init_mlx(t_main *data) // учитывает размер карты
//{
//	if (WIN_WIDTH >= data->map->width * data->zoom)
//		data->win->win_width = WIN_WIDTH;
//	else
//		data->win->win_width = data->map->width * data->zoom;
//	if (WIN_HEIGHT >= data->map->height * data->zoom)
//		data->win->win_height = WIN_HEIGHT;
//	else
//		data->win->win_height = data->map->height * data->zoom;
//	data->win->mlx_ptr = mlx_init();
//	if (data->win->mlx_ptr == NULL)
//	{
//		ft_putendl_fd(strerror(errno), STDERR_FILENO);
//		exit(EXIT_FAILURE);
//	}
//	data->win->win_ptr = mlx_new_window(data->win->mlx_ptr,
//			data->win->win_width, data->win->win_height, "cub3D");
//	if (data->win->win_ptr == NULL)
//	{
//		ft_putendl_fd(strerror(errno), STDERR_FILENO);
//		exit(EXIT_FAILURE);
//	}
//	data->win->img_ptr = mlx_new_image(data->win->mlx_ptr,
//			WIN_WIDTH, WIN_HEIGHT);
//	data->win->addr = mlx_get_data_addr(data->win->img_ptr, &data->win->bpp,
//			&data->win->line_length, &data->win->endian);
//}

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
	cb_render_2d(&data);
	mlx_put_image_to_window(data.win->mlx_ptr, data.win->win_ptr, data.win->img_ptr, 0, 0);
	cb_handle_events(&data); // ловит нажатие X-окна
	open_texture(&data);

//	mlx_key_hook(data.win->win_ptr, cb_handle_keyboard, &data); // ловит ESC & NUM± // TODO я убрал это гавно
	mlx_loop(data.win->mlx_ptr);
}
