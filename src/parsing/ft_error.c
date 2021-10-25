#include "../../inc/cub3d.h"

void	ft_error(char *str)
{
	ft_putendl_fd("Error", STDERR);
	if (str)
		ft_putendl_fd(str, STDERR);
	else
		perror(NULL);
	exit (1);
}