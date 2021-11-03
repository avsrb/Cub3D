#include "../../inc/cub3d.h"

static int	counter_comas(char *str)
{
	int		i;
	int		comas;

	comas = 0;
	i = 0;
	while (str[i++])
	{
		if (str[i] == ',')
			comas++;
	}
	return (comas);
}

static void	free_all(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

static int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_color(char *str)
{
	char	**arr;
	int		color[3];
	char	*not_space;
	int		i;

	i = -1;
	not_space = ft_strtrim(str, " ");
	if (counter_comas(str) != 2)
		ft_error("not valid color");
	arr = ft_split(not_space, ',');
	while (++i < 3)
		color[i] = ft_atoi(arr[i]);
	if (color[0] > 255 || color[1] > 255 || color[2] > 255)
		ft_error("not valid color code");
	color[0] = create_trgb(0, color[0], color[1], color[2]);
	free(not_space);
	free_all(arr);
	return (color[0]);
}

void	get_tex_and_color(char *str, t_map *m)
{
	while (*str == ' ' || *str == '\t')
		str++;
	if (!ft_strncmp(str, "F ", 2))
		m->floor = get_color(spacecutter(str + 2));
	else if (!ft_strncmp(str, "C ", 2))
		m->cilling = get_color(spacecutter(str + 2));
	else if (!(ft_strncmp(str, "NO ", 3)))
		m->xpm[0] = ft_strdup(spacecutter(str + 3));
	else if (!(ft_strncmp(str, "SO ", 3)))
		m->xpm[1] = ft_strdup(spacecutter(str + 3));
	else if (!(ft_strncmp(str, "WE ", 3)))
		m->xpm[2] = ft_strdup(spacecutter(str + 3));
	else if (!(ft_strncmp(str, "EA ", 3)))
		m->xpm[3] = ft_strdup(spacecutter(str + 3));
	else
		ft_error("not enough parameters\n");
	m->param_done = (m->floor >= 0 && m->cilling >= 0 && m->xpm[0]
			&& m->xpm[1] && m->xpm[2] && m->xpm[2]);
}
