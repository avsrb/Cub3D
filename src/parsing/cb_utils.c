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

void	init(t_map *m)
{
	int	i;

	i = -1;
	m->param_done = false;
	m->map_done = false;
	m->map = NULL;
	m->floor = -1;
	m->cilling = -1;
	m->width = 0;
	m->height = 0;
	m->map_l = NULL;
	m->xpm = malloc(sizeof(char *) * 4);
	if (!m->xpm)
		ft_error(NULL);
	while (++i < 5)
		m->xpm[i] = NULL;
}
