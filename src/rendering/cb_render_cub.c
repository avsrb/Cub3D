#include "../../inc/cub3d.h"

static void	draw_line(t_main *data, int x)
{
	int	color;
	int	tex_y;

	while (data->lodev->draw_start < data->lodev->draw_end + 1)
	{
		tex_y = (int) data->lodev->tex_pos & (64 - 1);
		data->lodev->tex_pos += data->lodev->step;
		if (data->lodev->side == 'H')
		{
			if (data->lodev->step_y == -1)
				color = data->txrs->west->matrix[data->lodev->tex_x][tex_y];
			else
				color = data->txrs->east->matrix[data->lodev->tex_x][tex_y];
		}
		else
		{
			if (data->lodev->step_x == -1)
				color = data->txrs->north->matrix[data->lodev->tex_x][tex_y];
			else
				color = data->txrs->south->matrix[data->lodev->tex_x][tex_y];
		}
		cb_mlx_pixel_put(data->win, x, data->lodev->draw_start, color);
		data->lodev->draw_start++;
	}
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
		data->lodev->line_height = (int)(data->win->win_height \
				/ data->lodev->perp_wall_dist);
		calculate_lowest_and_highest_pixel(data);
		calculate_value_of_wall_x(data);
		data->lodev->tex_x = (int)(data->lodev->wall_x * (double)(64));
		if (data->lodev->side == 0 && data->lodev->ray_dir_x > 0)
			data->lodev->tex_x = 64 - data->lodev->tex_x - 1;
		if (data->lodev->side == 1 && data->lodev->ray_dir_y < 0)
			data->lodev->tex_x = 64 - data->lodev->tex_x - 1;
		data->lodev->step = 1.0 * 64 / data->lodev->line_height;
		data->lodev->tex_pos = (data->lodev->draw_start - data->win->win_height \
				/ 2 + data->lodev->line_height / 2) * data->lodev->step;
		draw_line(data, x);
		x++;
	}
}
