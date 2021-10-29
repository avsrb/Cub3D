#include "../../inc/cub3d.h"

int	check_file(int ac, char *file, t_map *m)
{
	int	fd;

	fd = -1;
	if (ac != 2)
		ft_error(NULL);
	if (ft_strncmp(file + (ft_strlen(file) - 4), ".cub", 4) \
		|| ft_strlen(file) < 4)
		ft_error("use map with '.cub'");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error(NULL);
	return (fd);
}

void	init(t_map *m)
{
	int	i;

	i = 0;
	m->param_done = false;
	m->xpm = malloc(sizeof(char *) * 4);
	if (!m->xpm)
		ft_error(NULL);
	while (m->xpm[i])
		m->xpm[i] = NULL;
}

void	parsing_param(int fd, t_map *m)
{
	char	*line;
	char	*scrubbed_str;

	line = NULL;
	scrubbed_str = NULL;
	while (get_next_line(fd, &line))
	{
		get_tex_and_color(line, m);
		if (m->param_done == true)
		{
			scrubbed_str = spacecutter(line);
			if (scrubbed_str != NULL)
				ft_lstadd_back(&m->map_l, ft_lstnew(ft_strdup(scrubbed_str)));
		}
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

void	check_map(t_lst *map_l)
{
	int	i;

	while (map_l)
	{
		i = 0;
		while (map_l->val[i])
		{
			if (!cb_strchr(" 012NEWS", map_l->val[i]))
				ft_error("bad symbols in map\n");
			i++;
		}
		map_l = map_l->next;
	}
}

int	find_player(t_map *m)
{
	int	i;
	int	i1;
	int	player;

	i = 0;
	i1 = 0;
	player = 0;
	while (m->map[i])
	{
		i1 = 0;
		while (m->map[i][i1])
		{
			if (m->map[i][i1] == 'N')
				player++;
			if (m->map[i][i1] == 'S')
				player++;
			if (m->map[i][i1] == 'W')
				player++;
			if (m->map[i][i1] == 'E')
				player++;
			i1++;
		}
		i++;
	}
	return (player != 1);
}

int	parsing(int ac, char *file, t_map *m)
{
	int	fd;

	fd = check_file(ac, file, m);
	init(m);
	parsing_param(fd, m);
	close(fd);
	check_map(m->map_l);
	make_map(m);
	if (find_player(m))
		ft_error("the player must be alone\n");
	return (0);
}

//int	main(int argc, char **argv)
//{
//	t_map	m;
//	int		i;
//
//	i = 0;
//	parsing(argc, argv[1], &m);
//	printf("%d\n", m.floor);
//	printf("%d\n", m.cilling);
//	printf("%s\n", m.xpm[0]);
//	printf("%s\n", m.xpm[1]);
//	printf("%s\n", m.xpm[2]);
//	printf("%s\n", m.xpm[3]);
//	while (m.map[i])
//	{
//		printf("%s\n", m.map[i]);
//		i++;
//	}
//	return (0);
//}
