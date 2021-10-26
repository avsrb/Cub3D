// allocates memory & exit if failed

#include "../../inc/cub3d.h"

void	*cb_malloc_x(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("cub3D");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}
