

#ifndef cub3D_H
# define cub3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "./minilibx/mlx.h"
# include "./libft/libft.h"

#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_EXIT	17
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24
#define width 1920
#define height 1080

#define BACKWARD 1
#define FORWARD 13
#define ROTATE_LEFT 123
#define ROTATE_RIGHT 124
#define ESC 53

extern int	worldmap[mapHeight][mapWidth];

typedef struct s_user {
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	moveSpeed;
	double	rotSpeed;
}	t_user;

typedef struct s_mlx {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

typedef struct s_screen {
	//screen 구조체
	int		*floor;
	int		*ceiling;
	char	**texpath_ary;
	int		**buffer;
	int		tex_ary[4][texHeight * texWidth];
	int		re_buf;
}	t_screen;


typedef struct s_texture {
	//texture 배열의 각 요소 하나하나가 품고 있는 정보들
}	t_texture;

void	init_structs(t_user *user, t_mlx *mlx, t_screen *screen, t_texture *texture);


#endif