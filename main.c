

#include "cub3D.h"

		int	worldmap[mapHeight][mapWidth] =
						{
							{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
							{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
							{4,0,1,0,0,0,0,0,0,83,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
							{4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
							{4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
							{4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
							{4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
							{4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
							{4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
							{4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
							{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
							{4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
							{6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
							{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
							{6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
							{4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
							{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
							{4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
							{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
							{4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
							{4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
							{4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
							{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
							{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
						};


int main()
{
	t_user		user;
	t_screen	screen;
	t_mlx		mlx;

	screen.tex_ary = (t_texture *)malloc(sizeof(t_texture) * 8);
	for (int i = 0; i < 8; i++)
	{
		screen.tex_ary[i].tex_info = (int *)malloc(sizeof(texWidth * texHeight));
	}
	for (int x = 0; x < texWidth; x++)
	{
		for (int y = 0; y < texHeight; y++)
		{
			int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
			int ycolor = y * 256 / texHeight;
			int xycolor = y * 128 / texHeight + x * 128 / texWidth;
			screen.tex_ary[0].tex_info[texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
			screen.tex_ary[1].tex_info[texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			screen.tex_ary[2].tex_info[texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			screen.tex_ary[3].tex_info[texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			screen.tex_ary[4].tex_info[texWidth * y + x] = 256 * xorcolor; //xor green
			screen.tex_ary[5].tex_info[texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
			screen.tex_ary[6].tex_info[texWidth * y + x] = 65536 * ycolor; //red gradient
			screen.tex_ary[7].tex_info[texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
		}
	}


	init_structs(&user, &mlx, &screen);
	execution_main(&user, &mlx, &screen);
	mlx_loop(mlx.mlx);

	return (0);
}