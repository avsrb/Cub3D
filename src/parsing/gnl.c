#include "../../inc/cub3d.h"

int	gnl(int fd, char **line)
{
	int	res;
	int	i;

	i = 0;
	*line = malloc(sizeof (*line) * 10485760);
	if (!*line)
		return (-1);
	while (1 && (res = read(fd, *line + i, 1)))
	{
		if (res == -1)
			return (-1);
		if ((*line)[i] == '\n')
			break ;
		i++;
	}
	(*line)[i] = 0;
	return ((res != 0));
}
