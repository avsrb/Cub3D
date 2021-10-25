#include "./../inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_main	*data;

	(void)argv;
	if (argc != 2)
		return(cb_return_nbr(1, "Error: Invalid arguments"));
	data = (t_main *)malloc(sizeof(t_main));
	if (!data)
		return(cb_return_nbr(1, strerror(errno)));
	data = cb_init_main_struct(data);

	printf("LET THE GAME BEGIN!!!\n"); // todo

	return (0);
}
