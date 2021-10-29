#include "../../inc/cub3d.h"

int	get_height(t_lst *map_l)
{
	int		height;

	height = 0;
	while (map_l)
	{
		height++;
		map_l = map_l->next;
	}
	return (height);
}

int	get_width(t_lst *map_l)
{
	int	width;
	int	prev_width;

	width = 0;
	prev_width = ft_strlen(map_l->val);
	while (map_l)
	{
		width = 0;
		while (map_l->val[width])
		{
			width++;
		}
		if (width != prev_width)
			ft_error("different width in map\n");
		prev_width = width;
		map_l = map_l->next;
	}
	return (width);
}

char	*spacecutter(char *str)
{
	char	*pStr = str;
	int		i = 0;

	while (*str != '\0')
	{
		if (*str != ' ')
		{
			pStr[i] = *str;
			i++;
		}
		str++;
	}
	pStr[i] = '\0';
	return(pStr);
}

void	fill_matrix(t_map *map, t_lst **map_l)
{
	int		i;
	t_lst	*lst;

	lst = *map_l;
	i = 0;
	while (lst)
	{
//		if (i == 0 || i == map->height) дописать проверку на стену сверху и внизу
//				ft_error("Not wall in map1\n");
		if (lst->val[0] != '1' ||  lst->val[ft_strlen(lst->val) - 1] != '1')
			ft_error("Not wall in map\n");
		map->map[i] = ft_strdup(spacecutter(lst->val));
		lst = lst->next;
		i++;
	}
}

void	make_map(t_map *data)
{
	data->height = get_height(data->map_l);
	data->width = get_width(data->map_l);
	data->map = malloc(sizeof(char *) * (data->height + 1));
	fill_matrix(data, &data->map_l);
	data->map[data->height] = NULL;
}

int	check_file(int ac, char *file, t_map *m)
{
	int	fd = 0;

	(void)m;
	if (ac != 2)
		ft_error(NULL);
	if (ft_strncmp(file + (ft_strlen(file) - 4), ".cub", 4) || ft_strlen(file) < 4)
		ft_error("Use map with '.cub'");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error(NULL);
	return (fd);
}

int	counter_comas(char *str)
{
	int		i;
	int		comas;

	comas = 0;
	i = 0;
	while(str[i++])
	{
		if (str[i] == ',')
			comas++;
	}
	return (comas);
}

void	free_all(char **arr)
{
	int	i;

	i = 0;
	while(arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_color(char *str, t_map *m)
{
	char	**arr;
	int		color[3];
	char	*not_space;
	int		i;

	(void)m;
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
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (!ft_strncmp(str, "F ", 2))
		m->floor = get_color(str + 2, m);
	else if (!ft_strncmp(str, "C ", 2))
		m->cilling = get_color(str + 2, m);
	else if (!(ft_strncmp(str, "NO ", 3)))
		m->xpm[0] = ft_substr(str, 3, ft_strlen(str));
	else if (!(ft_strncmp(str, "SO ", 3)))
		m->xpm[1] = ft_substr(str, 3, ft_strlen(str));
	else if (!(ft_strncmp(str, "WE ", 3)))
		m->xpm[2] = ft_substr(str, 3, ft_strlen(str));
	else if (!(ft_strncmp(str, "EA ", 3)))
		m->xpm[3] = ft_substr(str, 3, ft_strlen(str));
	else if (m->floor && m->cilling && m->xpm[0] \
		&& m->xpm[1] && m->xpm[2] && m->xpm[2])
	{
		m->param_done = true;
		return ;
	}
}

void	init(t_map *m)
{
	int	i;

	i = 0;
	m->param_done = false;
	m->map = NULL;
	m->floor = 0;
	m->cilling = 0;
	m->width = 0;
	m->height = 0;
	m->xpm = malloc(sizeof(char *) * 4);
	if (!m->xpm)
		ft_error(NULL);
	while (m->xpm[i])
		m->xpm[i] = NULL;
}

void	ft_lstadd_back(t_lst **head, t_lst *new)
{
	t_lst	*last;

	if (head && (*head) && new)
	{
		last = *head;
		if (*head == NULL)
			*head = new;
		else
		{
			while (last->next)
				last = last->next;
			last->next = new;
		}
	}
	else if (*head == NULL)
		*head = new;
}

t_lst	*ft_lstnew(char *content)
{
	t_lst	*list;

	list = malloc(sizeof(*list));
	if (!list)
		return (NULL);
	list->val = content;
	list->next = NULL;
	return (list);
}

void	parsing_param(int fd, t_map *m)
{
	char	*line;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		get_tex_and_color(line, m);
		if (m->param_done == true && *line == '1')
			ft_lstadd_back(&m->map_l, ft_lstnew(ft_strdup(line)));
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
				ft_error("Bad symbols in map\n");
			i++;
		}
		map_l = map_l->next;
	}
}

int	find_player(t_map *m)
{
	int	i;
	int	i1;
	int player;

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
	int		fd;

	fd = check_file(ac, file, m);
	init(m);
	parsing_param(fd, m);
	check_map(m->map_l);
	make_map(m);
	if (find_player(m))
		ft_error("More players\n");
	close(fd);
	return 0;
}


//int	main(int argc, char **argv)
//{
//	t_map	m;
//	int i = 0;

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

