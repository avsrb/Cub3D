#include "../../inc/cub3d.h"

static void	print_rectangle(t_main *data, int start_x, int start_y, int color)
{
	int	y;
	int	x;

	y = start_y;
	while (y < 21 + start_y)
	{
		x = start_x;
		while (x < 21 + start_x)
		{
			mlx_pixel_put(data->win->mlx_ptr, data->win->win_ptr, x, y, color);
			x++;
		}
		y++;
	}
}

void	cb_put_flat_map(t_main *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map->map[y])
	{
		x = 0;
		//while (x < data->map->width && worldMap[y][x] != '\0')
		while (data->map->map[y][x])//&& data->map->map[y][x] != '\0')
		{
			//if (worldMap[y][x] == '1')
			if (data->map->map[y][x] == '1')
				print_rectangle(data, x * data->zoom, y * data->zoom, MAROON);
			else if (data->map->map[y][x] == '0')
				print_rectangle(data, x * data->zoom, y * data->zoom, WHITE);
			else if (ft_isalpha(data->map->map[y][x]))
				print_rectangle(data, x * data->zoom, y * data->zoom, WHITE);
			x++;
		}
		y++;
	}
	print_rectangle(data, data->plr->x * data->zoom, data->plr->y * data->zoom, BLUE);;
}
