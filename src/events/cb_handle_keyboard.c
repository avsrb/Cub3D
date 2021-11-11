#include "../../inc/cub3d.h"

//void    shift_plane(t_main *data) // меняет угол обзора
//{
//    double  tmp;

//    tmp = tan(90 * M_PI / 360);
//    data->plr->planeX = -data->plr->dirY * tmp;
//    data->plr->planeY = data->plr->dirX * tmp;
//}

//void    shift_plane(t_main *data) // меняет угол обзора
//{
//    double  tmp;

//    tmp = tan(data->plr->dir * M_PI / 360);
//    data->plr->start = -data->plr->end * tmp;
//    data->plr->end = data->plr->start * tmp;
//}

static void	handle_arrows(int key, t_main *data)
{
	if (key == ARROW_LEFT)
	{
		//mlx_clear_window(data->win->mlx_ptr, data->win->win_ptr);
		data->plr->dir -= 0.05;
		data->plr->start = data->plr->dir - M_PI_4;
		data->plr->end = data->plr->dir + M_PI_4;
		//shift_plane(data);
		rendering(data);
	}
	if (key == ARROW_RIGHT)
	{
		//mlx_clear_window(data->win->mlx_ptr, data->win->win_ptr);
		data->plr->dir += 0.05;
		data->plr->start = data->plr->dir - M_PI_4;
		data->plr->end = data->plr->dir + M_PI_4;
		//shift_plane(data);
		rendering(data);
	}
	mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
		data->win->img_ptr, 0, 0);
}

static void	handle_ws_keys(int key, t_main *data)
{
	if (key == MAIN_PAD_W && (data->map->map[(int)((data->plr->y)
				- (1 / data->plr->step_size))][(int)data->plr->x] != '1'))
	{
		//mlx_clear_window(data->win->mlx_ptr, data->win->win_ptr);
		data->plr->y -= (1 / data->plr->step_size);
		rendering(data);
	}
	if (key == MAIN_PAD_S && (data->map->map[(int)(data->plr->y
				+ (1 / data->plr->step_size))][(int)data->plr->x] != '1'))
	{
		//mlx_clear_window(data->win->mlx_ptr, data->win->win_ptr);
		data->plr->y += (1 / data->plr->step_size);
		rendering(data);
	}
	mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
		data->win->img_ptr, 0, 0);
}

static void	handle_ad_keys(int key, t_main *data)
{
	if (key == MAIN_PAD_A && (data->map->map[(int)data->plr->y]
			[(int)(data->plr->x - (1 / data->plr->step_size))] != '1'))
	{
		//mlx_clear_window(data->win->mlx_ptr, data->win->win_ptr);
		data->plr->x -= (1 / data->plr->step_size);
		rendering(data);
	}
	if (key == MAIN_PAD_D && (data->map->map[(int)data->plr->y]
			[(int)(data->plr->x + (1 / data->plr->step_size))] != '1'))
	{
		//mlx_clear_window(data->win->mlx_ptr, data->win->win_ptr);
		data->plr->x += (1 / data->plr->step_size);
		rendering(data);
	}
	mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
		data->win->img_ptr, 0, 0);
}

int	cb_handle_keyboard(int key, t_main *data)
{
	if (key == MAIN_PAD_ESC)
		cb_terminate(data);
	if (key == MAIN_PAD_W || key == MAIN_PAD_S)
		handle_ws_keys(key, data);
	if (key == MAIN_PAD_A || key == MAIN_PAD_D)
		handle_ad_keys(key, data);
	if (key == ARROW_RIGHT || key == ARROW_LEFT)
		handle_arrows(key, data);
	return (0);
}
