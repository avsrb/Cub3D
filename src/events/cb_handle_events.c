#include "../../inc/cub3d.h"

int	cb_terminate(t_main *data)
{
	(void)data;
//	mlx_clear_window(data->win->mlx_ptr, data->win->win_ptr);//todo не знаю зачем это
//	mlx_destroy_window(data->win->mlx_ptr, data->win->win_ptr);//todo не знаю зачем это
	if (data->win->win_ptr)
		mlx_destroy_window(data->win->mlx_ptr, data->win->win_ptr);//todo редакци Тараса
	exit(0);
}

int	cb_handle_events(t_main *data)
{
	mlx_hook(data->win->win_ptr, 2, 0, cb_handle_keyboard, data);
	mlx_hook(data->win->win_ptr, 17, 0, cb_terminate, data);
	return (0);
}
