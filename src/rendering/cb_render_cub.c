#include "../../inc/cub3d.h"

static void	draw_line(t_main *data, int x)
{
	int	color;
	int	texY;

	while (data->lodev->draw_start < data->lodev->draw_end)
	{
		texY = (int) data->lodev->texPos & (64 - 1);
		data->lodev->texPos += data->lodev->step;
		if (data->lodev->side == 'H')
		{
			if (data->lodev->step_y == -1)
				color = data->txrs->west->matrix[data->lodev->texX][texY];
			else
				color = data->txrs->east->matrix[data->lodev->texX][texY];
		}
		else
		{
			if (data->lodev->step_x == -1)
				color = data->txrs->north->matrix[data->lodev->texX][texY];
			else
				color = data->txrs->south->matrix[data->lodev->texX][texY];
		}
		cb_mlx_pixel_put(data->win, x, data->lodev->draw_start, color);
		data->lodev->draw_start++;
	}
}

static void	calculate_ray_position_len_direction(t_main *data, int x_line)
{
	data->lodev->camera_x = 2 * (float)x_line / data->win->win_width - 1;//todo x-coordinate in camera space
	data->lodev->ray_dir_x = data->plr->dir_x
		- data->plr->plane_x * data->lodev->camera_x;
	data->lodev->ray_dir_y = data->plr->dir_y
		- data->plr->plane_y * data->lodev->camera_x;
	data->lodev->map_x = (int)data->plr->x; // todo //which box of the map we're in
	data->lodev->map_y = (int)data->plr->y;
	data->lodev->delta_dist_x = fabsf(1 / data->lodev->ray_dir_x); //todo length of ray from current position to next x or y-side
	data->lodev->delta_dist_y = fabsf(1 / data->lodev->ray_dir_y);
}

static void	calculate_step_and_side_dist(t_main *data)
{
	if (data->lodev->ray_dir_x < 0)
	{
		data->lodev->step_x = -1;
		data->lodev->side_dist_x = (data->plr->x - data->lodev->map_x)
			* data->lodev->delta_dist_x;
	}
	else
	{
		data->lodev->step_x = 1;
		data->lodev->side_dist_x = (data->lodev->map_x + 1.0 - data->plr->x)
			* data->lodev->delta_dist_x;
	}
	if (data->lodev->ray_dir_y < 0)
	{
		data->lodev->step_y = -1;
		data->lodev->side_dist_y = (data->plr->y - data->lodev->map_y)
			* data->lodev->delta_dist_y;
	}
	else
	{
		data->lodev->step_y = 1;
		data->lodev->side_dist_y = (data->lodev->map_y + 1.0 - data->plr->y)
			* data->lodev->delta_dist_y;
	}
}

static void	check_which_wall_was_hitted(t_main *data)
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
	if (data->lodev->side == 'V') // == 0
		data->lodev->perp_wall_dist = data->lodev->side_dist_x
			- data->lodev->delta_dist_x;
	if (data->lodev->side == 'H')
		data->lodev->perp_wall_dist = data->lodev->side_dist_y
			- data->lodev->delta_dist_y;
}

void	calculate_lowest_and_highest_pixel(t_main *data)
{
	data->lodev->draw_start = -data->lodev->line_height / 2 + data->win->win_height / 2;
	if (data->lodev->draw_start < 0)
		data->lodev->draw_start = 0;
	data->lodev->draw_end = data->lodev->line_height / 2 + data->win->win_height / 2;
	if (data->lodev->draw_end >= data->win->win_height)
		data->lodev->draw_end = data->win->win_height - 1;
}

void	calculate_value_of_wallX(t_main *data)
{
	if (data->lodev->side == 'V')
		data->lodev->wallX = data->plr->y + data->lodev->perp_wall_dist * data->lodev->ray_dir_y;
	else
		data->lodev->wallX = data->plr->x + data->lodev->perp_wall_dist * data->lodev->ray_dir_x;
	data->lodev->wallX -= floor((data->lodev->wallX));
}

void	cb_render_cub(t_main *data)
{
	int		x;

	x = 0;
	while (x < data->win->win_width)
	{
		calculate_ray_position_len_direction(data, x);
		calculate_step_and_side_dist(data);
		check_which_wall_was_hitted(data);
		data->lodev->line_height = (int)(data->win->win_height / data->lodev->perp_wall_dist);
		calculate_lowest_and_highest_pixel(data);
		calculate_value_of_wallX(data);
		data->lodev->texX = (int)(data->lodev->wallX * (double)(64));
		if (data->lodev->side == 0 && data->lodev->ray_dir_x > 0)
			data->lodev->texX = 64 - data->lodev->texX - 1;
		if (data->lodev->side == 1 && data->lodev->ray_dir_y < 0)
			data->lodev->texX = 64 - data->lodev->texX - 1;
		data->lodev->step = 1.0 * 64 / data->lodev->line_height;
		data->lodev->texPos = (data->lodev->draw_start - data->win->win_height / 2 + data->lodev->line_height / 2) * data->lodev->step;
		draw_line(data, x);
		x++;
	}
}
