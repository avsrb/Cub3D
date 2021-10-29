#include "./../inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_main	*data;
	
	(void)argv;
	if (argc != 2)
		return(cb_return_nbr(1, "Error: Invalid arguments"));
	data = (t_main *)malloc(sizeof(t_main));
	if (!data || !data->map)
		return(cb_return_nbr(1, strerror(errno)));
	data = cb_init_main_struct(data); // инит структур win и plr в data + запуск окна 
//	parsing(argc, argv[1], data->map);
	cb_handle_events(data->win); // ловит нажатие X-окна
	mlx_key_hook(data->win->win_ptr, &cb_handle_keyboard, data); // ловит ESC & NUM±
	mlx_loop(data->win->mlx_ptr);
}
