/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:52:00 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/10 12:17:10 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_draw_start_end(t_game *game, t_data *data, t_ray *ray)
{
	ray->draw_start = -ray->line_height / 2 + data->screen_h / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + data->screen_h / 2;
	if (ray->draw_end >= data->screen_h)
		ray->draw_end = data->screen_h - 1;
	if (ray->side == 0 || ray->side == 1)
		ray->wall_x = game->player->pos_y +
			ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = game->player->pos_x +
			ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	return (0);
}

int		ft_dda(t_ray *ray, t_data *data)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			if (ray->step_x == -1)
				ray->side = 0;
			else
				ray->side = 1;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			if (ray->step_y == -1)
				ray->side = 2;
			else
				ray->side = 3;
		}
		if (data->map[ray->map_x][ray->map_y] == '1')
			ray->hit = 1;
	}
	return (0);
}
