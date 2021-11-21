#include "../../inc/cub3d.h"
uint32_t	texture[64][4096];

void generate_some_textures(void)
{
	int texWidth = 64;
	int texHeight = 64;
	for(int x = 0; x < texWidth; x++)
		for(int y = 0; y < texHeight; y++)
		{
			int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
			//int xcolor = x * 256 / texWidth;
			int ycolor = y * 256 / texHeight;
			int xycolor = y * 128 / texHeight + x * 128 / texWidth;
			texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
			texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			texture[4][texWidth * y + x] = 256 * xorcolor; //xor green
			texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
			texture[6][texWidth * y + x] = 65536 * ycolor; //red gradient
			texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
		}
}

static void	draw_line(t_main *data, int x, t_points y_coordinates, int colorsss)
{
	int	color;
	int	texY;

	while (y_coordinates.draw_start < y_coordinates.draw_end)
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
		cb_mlx_pixel_put(data->win, x, y_coordinates.draw_start, color);
		y_coordinates.draw_start++;
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

static int	get_wall_color(t_lodev *lodev) //todo в идеале вместо color должна встать текстура
{
	int	color;

	color = 0;
	if (lodev->side == 'V') // todo Vertical wall
	{
		if (lodev->step_x < 0) // todo West
			color = GREEN;
		if (lodev->step_x > 0) // todo East
			color = MAROON;
	}
	else if (lodev->side == 'H') // todo Horizontal wall
	{
		if (lodev->step_y < 0) // todo North
			color = NAVY;
		if (lodev->step_y > 0) // todo South
			color = JAFFA;
	}
	return (color);
}

void	cb_render_cub(t_main *data)
{
	int			x;
	int			line_height;
	t_points	y_coordinates;
	generate_some_textures();
	int			buffer[WIN_HEIGHT][WIN_WIDTH];
	uint32_t 	color;

	x = 0;
	while (x < data->win->win_width)
	{
		calculate_ray_position_len_direction(data, x); //todo calculate ray position and direction
		calculate_step_and_side_dist(data); //todo calculate step and initial sideDist
		check_which_wall_was_hitted(data);
		data->lodev->line_height = (int)(data->win->win_height / data->lodev->perp_wall_dist);
		data->lodev->draw_start = -data->lodev->line_height / 2 + data->win->win_height / 2;
		if (data->lodev->draw_start < 0)
			data->lodev->draw_start = 0;
		data->lodev->draw_end = data->lodev->line_height / 2 + data->win->win_height / 2;
		if (data->lodev->draw_end >= data->win->win_height)
			data->lodev->draw_end = data->win->win_height - 1;

		char		tex_num = data->map->map[data->lodev->map_y][data->lodev->map_x] - 1; // расчеты текстурирования

		// вычисляем значение wallX
		double wallX; // где именно стена была поражена
		if (data->lodev->side == 'V')
			data->lodev->wallX = data->plr->y + data->lodev->perp_wall_dist * data->lodev->ray_dir_y;
		else
			data->lodev->wallX = data->plr->x + data->lodev->perp_wall_dist * data->lodev->ray_dir_x;
		data->lodev->wallX -= floor((data->lodev->wallX));
		// координата x текстуры
		data->lodev->texX = (int)(data->lodev->wallX * (double)(64));
		if (data->lodev->side == 0 && data->lodev->ray_dir_x > 0)
			data->lodev->texX = 64 - data->lodev->texX - 1;
		if (data->lodev->side == 1 && data->lodev->ray_dir_y < 0)
			data->lodev->texX = 64 - data->lodev->texX - 1;

		//Теперь, когда мы знаем координату x текстуры, мы знаем, что эта координата останется прежней,
		// потому что мы остаемся в той же вертикальной полосе экрана. Теперь нам нужен цикл в направлении y,
		// чтобы дать каждому пикселю вертикальной полосы правильную координату y текстуры, называемую texY.

		// Насколько увеличить координату текстуры на пиксель экрана
		data->lodev->step = 1.0 * 64 / data->lodev->line_height;
		// Начальная координата текстуры
		data->lodev->texPos = (data->lodev->draw_start - data->win->win_height / 2 + data->lodev->line_height / 2) * data->lodev->step;
		for(int y = data->lodev->draw_start; y < data->lodev->draw_end; y++)
		{
			// Приведем координату текстуры к целому числу и замаскируем с помощью (texHeight - 1) в случае переполнения
			int texY = (int)data->lodev->texPos & (64 - 1);
			data->lodev->texPos += data->lodev->step;
			color = texture[tex_num][64 * texY + data->lodev->texX];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(data->lodev->side == 1)
				color = (color >> 1) & 8355711;
			buffer[y][x] = color;
		}
//		while (data->lodev->draw_start < data->lodev->draw_end)
//		{
//			cb_mlx_pixel_put(data->win, x, data->lodev->draw_start, 8355711);
//			data->lodev->draw_start++;
//		}
		y_coordinates.draw_start = data->lodev->draw_start;
		y_coordinates.draw_end = data->lodev->draw_end;
		draw_line(data, x, y_coordinates, 0);
//		todo draw_line рисует вертикальную линию по X. Последний аргумент - INT, обозначающий цвет (текстуру)
		x++;
	}
}
