/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:45:47 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/12 11:28:40 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

void	ft_calc_perp_height(t_data *data, t_player *player, t_ray *ray)
{
	if (ray->side == 0 || ray->side == 1)
		ray->perp_wall_dist = (ray->map_x - player->pos_x + (1 - ray->step_x)
		/ 2) / ray->ray_dir_x;
	else if (ray->side == 2 || ray->side == 3)
		ray->perp_wall_dist = (ray->map_y - player->pos_y + (1 - ray->step_y)
		/ 2) / ray->ray_dir_y;
	ray->line_height = (int)(data->screen_h / ray->perp_wall_dist);
}

int		ft_step_side_dist(t_player *player, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x - player->pos_x + 1.0) *
		ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y - player->pos_y + 1.0) *
		ray->delta_dist_y;
	}
	return (0);
}

void	ft_rays(t_data *data, t_player *player, t_ray *ray, int x)
{
	ray->cam_x = 2 * x / (double)data->screen_w - 1;
	ray->ray_dir_x = player->dir_x + player->plan_x * ray->cam_x;
	ray->ray_dir_y = player->dir_y + player->plan_y * ray->cam_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->line_height = 0;
}

int		ft_raycasting(t_game *game)
{
	int x;

	x = 0;
	game->z_buffer = ft_calloc(game->data.screen_w, sizeof(double));
	while (x < game->data.screen_w)
	{
		ft_rays(&game->data, game->player, game->ray, x);
		ft_step_side_dist(game->player, game->ray);
		ft_dda(game->ray, &game->data);
		ft_calc_perp_height(&game->data, game->player, game->ray);
		game->z_buffer[x] = game->ray->perp_wall_dist;
		ft_draw_start_end(game, &game->data, game->ray);
		ft_render_walls(x, game, &game->data, game->tex);
		x++;
	}
	if (game->data.sprite_nb > 0)
		ft_sprite(game, game->spr, game->spr->s);
	free(game->z_buffer);
	if (game->save == 1)
		ft_bmp(game);
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->win,
	game->img->img_ptr, 0, 0);
	return (0);
}
