#include "../../inc/cub3d.h"

void	ft_error(char *str)
{
	if (str)
	{
		ft_putstr_fd("Error: ", STDERR);
		ft_putendl_fd(str, STDERR);
	}
	else
		perror(NULL);
	exit (1);
}
