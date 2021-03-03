/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 09:54:24 by hugsbord          #+#    #+#             */
/*   Updated: 2021/03/03 10:05:11 by hugsbord         ###   ########.fr       */
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
	game->ray.ray_dir_x = 0;
	game->ray.ray_dir_y = 0;
	game->ray.map_x = 0;
	game->ray.map_y = 0;
	return (0);
}
