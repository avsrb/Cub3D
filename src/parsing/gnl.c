#include "../../inc/cub3d.h"

char	*gnl(int fd)
{
	int		res;
	int		i;
	char	*line;

	i = 0;
	line = malloc(sizeof(*line) * 1024);
	if (!line)
		return (NULL);
	while ((res = read(fd, line + i, 1)))
	{
		if (res < 0)
			return(NULL);
		if (line[i] == '\n')
			break ;
		i++;
	}
	line[i] = '\0';
	return (line);
}
