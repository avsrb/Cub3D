#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <sys/errno.h>
# include "../inc/colors.h"
# include "../inc/macos_keyboard.h"
# include "../src/libft/inc/libft.h"
# include "../src/minilibx_mms/mlx.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

#define SCALE 16 // условный размер каждого квадратика в карте

typedef struct	s_win //структура для окна
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*addr;
	int			line_l;
	int			bpp;
	int			en;
}				t_win;

typedef struct	s_point // структура для точки
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_plr //структура для игрока и луча
{
	float		x;
	float		y;
	float		dir;
	float		start;
	float		end;
}				t_plr;

typedef struct	s_map
{
	int		height;
	int 	width;
	int 	**z_matrix;
}			t_map;

typedef struct	s_all // структура для всего вместе
{
	t_win		*win;
	t_plr		*plr;
	char		**map;
}				t_all;

typedef struct s_list
{
	char *val;
	struct s_list *next;
}			t_list;

//utils

//parser
int		gnl(int fd, char **line);
void	ft_error(char *str);

//lst
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstnew(char *val);
int		ft_lstmed(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstfindmin(t_list *lst);
int		ft_lstfindmax(t_list *lst);
void	ft_lstclear(t_list **lst);
void	ft_lstdelone(t_list *lst);
int	ft_lstfindindex(t_list *lst, int f);

#endif
