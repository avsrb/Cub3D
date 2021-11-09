#include "../../inc/cub3d.h"

void	cb_render_floor_ceiling(t_main *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->win->win_height / 2)
	{
		j = -1;
		while (++j < data->win->win_width)
			my_mlx_pixel_put(data->win, j, i, data->map->ceiling);
	}
	i = data->win->win_height / 2 - 1;
	while (++i < data->win->win_height)
	{
		j = -1;
		while (++j < data->win->win_width)
			my_mlx_pixel_put(data->win, j, i, data->map->floor);
	}
}
