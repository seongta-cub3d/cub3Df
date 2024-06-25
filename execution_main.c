
#include "cub3D.h"

void	fill_buffer(t_user *user, t_screen *screen)
{
	t_calc	var;
	int		x;

	x = -1;
	while (++x < width)
	{
		init_vars(user, &var, x);
		shoot_ray(&var, screen);
		fish_eye_correction(&var, user);
		calc_draw_y_coordinates(&var);
		calc_texture(&var, user, screen, x);
		draw_floor_and_ceiling(&var, screen, x);
	}
	return ;
}

void	execution_main(t_user *user, t_mlx *mlx, t_screen *screen)
{
	clear_buffer(screen);
	fill_buffer(user, screen);
	draw_buffer(mlx, screen);
	return ;
}