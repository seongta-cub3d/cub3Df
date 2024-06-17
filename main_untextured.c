#include "cub3D.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (!(0 <= x && x <= 1920) || !(0 <= y && y <= 1080))
		return ;
	
	dst = mlx->img_instance_addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	initiate_mlx_setting(t_mlx *mlx)
{
	mlx->mlx_instance_addr = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx_instance_addr, 1920, 1080, "cub3D");
	mlx->img_instance = mlx_new_image(mlx->mlx_instance_addr, 1920, 1080);
	mlx->img_instance_addr = mlx_get_data_addr(mlx->img_instance, &mlx->bits_per_pixel, \
	&mlx->line_length, &mlx->endian);
}

void	draw_vertical_line(t_mlx *mlx, int x, int drawStart, int drawEnd, int side)
{
	unsigned int red_bright;
	unsigned int red_dark;

	red_bright = 0x00FF0000;
	red_dark = 0x00FF0000 >> 1;

	while (drawStart <= drawEnd)
	{
		if (side == 1)
			my_mlx_pixel_put(mlx, x, drawStart, red_dark);
		else
			my_mlx_pixel_put(mlx, x, drawStart, red_bright);
		drawStart++;
	}
	return ;
}

int main()
{
    //mlx preset
    t_mlx   mlx;
    initiate_mlx_setting(&mlx);

    //Raycasting preset
    int height = 1080; //창의 높이
    int width = 1920; //창의 너비

    double posX = 22, posY = 12; //플레이어의 위치벡터
    double dirX = -1, dirY = 0; //player의 시선 방향을 나타내는 방향벡터
    double planeX = 0, planeY = 0.66; //카메라 평면벡터(시야에는 무조건 수직)

    // double time = 0; //현재 프레임의 시간
    // double oldTime = 0; //그 전 프레임의 시간

    for (int x = 0; x < width; x++)
    {
        //////////////////////////////////////////////////////////////////
        //////////////////////////각종 변수 초기화////////////////////////////
        //////////////////////////////////////////////////////////////////
        //광선의 목표 지점 설정
        double cameraX = 2 * x / (double)width - 1; //카메라평면에서의 x좌표

        //광선의 방향 설정
        double rayDirX = dirX + planeX * cameraX; //광선의 X축 방향벡터
        double rayDirY = dirY + planeY * cameraX; //광선의 y축 방향벡터

        //광선이 벽에 부딪쳤을 경우의 위치 좌표를 저장(처음에는 player의 위치좌표로 초기화)
        int mapX = (int)posX;
        int mapY = (int)posY;

        //광선이 player로부터 출발해 첫 번째 x면 or y면을 만나기까지의 거리
        double sideDistX;
        double sideDistY;

        // double deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : fabs(1 / rayDirX));
        // double deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : fabs(1 / rayDirY));

        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

        //Camera 평면에서 벽까지의 수직 거리
        double perpWallDist;

        //광선이 x or y 방향으로 (1 or -1) 이동할 때의 방향을 나타냄
        int stepX;
        int stepY;

        int hit = 0; //광선이 벽에 부딪쳤는지 아닌지를 나타냄
        int side; //부딪친 면이 x면인지 y면인지를 나타냄

        //*주의: 2차원 배열이므로 y축의 증가 방향은 아래쪽 방향이다. 아무 생각없이 일반적인 그래프에서 사용하는
        //2차원 좌표계 생각하면 큰일난다.

        //stepX & Y, sideDistX & Y 설정
        if(rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }
        if(rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }

        //////////////////////////////////////////////////////////////////
        //////////////////////////DDA algorithm///////////////////////////
        //////////////////////////////////////////////////////////////////
        //광선이 벽에 부딪칠 때까지 DDA 알고리즘을 진행하는데 벽에 부딪치면 끝.
		//이 반복문이 끝나면 mapX & Y에는 부딪친 시점의 좌표가 저장된다.
		while (!hit)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (worldMap[mapX][mapY] > 0)
                hit = 1;
        }
        //////////////////////////////////////////////////////////////////
        /////////////////////////////벽 그리기//////////////////////////////
        //////////////////////////////////////////////////////////////////

		//카메라 평면에서 벽까지의 수직 거리 구하기(원리는 잘 모르겠음)
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		//벽이 그려지는 영역의 높이를 설정
		int wallHeight = (int)(height / perpWallDist);

		//광선이 충돌한 x좌표에서 y축 방향으로 얼마나 벽을 그릴지 결정
		int drawStart = (height / 2) - (wallHeight / 2);
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = (height / 2) + (wallHeight / 2);
		if(drawEnd >= height)
			drawEnd = height - 1;
		draw_vertical_line(&mlx, x, drawStart, drawEnd, side);
    }

	mlx_put_image_to_window(mlx.mlx_instance_addr, mlx.mlx_win, mlx.img_instance, 0, 0);
	mlx_loop(mlx.mlx_instance_addr);
    return (0);
}