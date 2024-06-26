/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajeong <tajeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:29:54 by seongjko          #+#    #+#             */
/*   Updated: 2024/06/26 20:49:52 by tajeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_struc		struc;
	t_user		user;
	t_screen	screen;
	t_mlx		mlx;

	struc.mlx = &mlx;
	struc.user = &user;
	struc.screen = &screen;
	if (argc != 2)
	{
		perror("invalid argument number\n");
		exit(1);
	}
	parsing_map(&screen, argv[1]);
	init_structs(&user, &mlx, &screen);
	execution_main(&user, &mlx, &screen);
	mlx_hook(mlx.win, 2, 1L << 0, &key_press, &struc);
	mlx_hook(mlx.win, 17, 0, &exit_hook, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
