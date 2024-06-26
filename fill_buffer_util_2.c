/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_buffer_util_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:07:34 by seongjko          #+#    #+#             */
/*   Updated: 2024/06/26 16:16:27 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_deltadist(t_calc *var)
{
	if (var->raydir_y == 0)
		var->delta_dist_x = 0;
	else
	{
		if (var->raydir_x == 0)
			var->delta_dist_x = 1;
		else
			var->delta_dist_x = fabs(1 / var->raydir_x);
	}
	if (var->raydir_x == 0)
		var->delta_dist_y = 0;
	else
	{
		if (var->raydir_y == 0)
			var->delta_dist_y = 1;
		else
			var->delta_dist_y = fabs(1 / var->raydir_y);
	}
	return ;
}
