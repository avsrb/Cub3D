#include "../../inc/cub3d.h"

static void	my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char	*dst;

	dst = win->addr + (y * win->line_length + x * (win->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	print_player(t_main *data, int start_x, int start_y, int color)
{
	int	y;
	int	x;

	y = start_y;
	while (y < data->plr->player_size + start_y)
	{
		x = start_x;
		while (x < data->plr->player_size + start_x)
		{
			my_mlx_pixel_put(data->win, x, y, color);
			x++;
		}
		y++;
	}
}

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

//static void	cast_ray(t_main *data)
//{
//	data->plr->dir = 0.5f; // это рандомное значение. Как правильно определить направление луча я ХЗ
//	t_plr ray = *data->plr;
	
//	ray.x *= data->zoom;
//	ray.y *= data->zoom;
//	while (data->map->map[(int)(ray.y / data->zoom)][(int)(ray.x / data->zoom)] != '1')
//	{
//		ray.x += cos(ray.dir);
//		ray.y += sin(ray.dir);
//		my_mlx_pixel_put(data->win, ray.x, ray.y, WHITE);
//	}
//}

static void	cast_rays(t_main *data)
{
	data->plr->dir = 0.5f; // это рандомное значение. Как правильно определить направление луча я ХЗ
	
	t_plr	ray;
	
	ray = *data->plr; // задаем координаты и направление луча равными координатам игрока
	ray.start = ray.dir - M_PI_4; // начало веера лучей
	ray.end = ray.dir + M_PI_4; // край веера лучей
	while (ray.start <= ray.end)
	{
		ray.x = data->plr->x * data->zoom; // каждый раз возвращаемся в точку начала
		ray.y = data->plr->y * data->zoom;
		while (data->map->map[(int)(ray.y / data->zoom)][(int)(ray.x / data->zoom)] != '1')
		{
			ray.x += cos(ray.start);
			ray.y += sin(ray.start);
			my_mlx_pixel_put(data->win, ray.x, ray.y, WHITE);
		}
		ray.start += M_PI_2 / WIN_WIDTH; // делю на количество лучей;
	}
}

void	cb_put_flat_map(t_main *data)
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
				print_rectangle(data, x * data->zoom, y * data->zoom, INDIGO);
			else if (data->map->map[y][x] == '0')
				print_rectangle(data, x * data->zoom, y * data->zoom, data->map->ceiling);
			else if (ft_isalpha(data->map->map[y][x]))
				print_rectangle(data, x * data->zoom, y * data->zoom, data->map->ceiling);
			x++;
		}
		y++;
	}
	print_player(data, data->plr->x * data->zoom, data->plr->y * data->zoom, AQUA);
	cast_rays(data);
}
