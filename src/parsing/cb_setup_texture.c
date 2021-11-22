#include "../../inc/cub3d.h"

unsigned int	color_pixel_texture(t_txr *img, int i, int j)
{
	char			*addr;
	unsigned int	color;

	addr = img->addr + (j * img->size_line + i * (img->bpp / 8));
	color = *(unsigned int *)addr;
	return (color);
}

void	setup_texture(t_main *all, t_txr *txr, char *file)
{
	int	sz[2];
	int	i;
	int	j;

	i = -1;
	txr->img = mlx_xpm_file_to_image(all->win->mlx_ptr, file, &sz[0], &sz[1]);
	if (!txr->img)
		ft_error("Not read xmp file\n");
	if (sz[0] != 64 || sz[1] != 64)
		ft_error("invalid xpm size\n");
	txr->addr = mlx_get_data_addr(txr->img, &txr->bpp, \
								&txr->size_line, &txr->endian);
	txr->matrix = cb_malloc_x(sizeof(int *) * sz[0]);
	while (++i < sz[0])
	{
		j = -1;
		txr->matrix[i] = malloc(sizeof(int) * sz[1]);
		while (++j < sz[1])
			txr->matrix[i][j] = color_pixel_texture(txr, i, j);
	}
}

void	open_texture(t_main *all)
{
	all->txrs->north = cb_malloc_x(sizeof(t_txr));
	setup_texture(all, all->txrs->north, all->map->xpm[0]);
	all->txrs->south = cb_malloc_x(sizeof(t_txr));
	setup_texture(all, all->txrs->south, all->map->xpm[1]);
	all->txrs->west = cb_malloc_x(sizeof(t_txr));
	setup_texture(all, all->txrs->west, all->map->xpm[2]);
	all->txrs->east = cb_malloc_x(sizeof(t_txr));
	setup_texture(all, all->txrs->east, all->map->xpm[3]);
}
