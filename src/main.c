#include "./../inc/cub3d.h"

//todo DYNAMIC gcc ./src/main_bonus.c ./src/parsing/*.c ./src/utils/*.c ./src/rendering/*.c ./src/events/*.c ./src/libft/libft.a libmlx.dylib -o cub3D -g
//todo gcc ./src/main.c ./src/parsing/*.c ./src/utils/*.c ./src/rendering/*.c ./src/events/*.c ./src/libft/libft.a ./src/minilibx_opengl/libmlx.a -o cub3D -lmlx -framework OpenGL -framework AppKit -g

//void	cb_clear_all(t_main *data) // todo на случай если будем юзать malloc
//{
//	if (data->lodev)
//		free(data->lodev);
//	if (data->plr)
//		free(data->plr);
//	if (data->map)
//	{
//		if (data->map->map)
//			ft_free_array(&(data->map->map));
//		if (data->map->xpm)
//			ft_free_array(&(data->map->xpm));
//		free(data->map);
//	}
//}

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
	cb_init_main_struct(&data);
	parsing(argc, argv[1], &data);
	cb_rendering(&data);
	cb_handle_events(&data);
	mlx_loop(data.win->mlx_ptr);
}
