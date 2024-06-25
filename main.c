
#include "cub3D.h"

int main(int argc, char *argv[])
{
	t_struc		struc;
	t_user		user;
	t_screen	screen;
	t_mlx		mlx;

	struc.mlx = &mlx;
	struc.user = &user;
	struc.screen = &screen;

	(void)argc;
	parsing_map(&screen, argv[1]);
	init_structs(&user, &mlx, &screen);
	execution_main(&user, &mlx, &screen);
	mlx_hook(mlx.win, 2, 1L << 0, &key_press, &struc);
	mlx_hook(mlx.win, 17, 0, &exit_hook, &mlx);
	mlx_loop(mlx.mlx);

	//프로그램이 끝날 때 해주어야 할 것들
	//1. 각 texture image를 destroy해주어야 함

	return (0);
}
