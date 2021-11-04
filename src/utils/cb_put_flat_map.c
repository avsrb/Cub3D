#include "../../inc/cub3d.h"

static void	my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char	*dst;

	dst = win->addr + (y * win->line_length + x * (win->bpp / 8));
	*(unsigned int*)dst = color;
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
				print_rectangle(data, x * data->zoom, y * data->zoom, MAROON);
			else if (data->map->map[y][x] == '0')
				print_rectangle(data, x * data->zoom, y * data->zoom, WHITE);
			else if (ft_isalpha(data->map->map[y][x]))
				print_rectangle(data, x * data->zoom, y * data->zoom, WHITE);
			x++;
		}
		y++;
	}
	print_player(data, data->plr->x * data->zoom, data->plr->y * data->zoom, BLUE);
}
