
#include "cub3D.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (!(0 <= x && x <= 1920) || !(0 <= y && y <= 1080))
		return ;
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void    draw_buffer(t_mlx *mlx, t_screen *screen)
{
    int y;
    int x;

    y = -1;
    while (++y < height)
    {
        x = -1;
        while (++x < width)
        {
            my_mlx_pixel_put(mlx, x, y, screen->buffer[y][x]);
        }
    }
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
    return ;
}
