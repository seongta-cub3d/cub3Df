
#include "cub3D.h"

void    init_tex_ary(t_mlx *mlx, t_screen *screen)
{
    int     i;

    screen->tex_ary = (t_texture *)malloc(sizeof(t_texture) * 4);
    //parsing to do 
    //-일단 하드코딩으로 구현했으니 파싱부에서 tex_path에 경로 넣어주는 작업 해주면 됨.
    screen->tex_ary[0].tex_path = "./textures/barrel.xpm";
    screen->tex_ary[1].tex_path = "./textures/bluestone.xpm";
    screen->tex_ary[2].tex_path = "./textures/purplestone.xpm";
    screen->tex_ary[3].tex_path = "./textures/redbrick.xpm";

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
