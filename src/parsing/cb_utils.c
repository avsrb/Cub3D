#include "../../inc/cub3d.h"

int	cb_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	init_map(t_map *m)
{
	int	i;

	i = -1;
	m->param_done = false;
	m->map_done = false;
	m->map = NULL;
	m->floor = -1;
	m->ceiling = -1;
	m->width = 0;
	m->height = 0;
	m->map_l = NULL;
	m->xpm = malloc(sizeof(char *) * 4);
	if (!m->xpm)
		ft_error(NULL);
	while (++i < 4)
		m->xpm[i] = NULL;
}

void	init_player(t_main *data)
{
	data->plr->x = 0.0F;
	data->plr->y = 0.0F;
	data->plr->plane_x = 0.0F;
	data->plr->plane_y = 0.0F;
	data->plr->dir_x = 0.0F;
	data->plr->dir_y = 0.0F;
	data->plr->angle = 0.0F;
}

int	cb_isdigit_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}
