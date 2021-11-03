#include "../../inc/cub3d.h"

int	check_file(int ac, char *file)
{
	int	fd;

	fd = -1;
	if (ac != 2)
		ft_error("use './cub maps/org.cud'");
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

void	parsing_param(int fd, t_map *m)
{
	char	*line;
	int		res;

	line = NULL;
	while (true)
	{
		res = gnl(fd, &line);
		if (res < 0)
			ft_error(NULL);
		if (!ft_strlen(line) && m->height && !m->map_done)
			m->map_done = true;
		if (ft_strlen(line))
		{
			if (m->map_done)
				ft_error("line empty in the map\n");
			if (m->param_done == true)
				ft_lstadd_back(&m->map_l, ft_lstnew(ft_strdup(line)));
			else
				get_tex_and_color(line, m);
		}
		free(line);
		if (!res)
			break ;
	}
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

int	double_player(t_map *m)
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
	if (player > 1)
		return (1);
	return (0);
}

//void	check_open_texture(t_main *all)
//{
//	if (!mlx_xpm_file_to_image(all->win->win_ptr, all->map->xpm[0], 600, 600))
//		ft_error("can`t open texture\n");
//	if (!mlx_xpm_file_to_image(all->win->win_ptr, all->map->xpm[1], 600, 600))
//		ft_error("can`t open texture\n");
//	if (!mlx_xpm_file_to_image(all->win->win_ptr, all->map->xpm[2], 600, 600))
//		ft_error("can`t open texture\n");
//	if (!mlx_xpm_file_to_image(all->win->win_ptr, all->map->xpm[3], 600, 600))
//		ft_error("can`t open texture\n");
//
//}

int	check_wall(char **map, int y, int x)
{
	return ((!map[y + 1][x]||map[y + 1][x] == ' '
			|| !map[y - 1][x]||map[y - 1][x] == ' '
			|| !map[y][x + 1]||map[y][x + 1] == ' '
			|| !map[y][x - 1]||map[y][x - 1] == ' '
			|| !map[y + 1][x + 1]||map[y + 1][x + 1] == ' '
			|| !map[y + 1][x - 1]||map[y + 1][x - 1] == ' '
			|| !map[y - 1][x + 1]||map[y - 1][x + 1] == ' '
			|| !map[y - 1][x - 1]||map[y - 1][x - 1] == ' '));
}

void	final_check_map(t_map *m)
{
	char **map;
	int	y;
	int	x;

	map = m->map;
	y = 0;
	while (++y < m->height - 1)
	{
		x = 0;
		while(++x < m->width - 1)
		{
			if (cb_strchr("0NEWS", map[y][x]) && check_wall(map, y, x))
				ft_error("there is a door to a parallel universe\n");
		}
	}
}

int	parsing(int ac, char *file, t_main *all)
{
	int	fd;

	fd = check_file(ac, file);
	init(all->map);
	parsing_param(fd, all->map);
	close(fd);
	check_simbol(all->map->map_l);
	make_map(all->map);

	final_check_map(all->map);
	if (double_player(all->map))
		ft_error("the player must be alone\n");
	if (all->map->param_done == false)//Del
		ft_error("map not valid\n");//Del
	return (0);
}
