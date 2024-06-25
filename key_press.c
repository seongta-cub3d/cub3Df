
#include "cub3D.h"

int key_press(int key, t_struc *struc)
{
	int new_x;
	int new_y;

	if (key == FORWARD)
	{
		new_x = (int)(struc->user->pos_x + struc->user->dir_x * struc->user->move_speed);
		new_y = (int)(struc->user->pos_y + struc->user->dir_y * struc->user->move_speed);
		if (!(0 <= new_x && new_x < struc->screen->worldmap.map_width) || !(0 <= new_y && new_y < struc->screen->worldmap.map_height))
			return (1);
		if (!struc->screen->worldmap.worldmap[new_y][new_x])
		{
			struc->user->pos_x += struc->user->dir_x * struc->user->move_speed;
			struc->user->pos_y += struc->user->dir_y * struc->user->move_speed;
		}
	}
	if (key == BACKWARD)
	{
		new_x = (int)(struc->user->pos_x - struc->user->dir_x * struc->user->move_speed);
		new_y = (int)(struc->user->pos_y - struc->user->dir_y * struc->user->move_speed);
		if (!(0 <= new_x && new_x < struc->screen->worldmap.map_width) || !(0 <= new_y && new_y < struc->screen->worldmap.map_height))
			return (1);
		if (!struc->screen->worldmap.worldmap[new_y][new_x])
		{
			struc->user->pos_x -= struc->user->dir_x * struc->user->move_speed;
			struc->user->pos_y -= struc->user->dir_y * struc->user->move_speed;
		}
	}
    if (key == RIGHT)
	{
		new_x = (int)(struc->user->pos_x + struc->user->plane_x * struc->user->move_speed);
		new_y = (int)(struc->user->pos_y + struc->user->plane_y * struc->user->move_speed);
		if (!(0 <= new_x && new_x < struc->screen->worldmap.map_width) || !(0 <= new_y && new_y < struc->screen->worldmap.map_height))
			return (1);
		if (!struc->screen->worldmap.worldmap[new_y][new_x])
		{
			struc->user->pos_x += struc->user->plane_x * struc->user->move_speed;
			struc->user->pos_y += struc->user->plane_y * struc->user->move_speed;
		}
	}
    if (key == LEFT)
	{
		new_x = (int)(struc->user->pos_x - struc->user->plane_x * struc->user->move_speed);
		new_y = (int)(struc->user->pos_y - struc->user->plane_y * struc->user->move_speed);
		if (!(0 <= new_x && new_x < struc->screen->worldmap.map_width) || !(0 <= new_y && new_y < struc->screen->worldmap.map_height))
			return (1);

		if (!struc->screen->worldmap.worldmap[new_y][new_x])
		{
			struc->user->pos_x -= struc->user->plane_x * struc->user->move_speed;
			struc->user->pos_y -= struc->user->plane_y * struc->user->move_speed;
		}

	}
	if (key == ROTATE_LEFT)
	{
		double olddir_x = struc->user->dir_x;
		struc->user->dir_x = struc->user->dir_x * cos(-struc->user->rot_speed) - struc->user->dir_y * sin(-struc->user->rot_speed);
		struc->user->dir_y = olddir_x * sin(-struc->user->rot_speed) + struc->user->dir_y * cos(-struc->user->rot_speed);
		double oldplane_x = struc->user->plane_x;
		struc->user->plane_x = struc->user->plane_x * cos(-struc->user->rot_speed) - struc->user->plane_y * sin(-struc->user->rot_speed);
		struc->user->plane_y = oldplane_x * sin(-struc->user->rot_speed) + struc->user->plane_y * cos(-struc->user->rot_speed);
	}
	if (key == ROTATE_RIGHT)
	{
		double olddir_x = struc->user->dir_x;
		struc->user->dir_x = struc->user->dir_x * cos(struc->user->rot_speed) - struc->user->dir_y * sin(struc->user->rot_speed);
		struc->user->dir_y = olddir_x * sin(struc->user->rot_speed) + struc->user->dir_y * cos(struc->user->rot_speed);
		double oldplane_x = struc->user->plane_x;
		struc->user->plane_x = struc->user->plane_x * cos(struc->user->rot_speed) - struc->user->plane_y * sin(struc->user->rot_speed);
		struc->user->plane_y = oldplane_x * sin(struc->user->rot_speed) + struc->user->plane_y * cos(struc->user->rot_speed);
	}
	if (key == ESC)
		exit(0);
	mlx_clear_window(struc->mlx->mlx, struc->mlx->win);
    execution_main(struc->user, struc->mlx, struc->screen);
    return (0);
}

int	exit_hook(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
}