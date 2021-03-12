/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 09:54:24 by hugsbord          #+#    #+#             */
/*   Updated: 2021/03/10 12:27:49 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_init_raycasting(t_game *game)
{
	game->ray.pos_x = 0;
	game->ray.pos_y = 0;
	game->ray.dir_x = 0;
	game->ray.dir_y = 0;
	game->ray.plan_x = 0;
	game->ray.plan_y = 0;
	game->ray.cam_x = 0;
	game->ray.ray_dir_x = 0;
	game->ray.ray_dir_y = 0;
	game->ray.map_x = 0;
	game->ray.map_y = 0;
	game->ray.line_height = 0;
	game->ray.delta_dist_x = 0;
	game->ray.delta_dist_y = 0;
	game->ray.step_x = 0;
	game->ray.step_y = 0;
	game->ray.side_dist_x = 0;
	game->ray.side_dist_y = 0;
	game->ray.hit = 0;
	game->ray.side = 0;
	game->ray.perp_wall_dist = 0;
	game->ray.draw_start = 0;
	game->ray.draw_end = 0;
	game->ray.y = 0;
	game->ray.x = 0;
	return (0);
}
