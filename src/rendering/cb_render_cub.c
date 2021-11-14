#include "../../inc/cub3d.h"

static void draw_line(t_main *data, int x, int drawStart, int drawEnd, int color)
{
	while (drawStart < drawEnd)
	{
		cb_mlx_pixel_put(data->win, x, drawStart, color);
		drawStart++;
	}
}

void init_lodev_stuct(t_lodev *lodev)
{
	lodev->step_x = 0;
	lodev->step_y = 0;
	lodev->camera_x = 0;
	lodev->rayDirX = 0;
	lodev->rayDirY = 0;
	lodev->map_x = 0;
	lodev->map_y = 0;
	lodev->sideDist_x = 0;
	lodev->sideDist_y = 0;
	lodev->deltaDist_x = 0;
	lodev->deltaDist_y = 0;
	lodev->perpWallDist = 0;
	lodev->flag_hit = 0;
	lodev->side = '0';
}

void	cb_render_cub(t_main *data)
{
	int		x;
	t_lodev	lodev;

	init_lodev_stuct(&lodev);
	x = 0;
	while (x < data->win->win_width)
	{
		//calculate ray position and direction
		lodev.camera_x = 2 * (float)x / data->win->win_width - 1; //x-coordinate in camera space
		lodev.rayDirX = data->plr->dir_x - data->plr->plane_x * lodev.camera_x;
		lodev.rayDirY = data->plr->dir_y - data->plr->plane_y * lodev.camera_x;

		//which box of the map we're in
		lodev.map_x = (int)data->plr->x;
		lodev.map_y = (int)data->plr->y;

		//length of ray from current position to next x or y-side
		lodev.deltaDist_x = fabsf(1 / lodev.rayDirX);
		lodev.deltaDist_y = fabsf(1 / lodev.rayDirY);


		lodev.flag_hit = 0; //was there a wall hit?
		//calculate step and initial sideDist
		if (lodev.rayDirX < 0)
		{
			lodev.step_x = -1;
			lodev.sideDist_x = (data->plr->x - lodev.map_x) * lodev.deltaDist_x;
		}
		else
		{
			lodev.step_x = 1;
			lodev.sideDist_x = (lodev.map_x + 1.0 - data->plr->x) * lodev.deltaDist_x;
		}
		if (lodev.rayDirY < 0)
		{
			lodev.step_y = -1;
			lodev.sideDist_y = (data->plr->y - lodev.map_y) * lodev.deltaDist_y;
		}
		else
		{
			lodev.step_y = 1;
			lodev.sideDist_y = (lodev.map_y + 1.0 - data->plr->y) * lodev.deltaDist_y;
		}
		//perform dist
//side - какая сторона (NS или EW) задета лучем? N/S (по у) = 'H', E/W  (по х) = 'V'
		while (lodev.flag_hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if(lodev.sideDist_x < lodev.sideDist_y)
			{
				lodev.sideDist_x += lodev.deltaDist_x;
				lodev.map_x += lodev.step_x;
				lodev.side = 'V';
			}
			else
			{
				lodev.sideDist_y += lodev.deltaDist_y;
				lodev.map_y += lodev.step_y;
				lodev.side = 'H';
			}
			if(data->map->map[lodev.map_y][lodev.map_x] == '1')
				lodev.flag_hit = 1;
		}
		if (lodev.side == 'V')
			lodev.perpWallDist = (lodev.sideDist_x - lodev.deltaDist_x);
		if (lodev.side == 'H')
			lodev.perpWallDist = (lodev.sideDist_y - lodev.deltaDist_y);

		//Calculate height of line to draw on screen
		// printf("lodev.perpWallDist: %f\n", lodev.perpWallDist), exit(0);
		int lineHeight = (int)(data->win->win_height / lodev.perpWallDist);

		//calculate lowest and higest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + data->win->win_height / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + data->win->win_height / 2;
		if(drawEnd >= data->win->win_height)
			drawEnd = data->win->win_height - 1;


		//give x and y sides different color
		if (lodev.side == 'H')
			draw_line(data, x, drawStart, drawEnd, NAVY);
		if (lodev.side == 'V')
			draw_line(data, x, drawStart, drawEnd, MAROON);
		x++;
	}
}
