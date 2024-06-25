
#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include "./minilibx/mlx.h"
# include "./libft/libft.h"

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_EXIT 17
# define texWidth 64
# define texHeight 64
# define width 1920
# define height 1080

# define TEXWIDTH 64
# define TEXHEIGHT 64
# define WIDTH 1920
# define HEIGHT 1080

# define BACKWARD 1
# define FORWARD 13
# define LEFT 0
# define RIGHT 2
# define ROTATE_LEFT 123
# define ROTATE_RIGHT 124
# define ESC 53

# define NEAR_ZERO 1e-9

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

typedef struct s_map {
	int	**worldmap;
	int	map_height;
	int	map_width;
}	t_map;

typedef struct s_texture {
	void			*img;
	char			*tex_path;
	unsigned int	*tex_data;
	int				tex_height;
	int				tex_width;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}	t_texture;

typedef struct s_screen {
	t_map		worldmap;
	int			floor;  //parsing to-do
	int			ceiling; //parsing to-do
	t_texture	tex_ary[4]; // 북남동서
	int			**buffer;
}	t_screen;



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

typedef struct s_struc{
	t_user		*user;
	t_screen	*screen;
	t_mlx		*mlx;
}	t_struc;

void	init_structs(t_user *user, t_mlx *mlx, t_screen *screen);
void	init_screen(t_mlx *mlx, t_screen *screen);
void	execution_main(t_user *user, t_mlx *mlx, t_screen *screen);
void	fill_buffer(t_user *user, t_screen *screen);
void	clear_buffer(t_screen *screen);
void	init_buffer_with_zero(t_screen *screen);
void	init_vars(t_user *user, t_calc *var, int x);
void	init_step_and_sidedist(t_user *user, t_calc *var);
void	shoot_ray(t_calc *var, t_screen *screen);
void	fish_eye_correction(t_calc *var, t_user *user);
void	calc_draw_y_coordinates(t_calc *var);
void	calc_texture(t_calc *var, t_user *user, t_screen *screen, int x);
void	calc_texture_vars(t_calc *var, t_user *user, t_screen *screen);
void	calc_texture_coor(t_calc *var, t_screen *screen, int x);
void	draw_buffer(t_mlx *mlx, t_screen *screen);
void	init_tex_ary(t_mlx *mlx, t_screen *screen);
int		key_press(int key, t_struc *struc);

void	draw_floor_and_ceiling(t_calc *var, t_screen *screen, int x);

void	parsing_map(t_screen *screen, char *path);

int		exit_hook(t_mlx *mlx);
#endif
