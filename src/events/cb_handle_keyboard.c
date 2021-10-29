#include "../../inc/cub3d.h"

static int	handle_window_resize(int key, t_main *data)
{
	if (key == NUM_PAD_PLUS)
	{
		data->win->win_height += 86;
		data->win->win_width += 115;
	}
	if (key == NUM_PAD_MINUS)
	{
		if (data->win->win_height > 86 && data->win->win_width > 115)
		{
			data->win->win_height -= 86;
			data->win->win_width -= 115;
		}
	}
	mlx_destroy_window(data->win->mlx_ptr, data->win->win_ptr);
	data->win->mlx_ptr = mlx_init();
	data->win->win_ptr = mlx_new_window(data->win->mlx_ptr, data->win->win_width,
			data->win->win_height, "cub3D");
	//cb_put_map(data);//todo
	cb_handle_events(data->win);
	mlx_key_hook(data->win->win_ptr, &cb_handle_keyboard, data);
	mlx_loop(data->win->mlx_ptr);
	return (0);
}

int	cb_handle_keyboard(int key, t_main *data)
{
	if (key == MAIN_PAD_ESC)
		cb_terminate(data->win);
	else if (key == NUM_PAD_MINUS || key == NUM_PAD_PLUS)
		handle_window_resize(key, data);
	return (0);
}