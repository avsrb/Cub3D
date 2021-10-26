#include "../../inc/cub3d.h"

void	*cb_return_null(char *message)
{
	write(STDERR_FILENO, "cub3D: ", 7);
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
	return (NULL);
}

int	cb_return_nbr(int return_value, char *message)
{
	write(STDERR_FILENO, "cub3D: ", 7);
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
	return (return_value);
}
