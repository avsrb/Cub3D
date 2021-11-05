#include "../../inc/cub3d.h"

int	check_file(int ac, char *file)
{
	int	fd;

	fd = -1;
	if (ac != 2)
		ft_error("use './cub maps/org.cub'");
	if (ft_strncmp(file + (ft_strlen(file) - 4), ".cub", 4) \
	|| ft_strlen(file) < 4)
	ft_error("use map with '.cub'");
	fd = open(file, O_RDONLY);
	if (fd < 0 || read(fd, NULL, 0) < 0)
	{
		ft_error(NULL);
		close(fd);
	}
	return (fd);
}

void	check_map(t_map *m)
{
	char	**map;
	int		y;
	int		x;

	map = m->map;
	y = 0;
	while (++y < m->height - 1)
	{
		x = 0;
		while (++x < m->width - 1)
		{
			if (cb_strchr("0NEWS", map[y][x]) && check_wall(map, y, x))
				ft_error("there is a door to a parallel universe\n");
		}
	}
}

int	check_wall(char **map, int y, int x)
{
	return ((!map[y + 1][x] || map[y + 1][x] == ' '
	|| !map[y - 1][x] || map[y - 1][x] == ' '
	|| !map[y][x + 1] || map[y][x + 1] == ' '
	|| !map[y][x - 1] || map[y][x - 1] == ' '
	|| !map[y + 1][x + 1] || map[y + 1][x + 1] == ' '
	|| !map[y + 1][x - 1] || map[y + 1][x - 1] == ' '
	|| !map[y - 1][x + 1] || map[y - 1][x + 1] == ' '
	|| !map[y - 1][x - 1] || map[y - 1][x - 1] == ' '));
}

int	check_double_player(t_map *m)
{
	int	y;
	int	x;
	int	player;

	y = 0;
	player = 0;
	while (m->map[y])
	{
		x = 0;
		while (m->map[y][x])
		{
			if (m->map[y][x] == 'N' || m->map[y][x] == 'S'
			|| m->map[y][x] == 'W' || m->map[y][x] == 'E')
				player++;
			x++;
		}
		y++;
	}
	return (player != 1);
}

void	check_simbol(t_lst *map_l)
{
	int	i;

	while (map_l)
	{
		i = 0;
		while (map_l->val[i])
		{
			if (!cb_strchr(" 01NEWS", map_l->val[i]))
				ft_error("bad symbols in map\n");
			i++;
		}
		map_l = map_l->next;
	}
}
