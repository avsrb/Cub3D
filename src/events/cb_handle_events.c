#include "../../inc/cub3d.h"

int	cb_terminate(t_main *data)
{
	mlx_clear_window(data->win->mlx_ptr, data->win->win_ptr);
	mlx_destroy_window(data->win->mlx_ptr, data->win->win_ptr);
	exit(0);
}

int	cb_handle_events(t_main *data)
{
	mlx_hook(data->win->win_ptr, 17, 0, cb_terminate, data);
	return (0);
}
