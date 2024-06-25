
#include "cub3D.h"

void    init_tex_ary(t_mlx *mlx, t_screen *screen)
{
    int     i;

    i = -1;
    while (++i < 4)
    {
        screen->tex_ary[i].img = mlx_xpm_file_to_image(
            mlx->mlx,
            screen->tex_ary[i].tex_path,
            &screen->tex_ary[i].tex_width,
            &screen->tex_ary[i].tex_height);
        if (screen->tex_ary[i].img == NULL)
        {
            perror("mlx_xpm_file_to_image failed\n");
            exit(1);
        }
        screen->tex_ary[i].tex_data = (unsigned int *)mlx_get_data_addr(
            screen->tex_ary[i].img,
            &screen->tex_ary[i].bits_per_pixel,
            &screen->tex_ary[i].size_line,
            &screen->tex_ary[i].endian);
    }
    return ;
}
