#include "../../inc/cub3d.h"

static void draw_line(t_main *data, int x, int drawStart, int drawEnd, int color)
{
	while (drawStart < drawEnd)
	{
		my_mlx_pixel_put(data->win, x, drawStart, color);
		drawStart++;
	}
}

void	cb_render_cub(t_main *data)
{
	int	x;

	x = 0;
	while (x < data->win->win_width)
	{
		//calculate ray position and direction
		float cameraX = 2 * (float)x / data->win->win_width - 1; //x-coordinate in camera space
		float rayDirX = data->plr->dir_x + data->plr->plane_x * cameraX;
		float rayDirY = data->plr->dir_y + data->plr->plane_y * cameraX;

		//which box of the map we're in
		int mapX = (int)data->plr->x;
		int mapY = (int)data->plr->y;

		//length of ray from current position to next x or y-side
		float sideDistX;
		float sideDistY;
		float deltaDistX = fabsf(1 / rayDirX);
		float deltaDistY = fabsf(1 / rayDirY);

		float perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (data->plr->x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - data->plr->x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (data->plr->y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->plr->y) * deltaDistY;
		}
		//perform dist
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if(data->map->map[mapY][mapX] == '1')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		//Calculate height of line to draw on screen
		// printf("perpWallDist: %f\n", perpWallDist), exit(0);
		int lineHeight = (int)(data->win->win_height / perpWallDist);

		//calculate lowest and higest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + data->win->win_height / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + data->win->win_height / 2;
		if(drawEnd >= data->win->win_height)
			drawEnd = data->win->win_height - 1;

		//choose wall color
		int	color = MAROON;
		//give x and y sides different color
		if (side == 1)
			color = BLUE;
		draw_line(data, x, drawStart, drawEnd, color);
		x++;
	}
}
