#include "./../inc/cub3d.h"

void	lodev(t_opt *opt)
{
	float posX = (float)opt->plr->pos_x, posY = (float)opt->plr->pos_y;
	// printf("x: %f	y: %f\n",  posX, posY); exit(0);
	// float posX = 22, posY = 12;
	float	dirX = cos(opt->plr->angle * 0.5);
	float	dirY = sin(opt->plr->angle * 0.5);
	// float dirX = -1, dirY = 0;
	float planeX = 0, planeY = ANGLE * 0.5;
	float	w = RES_X;
	float	h = RES_Y;
	int x;

	x = 0;
	while (x < w)
	{
		//calculate ray position and direction
		float cameraX = 2 * x / w - 1; //x-coordinate in camera space
		float rayDirX = dirX + planeX * cameraX;
		float rayDirY = dirY + planeY * cameraX;

		//which box of the map we're in
		int mapX = (int)posX;
		int mapY = (int)posY;

		//length of ray from current position to next x or y-side
		float sideDistX;
		float sideDistY;
		float deltaDistX = (rayDirX == 0) ? 1e30 : ft_abs_f(1 / rayDirX);
		float deltaDistY = (rayDirY == 0) ? 1e30 : ft_abs_f(1 / rayDirY);

		float perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		//perform dist
		while(hit == 0)
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
			// printf("mapX: %d	mapY: %d\n", mapX, mapY);
			// printf("stepX: %d	stepY: %d	deltaDistX: %f	deltaDistY: %f	sideDistX: %f	sideDistY: %f\n",
			// 	stepX, stepY, deltaDistX, deltaDistY, sideDistX, sideDistY);
			//Check if ray has hit a wall
			// if(worldMap[mapX][mapY] > 0)
			// 	hit = 1;
			if(opt->map->canvas[mapX][mapY] == '1')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		//Calculate height of line to draw on screen
		// printf("perpWallDist: %f\n", perpWallDist), exit(0);
		int lineHeight = (int)(h / perpWallDist);
		// printf("lineHeight: %d\n", lineHeight), exit(0);

		//calculate lowest and higest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if(drawEnd >= h)
			drawEnd = h - 1;

		//choose wall color
		int	color = COLOR_RED;
		//give x and y sides different brightness
		if (side == 1)
			color = color / 2;
		draw_line(opt, x, drawStart, drawEnd, color);
		x++;
	}
} 