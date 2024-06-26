/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:30:16 by seongjko          #+#    #+#             */
/*   Updated: 2024/06/26 15:42:41 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_structs(t_user *user, t_mlx *mlx, t_screen *screen)
{
	init_user(user, screen);
	init_mlx(mlx);
	init_screen(mlx, screen);
	return ;
}
