#include "../../inc/cub3d.h"

int	cb_handle_keyboard(int key, t_main *data)
{
	if (key == MAIN_PAD_ESC)
		cb_terminate(data);
	if (key == MAIN_PAD_W || key == MAIN_PAD_S)
		cb_handle_ws_keys(key, data);
	if (key == MAIN_PAD_A || key == MAIN_PAD_D)
		cb_handle_ad_keys(key, data);
	if (key == ARROW_RIGHT || key == ARROW_LEFT)
		cb_handle_arrows(key, data);
	return (0);
}

int	cb_terminate(t_main *data)
{
	mlx_destroy_window(data->win->mlx_ptr, data->win->win_ptr);
	exit(0);
}

int	cb_handle_events(t_main *data)
{
	mlx_hook(data->win->win_ptr, 2, 0, cb_handle_keyboard, data);
	mlx_hook(data->win->win_ptr, 17, 0, cb_terminate, data);
	return (0);
}
