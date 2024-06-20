
#include "cub3D.h"

void	set_user_vector(t_user *user, t_screen *screen, int y, int x)
{
	(void)screen;
	user->posX = x;
	user->posY = y;

	if (worldmap[y][x] == 'N' || worldmap[y][x] == 'S')
	{
		user->dirX = 0;
		if (worldmap[y][x] == 'N')
			user->dirY = 1;
		else
			user->dirY = -1;
	}
	if (worldmap[y][x] == 'E' || worldmap[y][x] == 'W')
	{
		user->dirY = 0;
		if (worldmap[y][x] == 'E')
			user->dirX = 1;
		else
			user->dirX = -1;
	}
	return ;
}

void	init_user(t_user *user, t_screen *screen)
{
	int	y;
	int	x;

	y = -1;
	while (++y < mapHeight)
	{
		x = -1;
		while (++x < mapWidth)
		{
			if (worldmap[y][x] == 'N' || worldmap[y][x] == 'S' ||
				worldmap[y][x] == 'W' || worldmap[y][x] == 'E')
				{
					set_user_vector(user, screen, y, x);
					break;
				}
		}
	}
	user->planeX = 0.0;
	user->planeY = 0.66;
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
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, \
	&mlx->line_length, &mlx->endian);
	return ;
}


void	init_structs(t_user *user, t_mlx *mlx, t_screen *screen, t_texture *texture)
{
	init_user(user, screen);
	init_mlx(mlx);
	(void)texture;
	// init_screen(screen);
	// init_texture(texture);
	return ;
}