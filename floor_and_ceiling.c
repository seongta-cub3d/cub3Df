
#include "cub3D.h"

void    draw_floor(t_calc *var, t_screen *screen, int x)
{
    int y;

    y = var->draw_end;
    while (y < height)
    {
        screen->buffer[y][x] = screen->floor;
        y++;
    }
    return ;
}

void    draw_ceiling(t_calc *var, t_screen *screen ,int x)
{
    int y;

    y = -1;   
    while (++y < var->draw_start)
        screen->buffer[y][x] = screen->ceiling;
    return ;
}

void    draw_floor_and_ceiling(t_calc *var, t_screen *screen, int x)
{
    draw_ceiling(var, screen, x);
    draw_floor(var, screen, x);
    return ;
}