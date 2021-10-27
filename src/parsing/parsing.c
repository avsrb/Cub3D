#include "../../inc/cub3d.h"

//int	ft_wdcounter(char *str, char c)
//{
//	int	i;
//	int	newstr;
//
//	i = 0;
//	newstr = 0;
//	while (str[i])
//	{
//		while (str[i] && str[i] == c)
//			i++;
//		if (str[i] && str[i] != c)
//			newstr++;
//		while (str[i] && str[i] != c)
//			i++;
//	}
//	return (newstr);
//}
//
//int	get_height(char *file_name)
//{
//	char	*line;
//	int		fd;
//	int		height;
//
//	fd = open(file_name, O_RDONLY);
//	height = 0;
//	while (get_next_line(fd, &line))
//	{
//		height++;
//		free(line);
//	}
//	free(line);
//	close(fd);
//	return (height);
//}
//
//int	get_width(char *file_name)
//{
//	char	*line;
//	int		fd;
//	int		width;
//
//	fd = open(file_name, O_RDONLY);
//	get_next_line(fd, &line);
//	width = ft_wdcounter(line, ' ');
//	free(line);
//	close(fd);
//	return (width);
//}
//
//void	fill_matrix(int *z_line, char *line)
//{
//	char	**nums;
//	int		i;
//
//	nums = ft_split(line, ' ');
//	i = 0;
//	while (nums[i])
//	{
//		z_line[i] = ft_atoi(nums[i]);
//		free(nums[i]);
//		i++;
//	}
//	free(nums);
//}
//
//void	make_map(char *file_name, t_map *data)
//{
//	int		fd;
//	int		i;
//	char	*line;
//
//	data->height = get_height(file_name);
//	data->width = get_width(file_name);
//	data->map = (int **)malloc(sizeof(int *) * (data->height + 1));
//	i = 0;
//	while (i <= data->height)
//		data->xpm[i++] = (int *)malloc(sizeof(int) * (data->width + 1));
//	fd = open(file_name, O_RDONLY);
//	i = 0;
//	while (get_next_line(fd, &line))
//	{
//		if (line[0] == '1')
//			fill_matrix(data->xpm[i], line);
//		free(line);
//		i++;
//	}
//	free(line);
//	close(fd);
//	free (data->xpm[i]);
//	data->xpm[i] = NULL;
//}

int	check_file(int ac, char *file, t_map *m)
{
	int	fd = 0;

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
		if (m->param_done == true)
			ft_lstadd_back(&m->map_l, ft_lstnew(ft_strdup(line)));
		free(line);
	}
	free(line);
}

int	parsing(int ac, char *file, t_map *m)
{
	int		fd;

	fd = check_file(ac, file, m);
	init(m);
	parsing_param(fd, m);
	close(fd);
	return 0;
}


int	main(int argc, char **argv)
{
	t_map	m;
	int i = 0;
	int j = 0;


	parsing(argc, argv[1], &m);
//	while (1)
//		;
	printf("%d\n", m.floor);
	printf("%d\n", m.cilling);
	printf("%s\n", m.xpm[0]);
	printf("%s\n", m.xpm[1]);
	printf("%s\n", m.xpm[2]);
	printf("%s\n", m.xpm[3]);
//	while(i < m.height)
//	{
//		j = 0;
//		while(j < m.width)
//		{
//			printf("%3d", m.map[i][j]);
//			j++;
//		}
//		printf("\n");
//		i++;
//	}
	return (0);
}

