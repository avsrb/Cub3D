#include "../../inc/cub3d.h"

int	ft_wdcounter(char *str, char c)
{
	int	i;
	int	newstr;

	i = 0;
	newstr = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
			newstr++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (newstr);
}

int	get_height(char *file_name)
{
	char	*line;
	int		fd;
	int		height;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		ft_error(NULL);
	height = 0;
	while (get_next_line(fd, &line))
	{
		height++;
		free(line);
	}
	free(line);
	close(fd);
	return (height);
}

int	get_width(char *file_name)
{
	char	*line;
	int		fd;
	int		width;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		ft_error(NULL);
	get_next_line(fd, &line);
	width = ft_wdcounter(line, ' ');
	free(line);
	close(fd);
	return (width);
}

void	fill_matrix(int *z_line, char *line)
{
	char	**nums;
	int		i;

	nums = ft_split(line, ' ');
	i = 0;
	while (nums[i])
	{
		z_line[i] = ft_atoi(nums[i]);
		free(nums[i]);
		i++;
	}
	free(nums);
}

void	parsing(char *file_name, t_map *data)
{
	int		fd;
	int		i;
	char	*line;

	if (ft_strncmp(&file_name[ft_strlen(file_name) - 4], ".cub", 4))
		ft_error(NULL);
	data->height = get_height(file_name);
	data->width = get_width(file_name);
	data->z_matrix = malloc(sizeof(int *) * (data->height + 10));
	i = 0;
	while (i <= data->height)
		data->z_matrix[i++] = malloc(sizeof(int) * (data->width + 1));
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		ft_error(NULL);
	i = 0;
	while (get_next_line(fd, &line))
	{
		fill_matrix(data->z_matrix[i], line);
		free(line);
		i++;
	}
	free(line);
	close(fd);
	free (data->z_matrix[i]);
	data->z_matrix[i] = NULL;
}


int	main(int argc, char **argv)
{
	t_map	map;
	int		y = 0;
	int		x = 0;
	(void)argc;
	(void)argv;
	//	ft_putstr_fd("Let the game begin!\n", STDOUT_FILENO);
	parsing(argv[1], &map);
	while (y < map.height)
	{
		x = 0;
		while(x < map.width)
		{
			printf("%3d", map.z_matrix[x][y]);
			x++;
		}
		printf("\n");
		y++;
	}
	return (0);
}