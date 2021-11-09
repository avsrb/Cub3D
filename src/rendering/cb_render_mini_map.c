#include "../../inc/cub3d.h"

static void	print_rectangle(t_main *data, int start_x, int start_y, int color)
{
	int	y;
	int	x;

	y = start_y;
	while (y < data->zoom + start_y)
	{
		x = start_x;
		while (x < data->zoom + start_x)
		{
			my_mlx_pixel_put(data->win, x, y, color);
			x++;
		}
		y++;
	}
}

static void	cast_rays(t_main *data)
{
	t_plr	ray;
	int		ray_length;
	
	ray = *data->plr;
	while (ray.start <= ray.end)
	{
		ray.x = data->plr->x * data->zoom;
		ray.y = data->plr->y * data->zoom;
		ray_length = 0;
		while (data->map->map[(int)(ray.y / data->zoom)][(int)ray.x / data->zoom] != '1')
		{
			ray.x += cos(ray.start);
			ray.y += sin(ray.start);
			ray_length++;
			if (data->map->map[(int)(ray.y / data->zoom)][(int)ray.x / data->zoom] != '1')
				my_mlx_pixel_put(data->win, ray.x, ray.y, SILVER);
		}
		ray.start += M_PI_2 / WIN_WIDTH;
	}
}

static void	print_flat_map(t_main *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width && data->map->map[y][x] != '\0')
		{
			if (data->map->map[y][x] == '1')
				print_rectangle(data, x * data->zoom, y * data->zoom, MAROON);
			else if (data->map->map[y][x] == '0')
				print_rectangle(data, x * data->zoom, y * data->zoom, TEAL);
			else if (ft_isalpha(data->map->map[y][x]))
				print_rectangle(data, x * data->zoom, y * data->zoom, TEAL);
			x++;
		}
		y++;
	}
}

void	cb_render_mini_map(t_main *data)
{
	print_flat_map(data);
	my_mlx_pixel_put(data->win, data->plr->x * data->zoom,
			data->plr->y * data->zoom, AQUA);
	cast_rays(data);
}
