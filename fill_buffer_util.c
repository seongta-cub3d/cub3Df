

#include "cub3D.h"

void    clear_buffer(t_screen *screen)
{
    int y;
    int x;

    y = -1;
    while (++y < height)
    {
        x = -1;
        while (++x < width)
            screen->buffer[y][x] = 0;
    }
    return ;
}

void    init_step_and_sidedist(t_user *user, t_calc *var)
{
    if (var->raydir_x < 0)
	{
		var->step_x = -1;
	    var->side_dist_x = (user->pos_x - var->map_x) * var->delta_dist_x;
	}
	else
	{
		var->step_x = 1;
		var->side_dist_x = (var->map_x + 1.0 - user->pos_x) * var->delta_dist_x;
	}
	if (var->raydir_y < 0)
	{
		var->step_y = -1;
		var->side_dist_y = (user->pos_y - var->map_y) * var->delta_dist_y;
	}
	else
	{
		var->step_y = 1;
		var->side_dist_y = (var->map_y + 1.0 - user->pos_y) * var->delta_dist_y;
	}
    return ;
}


void    init_vars(t_user *user, t_calc *var, int x)
{
    var->camera_x = 2 * x / (double)width - 1;

    var->raydir_x = user->dir_x + user->plane_x * var->camera_x;
    var->raydir_y = user->dir_y + user->plane_y * var->camera_x;

    var->map_x = (int)user->pos_x;
    var->map_y = (int)user->pos_y;

	var->delta_dist_x = (var->raydir_y == 0) ? 0 : ((var->raydir_x == 0) ? 1 : fabs(1 / var->raydir_x));
	var->delta_dist_y = (var->raydir_x == 0) ? 0 : ((var->raydir_y == 0) ? 1 : fabs(1 / var->raydir_y));

    var->hit = 0;
    init_step_and_sidedist(user, var);
    return ;
}

void    shoot_ray(t_calc *var)
{
	while (var->hit == 0)
	{
		if (var->side_dist_x < var->side_dist_y)
		{
			var->side_dist_x += var->delta_dist_x;
			var->map_x += var->step_x;
			var->side = 0;
		}
		else
		{
			var->side_dist_y += var->delta_dist_y;
			var->map_y += var->step_y;
			var->side = 1;
		}
		if (worldmap[var->map_y][var->map_x] > 0)
		{
            var->hit = 1;
		}
	}
    return ;
}

void    fish_eye_correction(t_calc *var, t_user *user)
{
    if (var->side == 0)
		var->perpwall_dist = (var->map_x - user->pos_x + (1 - var->step_x) / 2) / var->raydir_x;
	else
		var->perpwall_dist = (var->map_y - user->pos_y + (1 - var->step_y) / 2) / var->raydir_y;   
}

void    calc_draw_y_coordinates(t_calc *var)
{
    var->line_height = (int)(height / var->perpwall_dist);

	var->draw_start = -var->line_height / 2 + height / 2;
	if (var->draw_start < 0)
		var->draw_start = 0;
	var->draw_end = var->line_height / 2 + height / 2;
	if (var->draw_end >= height)
		var->draw_end = height - 1;
    return ;
}

void    calc_texture_vars(t_calc *var, t_user *user)
{
	if (var->side == 0)
		var->wall_x = user->pos_y + var->perpwall_dist * var->raydir_y;
	else
		var->wall_x = user->pos_x + var->perpwall_dist * var->raydir_x;
	var->wall_x -= floor(var->wall_x);

	var->tex_x = (int)(var->wall_x * (double)texWidth);
	if (var->side == 0 && var->raydir_x > 0)
		var->tex_x = texWidth - var->tex_x - 1;
	if (var->side == 1 && var->raydir_y < 0)
		var->tex_x = texWidth - var->tex_x - 1;

	var->step = 1.0 * texHeight / var->line_height;
	var->tex_pos = (var->draw_start - height / 2 + var->line_height / 2) * var->step;
    return ;
}

int	select_wall_texture(t_calc *var)
{
	//x축과 평행한 벽에 충돌
	if (var->side == 1)
	{
		if (var->raydir_y < 0)
			return (0);
		else if (var->raydir_y > 0)
			return (1);
	}
	//y축과 평행한 벽에 충돌
	if (var->side == 0)
	{
		if (var->raydir_x < 0)
			return (3);
		else if (var->raydir_x > 0)
			return (2);
	}
	return (-1);
}

void    calc_texture_coor(t_calc *var, t_screen *screen, int x)
{
    int y;
    int color;
	int	tex_num;

	tex_num = select_wall_texture(var);
    y = var->draw_start;
    while (y < var->draw_end)
    {
        var->tex_y = (int)var->tex_pos & (texHeight - 1);
        var->tex_pos += var->step;
        color = screen->tex_ary[tex_num].tex_data[texHeight * var->tex_y + var->tex_x];
        if (var->side == 1)
            color = (color >> 1) & 8355711;
        screen->buffer[y][x] = color;
        y++;
    }
    return ;
}

void    calc_texture(t_calc *var, t_user *user, t_screen *screen, int x)
{
    calc_texture_vars(var, user);
    calc_texture_coor(var, screen, x);
}

