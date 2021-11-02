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

void	init(t_map *m)
{
	int	i;

	i = 0;
	m->param_done = 0;
	m->param_done = false;
	m->map = NULL;
	m->floor = 0;
	m->cilling = 0;
	m->width = 0;
	m->height = 0;
	m->map_l = NULL;
	m->xpm = malloc(sizeof(char *) * 4);
	if (!m->xpm)
		ft_error(NULL);
	while (m->xpm[i])
		m->xpm[i] = NULL;
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
		get_tex_and_color(line, m);
		if (m->param_done == true)
		{
			if (ft_strlen(line) == 0 && !m->map_l)
			{
				free(line);
				continue;
			}
			ft_lstadd_back(&m->map_l, ft_lstnew(ft_strdup(line)));
		}
		if (!res)
			break ;
		free(line);
	}
	free(line);
}

static int	cb_strchr(const char *str, int c)
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
			if (m->map[y][x] == 'N')
				player++;
			if (m->map[y][x] == 'S')
				player++;
			if (m->map[y][x] == 'W')
				player++;
			if (m->map[y][x] == 'E')
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
//}

int	parsing(int ac, char *file, t_main *all)
{
	int	fd;

	fd = check_file(ac, file);
	init(all->map);
	parsing_param(fd, all->map);
	close(fd);
	check_simbol(all->map->map_l);
	make_map(all->map);
	if (double_player(all->map))
		ft_error("the player must be alone\n");
	if (all->map->param_done == false)
		ft_error("map not valid\n");
//	check_open_texture(all);
	return (0);
}

//int	main(int argc, char **argv)
//{
//	t_main	*m = malloc(sizeof(t_main));
//	t_map	map;
//	m->map = &map;
//	int		i;
//
//	i = 0;
//	parsing(argc, argv[1], m);
////	printf("%d\n", m->map->floor);
////	printf("%d\n", m->map->cilling);
////	printf("%s\n", m->map->xpm[0]);
////	printf("%s\n", m->map->xpm[1]);
////	printf("%s\n", m->map->xpm[2]);
////	printf("%s\n", m->map->xpm[3]);
////	while (m->map->map[i])
////	{
////		printf("%s\n", m->map->map[i]);
////		i++;
////	}
//	return (0);
//}
