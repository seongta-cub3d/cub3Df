

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
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
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

typedef struct s_texture {
	char	*tex_path;  //parsing to-do
	int		*tex_info;  //execution to-do
	int		tex_height; //execution to-do
	int		tex_width;  //execution to-do
}	t_texture;

typedef struct s_screen {
	//t_map worldmap; parsing to-do: 지금은 main문에 선언한 임시 worldmap 사용 중
	int		*floor;  //parsing to-do
	int		*ceiling; //parsing to-do
	t_texture *tex_ary; //parsing to-do: tex_ary 안에 tex_path 넣어주기
	int		**buffer;
}	t_screen;

typedef struct s_map {
	int	**worldmap;
	int map_height;
	int map_width;
}	t_map;	


typedef struct s_calc{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perpwall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		color;
}	t_calc;


void	init_structs(t_user *user, t_mlx *mlx, t_screen *screen);
void	execution_main(t_user *user, t_mlx *mlx, t_screen *screen);
void	fill_buffer(t_user *user, t_screen *screen);
void    clear_buffer(t_screen *screen);
void    init_buffer_with_zero(t_screen *screen);
void    init_vars(t_user *user, t_calc *var, int x);
void    init_step_and_sidedist(t_user *user, t_calc *var);
void    shoot_ray(t_calc *var);
void    fish_eye_correction(t_calc *var, t_user *user);
void    calc_draw_y_coordinates(t_calc *var);
void    calc_texture(t_calc *var, t_user *user, t_screen *screen, int x);
void    calc_texture_vars(t_calc *var, t_user *user);
void    calc_texture_coor(t_calc *var, t_screen *screen, int x);
void    draw_buffer(t_mlx *mlx, t_screen *screen);

#endif