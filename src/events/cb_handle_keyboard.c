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
	data->win->win_ptr = mlx_new_window(data->win->mlx_ptr,
			data->win->win_width, data->win->win_height, "cub3D");
	cb_render_mini_map(data);
	mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
		data->win->img_ptr, 0, 0);
	cb_handle_events(data);
	mlx_loop(data->win->mlx_ptr);
	return (0);
}

static void	handle_arrows(int key, t_main *data)
{
	if (key == ARROW_LEFT)
	{
		mlx_clear_window(data->win->mlx_ptr, data->win->win_ptr);
		data->plr->dir -= 0.05;
		data->plr->start = data->plr->dir - M_PI_4;
		data->plr->end = data->plr->dir + M_PI_4;
		cb_render_mini_map(data);
	}
	if (key == ARROW_RIGHT)
	{
		mlx_clear_window(data->win->mlx_ptr, data->win->win_ptr);
		data->plr->dir += 0.05;
		data->plr->start = data->plr->dir - M_PI_4;
		data->plr->end = data->plr->dir + M_PI_4;
		cb_render_mini_map(data);
	}
	mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
		data->win->img_ptr, 0, 0);
}

static void	handle_ws_keys(int key, t_main *data)
{
	if (key == MAIN_PAD_W && (data->map->map[(int)((data->plr->y)
				- (1 / data->plr->step_size))][(int)data->plr->x] != '1'))
	{
		mlx_clear_window(data->win->mlx_ptr, data->win->win_ptr);
		data->plr->y -= (1 / data->plr->step_size);
		cb_render_mini_map(data);
	}
	if (key == MAIN_PAD_S && (data->map->map[(int)(data->plr->y
				+ (1 / data->plr->step_size))][(int)data->plr->x] != '1'))
	{
		mlx_clear_window(data->win->mlx_ptr, data->win->win_ptr);
		data->plr->y += (1 / data->plr->step_size);
		cb_render_mini_map(data);
	}
	mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
		data->win->img_ptr, 0, 0);
}

static void	handle_ad_keys(int key, t_main *data)
{
	if (key == MAIN_PAD_A && (data->map->map[(int)data->plr->y]
			[(int)(data->plr->x - (1 / data->plr->step_size))] != '1'))
	{
		mlx_clear_window(data->win->mlx_ptr, data->win->win_ptr);
		data->plr->x -= (1 / data->plr->step_size);
		cb_render_mini_map(data);
	}
	if (key == MAIN_PAD_D && (data->map->map[(int)data->plr->y]
			[(int)(data->plr->x + (1 / data->plr->step_size))] != '1'))
	{
		mlx_clear_window(data->win->mlx_ptr, data->win->win_ptr);
		data->plr->x += (1 / data->plr->step_size);
		cb_render_mini_map(data);
	}
	mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
		data->win->img_ptr, 0, 0);
}

int	cb_handle_keyboard(int key, t_main *data)
{
	if (key == MAIN_PAD_ESC)
		cb_terminate(data);
	if (key == NUM_PAD_MINUS || key == NUM_PAD_PLUS)
		handle_window_resize(key, data);
	if (key == MAIN_PAD_W || key == MAIN_PAD_S)
		handle_ws_keys(key, data);
	if (key == MAIN_PAD_A || key == MAIN_PAD_D)
		handle_ad_keys(key, data);
	if (key == ARROW_RIGHT || key == ARROW_LEFT)
		handle_arrows(key, data);
	return (0);
}
