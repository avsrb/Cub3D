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

data.plr->x = 3;//todo убрать после того, как допишется парсинг координат игрока
data.plr->y = 3;//todo убрать после того, как допишется парсинг координат игрока
	cb_put_flat_map(&data);
	cb_handle_events(&data); // ловит нажатие X-окна
	mlx_key_hook(data.win->win_ptr, cb_handle_keyboard, &data); // ловит ESC & NUM±
	mlx_loop(data.win->mlx_ptr);
}
