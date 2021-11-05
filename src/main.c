#include "./../inc/cub3d.h"

//void	set_player_direction(float *dir, char c)
//{
//	if (c == 'N')
//		*dir = 0;
//	else if (c == 'E')
//		*dir = 0.25f;
//	else if (c == 'S')
//		*dir = 0.5f;
//	else if (c == 'W')
//		*dir = 0.75f;
//}

int	main(int argc, char **argv)
{
	t_main	data;
	
	cb_init_main_struct(&data);
	parsing(argc, argv[1], &data);
	cb_put_flat_map(&data);
	mlx_put_image_to_window(data.win->mlx_ptr, data.win->win_ptr, data.win->img_ptr, 0, 0);
	cb_handle_events(&data); // ловит нажатие X-окна
//	mlx_key_hook(data.win->win_ptr, cb_handle_keyboard, &data); // ловит ESC & NUM± // TODO я убрал это гавно
	mlx_loop(data.win->mlx_ptr);
}
