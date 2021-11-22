#include "../../inc/cub3d.h"

void	calculate_ray_position_len_direction(t_main *data, int x_line)
{
	data->lodev->camera_x = 2 * (float)x_line / data->win->win_width - 1;
	data->lodev->ray_dir_x = data->plr->dir_x \
			- data->plr->plane_x * data->lodev->camera_x;
	data->lodev->ray_dir_y = data->plr->dir_y \
			- data->plr->plane_y * data->lodev->camera_x;
	data->lodev->map_x = (int)data->plr->x;
	data->lodev->map_y = (int)data->plr->y;
	data->lodev->delta_dist_x = fabsf(1 / data->lodev->ray_dir_x);
	data->lodev->delta_dist_y = fabsf(1 / data->lodev->ray_dir_y);
}

void	calculate_step_and_side_dist(t_main *data)
{
	if (data->lodev->ray_dir_x < 0)
	{
		data->lodev->step_x = -1;
		data->lodev->side_dist_x = (data->plr->x - data->lodev->map_x) \
				* data->lodev->delta_dist_x;
	}
	else
	{
		data->lodev->step_x = 1;
		data->lodev->side_dist_x = (data->lodev->map_x + 1.0 - data->plr->x) \
				* data->lodev->delta_dist_x;
	}
	if (data->lodev->ray_dir_y < 0)
	{
		data->lodev->step_y = -1;
		data->lodev->side_dist_y = (data->plr->y - data->lodev->map_y) \
				* data->lodev->delta_dist_y;
	}
	else
	{
		data->lodev->step_y = 1;
		data->lodev->side_dist_y = (data->lodev->map_y + 1.0 - data->plr->y) \
				* data->lodev->delta_dist_y;
	}
}

void	check_which_wall_was_hitted(t_main *data)
{
	data->lodev->flag_hit = 0;
	while (data->lodev->flag_hit == 0)
	{
		if (data->lodev->side_dist_x < data->lodev->side_dist_y)
		{
			data->lodev->side_dist_x += data->lodev->delta_dist_x;
			data->lodev->map_x += data->lodev->step_x;
			data->lodev->side = 'V';
		}
		else
		{
			data->lodev->side_dist_y += data->lodev->delta_dist_y;
			data->lodev->map_y += data->lodev->step_y;
			data->lodev->side = 'H';
		}
		if (data->map->map[data->lodev->map_y][data->lodev->map_x] == '1')
			data->lodev->flag_hit = 1;
	}
	if (data->lodev->side == 'V')
		data->lodev->perp_wall_dist = data->lodev->side_dist_x \
				- data->lodev->delta_dist_x;
	if (data->lodev->side == 'H')
		data->lodev->perp_wall_dist = data->lodev->side_dist_y \
				- data->lodev->delta_dist_y;
}

void	calculate_lowest_and_highest_pixel(t_main *data)
{
	t_lodev		*l;

	l = data->lodev;
	l->draw_start = -l->line_height / 2 + data->win->win_height / 2;
	if (l->draw_start < 0)
		l->draw_start = 0;
	l->draw_end = l->line_height / 2 + data->win->win_height / 2;
	if (l->draw_end >= data->win->win_height)
		l->draw_end = data->win->win_height - 1;
}

void	calculate_value_of_wall_x(t_main *data)
{
	t_lodev		*l;

	l = data->lodev;
	if (l->side == 'V')
		l->wall_x = data->plr->y + l->perp_wall_dist * l->ray_dir_y;
	else
		l->wall_x = data->plr->x + l->perp_wall_dist * l->ray_dir_x;
	l->wall_x -= floor((l->wall_x));
}
