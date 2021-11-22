#include "../../inc/cub3d.h"

void	set_player_direction_cont(t_plr *plr, char c)
{
	if (c == 'W')
	{
		plr->dir_x = -1.0;
		plr->dir_y = 0;
		plr->plane_x = 0;
		plr->plane_y = 0.66;
		plr->angle = ft_degree_to_ratio(180);
	}
	else if (c == 'E')
	{
		plr->dir_x = 0.998295;
		plr->dir_y = -0.058374;
		plr->plane_x = -0.038527;
		plr->plane_y = -0.658875;
		plr->angle = ft_degree_to_ratio(0);
	}
}

void	set_player_direction(t_plr *plr, char c)
{
	if (c == 'N')
	{
		plr->dir_x = 0.012389;
		plr->dir_y = -0.999923;
		plr->plane_x = -0.659949;
		plr->plane_y = -0.008177;
		plr->angle = ft_degree_to_ratio(270);
	}
	else if (c == 'S')
	{
		plr->dir_x = 0.029200;
		plr->dir_y = 0.999574;
		plr->plane_x = 0.659719;
		plr->plane_y = -0.019272;
		plr->angle = ft_degree_to_ratio(90);
	}
	else
		set_player_direction_cont(plr, c);
}

void	find_player(t_plr *plr, t_map *m)
{
	int	y;
	int	x;

	y = 0;
	while (m->map[y])
	{
		x = 0;
		while (m->map[y][x])
		{
			if (m->map[y][x] == 'N' || m->map[y][x] == 'S'
			|| m->map[y][x] == 'W' || m->map[y][x] == 'E')
			{
				plr->y = (float)y + 0.1F;
				plr->x = (float)x + 0.1F;
				set_player_direction(plr, m->map[y][x]);
				return ;
			}
			x++;
		}
		y++;
	}
}
