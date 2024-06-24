
#include "cub3D.h"

int key_press(int key, t_struc *struc)
{
    if (key == FORWARD)
	{
		if (!worldmap[(int)(struc->user->pos_x + struc->user->dir_x * struc->user->move_speed)][(int)(struc->user->pos_y)])
			struc->user->pos_x += struc->user->dir_x * struc->user->move_speed;
		if (!worldmap[(int)(struc->user->pos_x)][(int)(struc->user->pos_y + struc->user->dir_y * struc->user->move_speed)])
			struc->user->pos_y += struc->user->dir_y * struc->user->move_speed;
	}
	if (key == BACKWARD)
	{
		if (!worldmap[(int)(struc->user->pos_x - struc->user->dir_x * struc->user->move_speed)][(int)(struc->user->pos_y)])
			struc->user->pos_x -= struc->user->dir_x * struc->user->move_speed;
		if (!worldmap[(int)(struc->user->pos_x)][(int)(struc->user->pos_y - struc->user->dir_y * struc->user->move_speed)])
			struc->user->pos_y -= struc->user->dir_y * struc->user->move_speed;
	}
    if (key == RIGHT)
	{
		if (!worldmap[(int)(struc->user->pos_x + struc->user->plane_x * struc->user->move_speed)][(int)(struc->user->pos_y)])
			struc->user->pos_x += struc->user->plane_x * struc->user->move_speed;
		if (!worldmap[(int)(struc->user->pos_x)][(int)(struc->user->pos_y + struc->user->plane_y * struc->user->move_speed)])
			struc->user->pos_y += struc->user->plane_y * struc->user->move_speed;
	}
    if (key == LEFT)
	{
		if (!worldmap[(int)(struc->user->pos_x - struc->user->plane_x * struc->user->move_speed)][(int)(struc->user->pos_y)])
			struc->user->pos_x -= struc->user->plane_x * struc->user->move_speed;
		if (!worldmap[(int)(struc->user->pos_x)][(int)(struc->user->pos_y - struc->user->plane_y * struc->user->move_speed)])
			struc->user->pos_y -= struc->user->plane_y * struc->user->move_speed;
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
