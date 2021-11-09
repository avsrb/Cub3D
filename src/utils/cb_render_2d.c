#include "../../inc/cub3d.h"

// помещает игрока на карту в виде квадрата размером 1\5 от размера квадрата сетки карты
//static void	print_player(t_main *data, int start_x, int start_y, int color)
//{
//	int	y;
//	int	x;

//	y = start_y;
//	while (y < data->plr->player_size + start_y)
//	{
//		x = start_x;
//		while (x < data->plr->player_size + start_x)
//		{
//			my_mlx_pixel_put(data->win, x, y, color);
//			x++;
//		}
//		y++;
//	}
//}

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

//static void	cast_ray(t_main *data)//todo кастуем 1 луч
//{
//	data->plr->dir = 0;
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

int	select_color(t_main *data, double tex_posy, char direct)
{
	int	tex_posx;

	tex_posx = 0;
	if (direct == 'h')
		tex_posx = ((int)(data->ray->x2
				- ((int)(data->ray->x2 / SIZE) *SIZE))) / 2;
	else if (direct == 'v')
		tex_posx = ((int)(data->ray->y2
				- ((int)(data->ray->y2 / SIZE) *SIZE))) / 2;
	return (*(int *)(data->ray->texture->addr
	+ (int)tex_posy * data->ray->texture->ll
	+ tex_posx * (data->ray->texture->bpp / 8)));
}

void	select_texture(t_main *data, char *direct)
{
	if ((int)(data->ray->y1 / SIZE) == (int)(data->ray->y2 / SIZE))
	{
		if ((int)(data->ray->x1 / SIZE) < (int)(data->ray->x2 / SIZE))
			data->ray->texture = data->textures->west;
		else
			data->ray->texture = data->textures->east;
		*direct = 'v';
	}
	else if ((int)(data->ray->y1 / SIZE) == (int)(data->ray->x2 / SIZE))
	{
		if ((int)(data->ray->y1 / SIZE) < (int)(data->ray->y2 / SIZE))
			data->ray->texture = data->textures->north;
		else
			data->ray->texture = data->textures->south;
		*direct = 'h';
	}
}

double	dtr(double degree)
{
	return (degree * acos(-1.0) / 180);
}

void	calc_raypos(t_main *data)
{
	data->ray->x1 = data->plr->x + data->ray->dis * cos(data->ray->angle);
	data->ray->y1 = data->plr->y + data->ray->dis * sin(data->ray->angle);
}

void	put_texture(t_main *data)
{
	double	tex_posy;
	char	direct;

	data->ray->dis *= cos(data->plr->dir - data->ray->angle);
	data->ray->height = (int)(data->focus * SIZE / data->ray->dis);
	data->ray->scale = 64 / (double)data->ray->height;
	data->ray->start = (WIN_HEIGHT - data->ray->height) / 2;
	data->ray->end = data->ray->start + data->ray->height;
	tex_posy = 0;
	direct = 'h';
	select_texture(data, &direct);
	while (data->ray->start < data->ray->end)
	{
		if (data->ray->start >= 0 && data->ray->start < WIN_HEIGHT
		&& data->ray->nbr >= 0 && data->ray->nbr < WIN_WIDTH)
			my_mlx_pixel_put(data->win->win_ptr, data->ray->nbr, data->ray->start,
							 select_color(data, tex_posy, direct));
		tex_posy += data->ray->scale;
		data->ray->start++;
	}
}

void	rays(t_main *data, int ray_len)
{
	(void)ray_len;
	while (data->ray->nbr < WIN_WIDTH)
	{
		data->ray->dis = 0;
		while (++data->ray->dis < 2048)
		{
			calc_raypos(data);
			if (((int)data->ray->y1 / SIZE >= 0
			&& (int)data->ray->y1 / SIZE < data->map->height)
			&& ((int)data->ray->x1 / SIZE >= 0
			&& (int)data->ray->x1 / SIZE < data->map->height)
			&& data->map->map[(int)data->ray->y1 / SIZE][(int)data->ray->x1 / SIZE] == '1')
			{
				put_texture(data);
				break ;
			}
			data->ray->x1 = data->ray->x2;
			data->ray->y1 = data->ray->y2;
		}
		data->ray->nbr++;
		data->ray->angle += dtr(FOW / WIN_WIDTH);
	}
}

void	cb_make_3d(t_main *data, int ray_len)
{
	data->ray->angle = data->ray->angle - dtr(33.0);
	data->ray->nbr = 0;
	data->ray->x1 = 0;
	data->ray->x1 = 0;
	rays(data, ray_len);
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
				my_mlx_pixel_put(data->win, ray.x, ray.y, WHITE);
		}
		cb_make_3d(data, ray_length); // todo должна нариосвать псевдо3D
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
				print_rectangle(data, x * data->zoom, y * data->zoom, INDIGO);
			else if (data->map->map[y][x] == '0')
				print_rectangle(data, x * data->zoom, y * data->zoom, data->map->ceiling);
			else if (ft_isalpha(data->map->map[y][x]))
				print_rectangle(data, x * data->zoom, y * data->zoom, data->map->ceiling);
			x++;
		}
		y++;
	}
}

void	cb_render_2d(t_main *data)
{
	print_flat_map(data);
	//print_player(data, data->plr->x * data->zoom, data->plr->y * data->zoom, AQUA);//todo см. выше
	my_mlx_pixel_put(data->win, data->plr->x, data->plr->y, AQUA); //todo помещает игрока на карту в виде точки
	cast_rays(data);
}
