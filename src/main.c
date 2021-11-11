#include "./../inc/cub3d.h"

void draw_line(t_main *data, int x, int drawStart, int drawEnd, int color)
{
	while (drawStart < drawEnd)
	{
		my_mlx_pixel_put(data->win, x, drawStart, color);
		drawStart++;
	}
}

void	lodev(t_main *data)
{
	float posX = (float)data->plr->x;
	float posY = (float)data->plr->y;
	// printf("x: %f	y: %f\n",  posX, posY); exit(0);
	// float posX = 22, posY = 12;
	float	dirX = cos(data->plr->dir * 0.5);
	float	dirY = sin(data->plr->dir * 0.5);
//float dirX = -1, dirY = 0;
	
	float planeX = 0, planeY = 0.66;
	//float planeX = data->plr->start;
	//float planeY = data->plr->end;
	float	w = WIN_WIDTH;
	float	h = WIN_HEIGHT;
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
		float deltaDistX = (rayDirX == 0) ? 1e30 : fabsf(1 / rayDirX);
		float deltaDistY = (rayDirY == 0) ? 1e30 : fabsf(1 / rayDirY);

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
			if(data->map->map[mapX][mapY] == '1')
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
		int	color = MAROON;
		//give x and y sides different brightness
		if (side == 1)
			color = BLUE;
		draw_line(data, x, drawStart, drawEnd, color);
		x++;
	}
} 

void	rendering(t_main *data)
{
	cb_render_floor_ceiling(data);
	lodev(data);//todo сюда зафигачить наше супер 3D и все 
	cb_render_mini_map(data);
}

int	main(int argc, char **argv)
{
	t_main	data;
	t_map	map;
	t_win	win;
	t_plr	plr;

	data.map = &map;//todo пусть память выделятся на стеке
	data.win = &win;//todo пусть память выделятся на стеке
	data.plr = &plr;//todo пусть память выделятся на стеке
	cb_init_main_struct(&data);
	parsing(argc, argv[1], &data);
	rendering(&data);
	mlx_put_image_to_window(data.win->mlx_ptr, data.win->win_ptr, data.win->img_ptr, 0, 0);
	cb_handle_events(&data);
//	mlx_key_hook(data.win->win_ptr, cb_handle_keyboard, &data); // ловит ESC & NUM± // TODO я убрал это гавно
	mlx_loop(data.win->mlx_ptr);
}
