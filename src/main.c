#include "./../inc/cub3d.h"

//char worldMap[5][4]=
//{
//  {'1','1','1','1'},
//  {'1','0','0','1'},
//  {'1','0','N','1'},
//  {'1','0','0','1'},
//  {'1','1','1','1'}
// };

int	main(int argc, char **argv)
{
	t_main	data;
	t_map	map;
	t_win	win;
	t_plr	plr;

	data.map = &map;
	data.win = &win;
	data.plr = &plr;

	cb_init_main_struct(&data); // инит структур win и plr в data + запуск окна 
	parsing(argc, argv[1], &data);

//{
//t_map *tmp = data->map;
//   printf("################# MAP START #################\n");
//  for (int i = 0; tmp->map[i]; i++)
//  {
//   printf("%s", tmp->map[i]+1);
//   printf("\n");
//  }
//  printf("################# MAP FINISH ################\n");
//}

	cb_put_flat_map(&data);
	mlx_put_image_to_window(data.win->mlx_ptr, data.win->win_ptr, data.win->img_ptr, 0, 0);
	cb_handle_events(&data); // ловит нажатие X-окна
//	mlx_key_hook(data.win->win_ptr, cb_handle_keyboard, &data); // ловит ESC & NUM± // TODO я убрал это гавно
	mlx_loop(data.win->mlx_ptr);
}
