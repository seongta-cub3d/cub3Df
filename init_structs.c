
#include "cub3D.h"

void	set_user_vector(t_user *user, t_screen *screen, int y, int x)
{
	user->pos_x = x + 0.5;
	user->pos_y = y + 0.5;
	if (screen->worldmap.worldmap[y][x] == 'N' || screen->worldmap.worldmap[y][x] == 'S')
	{
		user->dir_x = 0;
		if (screen->worldmap.worldmap[y][x] == 'N')
			user->dir_y = -1;
		else
			user->dir_y = 1;
	}
	if (screen->worldmap.worldmap[y][x] == 'E' || screen->worldmap.worldmap[y][x] == 'W')
	{
		user->dir_y = 0;
		if (screen->worldmap.worldmap[y][x] == 'E')
			user->dir_x = 1;
		else
			user->dir_x = -1;
	}
	return ;
}

void	init_camera_plane(t_user *user, t_screen *screen, int y, int x)
{
	if (screen->worldmap.worldmap[y][x] == 'N')
	{
		user->plane_x = 0.66;
		user->plane_y = 0;
	}
	if (screen->worldmap.worldmap[y][x] == 'S')
	{
		user->plane_x = -0.66;
		user->plane_y = 0;
	}

	if (screen->worldmap.worldmap[y][x] == 'W')
	{
		user->plane_x = 0;
		user->plane_y = -0.66;
	}
	if (screen->worldmap.worldmap[y][x] == 'E')
	{
		user->plane_x = 0;
		user->plane_y = 0.66;
	}
	return ;
}

void	init_user(t_user *user, t_screen *screen)
{
	int	y;
	int	x;

	user->move_speed = 0.05;
	user->rot_speed = 0.05;
	y = -1;
	while (++y < screen->worldmap.map_height)
	{
		x = -1;
		while (++x < screen->worldmap.map_width)
		{
			if (screen->worldmap.worldmap[y][x] == 'N' || screen->worldmap.worldmap[y][x] == 'S' ||
				screen->worldmap.worldmap[y][x] == 'W' || screen->worldmap.worldmap[y][x] == 'E')
			{
				set_user_vector(user, screen, y, x);
				init_camera_plane(user,screen, y, x);
				screen->worldmap.worldmap[y][x] = 0;
				return ;
			}
		}
	}
	return ;
}

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (mlx->mlx == NULL)
	{
		perror("failed initiating mlx instance\n");
		exit(1);
	}
	mlx->win = mlx_new_window(mlx->mlx, 1920, 1080, "cub3D!");
	if (mlx->win == NULL)
	{
		perror("failed initiating window instance\n");
		exit(1);
	}
	mlx->img = mlx_new_image(mlx->mlx, 1920, 1080);
	mlx->addr = mlx_get_data_addr(mlx->img, &(mlx->bits_per_pixel), \
	&(mlx->line_length), &mlx->endian);
	return ;
}

void	init_screen(t_mlx *mlx, t_screen *screen)
{
	int	i;
	int	y;
	int	x;

	screen->buffer = (int **)malloc(sizeof(int *) * height);
	i = -1;
	while (++i < height)
		screen->buffer[i] = (int *)malloc(sizeof(int *) * width);
	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
			screen->buffer[y][x] = 0;
	}
	init_tex_ary(mlx, screen);
	return ;
}



void	init_structs(t_user *user, t_mlx *mlx, t_screen *screen)
{
	init_user(user, screen);
	init_mlx(mlx);
	init_screen(mlx, screen);
	return ;
}
