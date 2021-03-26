/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:36:27 by hugsbord          #+#    #+#             */
/*   Updated: 2021/03/26 11:22:40 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

void	ft_replace_spaces(t_data *data)
{
	int x;
	int y;
	int len;

	x = 0;
	y = 0;
	len = 0;
	while (x <= data->nb_lines)
	{
		y = 0;
		len = ft_strlen(data->map[x]);
		while (y <= len)
		{
			if (ft_isspace(data->map[x][y]))
				data->map[x][y] = '1';
			if (ft_is_player(data->map[x][y]))
				data->map[x][y] = '0';
			y++;
		}
		if (len < data->max_len)
		{
			while (len < data->max_len)
			{
				data->map[x][len] = '1';
				len++;
			}
			data->map[x][len] =  '\0';
		}
		x++;
	}
}

int		ft_check_player(t_data *data)
{
	static		int x;
	int			y;

	y = 0;
	while (x <= data->nb_lines)
	{
		y = 0;
		while (data->map[x][y] != '\0')
		{
			if (data->map[x][y] == 'N' || data->map[x][y] == 'S' ||
			data->map[x][y] == 'E' || data->map[x][y] == 'W')
			{
				data->is_player++;
				ft_get_player(data, x, y);
			}
			y++;
		}
		x++;
	}
	if (data->is_player == 0 || data->is_player > 1)
		return (ft_error(ERR_PLAYER));
	return (SUCCESS);
}

int		ft_check_wall(t_data *data)
{
	static int x;
	int y;

	x = 0;
	y = 0;
	while (x <= data->nb_lines)
	{
		y = 0;
		while (data->map[x][y] != '\0')
		{
			y = ft_skip_spaces2(data, x, y);
			if (ft_is_not_wall(data->map[x][y]))
				if (ft_check_neighborhood(data, x, y) != SUCCESS)
					return (ft_error(MISSING_WALL));
			y++;
		}
		x++;
	}
	return (SUCCESS);
}

int		ft_check_border_bottom(t_data *data)
{
	int x;
	int y;

	x = data->nb_lines;
	y = 0;
	y = ft_skip_spaces2(data, x, y);
	while (data->map[x][y] != '\0')
	{
		if (ft_is_not_wall(data->map[x][y]))
			return (ft_error(MISSING_WALL));
		y++;
	}
	return (SUCCESS);
}

int		ft_check_border_left(t_data *data, int x, int y, int len)
{
	while (y <= len)
	{
		y = ft_skip_spaces2(data, x, y);
		if (ft_is_not_wall(data->map[x][y]))
		{
			if (data->map[x][y - 2] == '1')
				break;
			if (data->map[x][y - 1] != '1')
				return (ft_error(MISSING_WALL));
			if (data->map[x - 1][y - 1] != '1')
				return (ft_error(MISSING_WALL));
			else
				break;
		}
		y++;
	}
	return (SUCCESS);
}

int		ft_check_border_right(t_data *data, int x, int y)
{
	while (y >= 0)
	{
		while (ft_isspace(data->map[x][y]))
			y--;
		if (ft_is_not_wall(data->map[x][y]))
		{
			if (data->map[x][y + 2] == '1')
				break;
			if (data->map[x][y + 1] != '1')
				return (ft_error(MISSING_WALL));
			if (data->map[x - 1][y + 1] != '1')
				return (ft_error(MISSING_WALL));
			else
				break;
		}
		y--;
	}
	return (SUCCESS);
}

int		ft_check_border(t_data *data)
{
	int x;
	int y;
	int len;

	x = 0;
	y = 0;
	len = 0;
	while (x <= data->nb_lines)
	{
		y = 0;
		len = ft_strlen(data->map[x]);
		if ((ft_check_border_left(data, x, y, len) == ERROR))
			return (ERROR);
		x++;
	}
	x = 0;
	while (x <= data->nb_lines)
	{
		y = ft_strlen(data->map[x]);
		if ((ft_check_border_right(data, x, y) == ERROR))
			return (ERROR);
		x++;
	}
	if (ft_check_border_bottom(data) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}

int		ft_parse_info_map(t_data *data, char *line)
{
	if (ft_check_char(data, line) == ERROR)
		return (ft_error(WRONG_CHAR));
//	ft_check_space(data, line);
	if (data->len > data->max_len)
		data->max_len = data->len;
	return (SUCCESS);
}

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
		// avance jusqu'a la prochaine case
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
		// Check si le rayon a touche un mur
		if (data->map[ray->map_x][ray->map_y] == '1')
			ray->hit = 1;
	}
	return (0);
}

void	ft_calc_perp_height(t_data *data, t_player *player, t_ray *ray)
{
	// Calcul la distance projetee dans la direction de la camera
	if (ray->side == 0 || ray->side == 1)
		ray->perp_wall_dist = (ray->map_x - player->pos_x + (1 - ray->step_x)
		/ 2) / ray->ray_dir_x;
	else if (ray->side == 2 || ray->side == 3)
		ray->perp_wall_dist = (ray->map_y - player->pos_y + (1 - ray->step_y)
		/ 2) / ray->ray_dir_y;
	// Calcul la hauteur de la ligne a dessiner
	ray->line_height = (int)(data->screen_h / ray->perp_wall_dist);
	ray->z_buffer[ray->x] = ray->perp_wall_dist;
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

void	ft_init_rays(t_data *data, t_player *player, t_ray *ray, int x)
{
	ray->cam_x = 2 * x / (double)data->screen_w - 1;
	ray->ray_dir_x = player->dir_x + player->plan_x * ray->cam_x;
	ray->ray_dir_y = player->dir_y + player->plan_y * ray->cam_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->line_height = 0;
	ray->y = 0;
}


int		ft_raycasting(t_game *game)
{
	int x;

	x = 0;
	if (!(game->ray.z_buffer = (double *)malloc(sizeof(double) * game->data.screen_w)))
		return (MALLOC_ERR);
	ft_bzero(game->ray.z_buffer, sizeof(double) * game->data.screen_h);
	while (x < game->data.screen_w)
	{
		ft_init_rays(&game->data, game->player, &game->ray, x);
		ft_step_side_dist(game->player, &game->ray);
		ft_dda(&game->ray, &game->data);
		ft_calc_perp_height(&game->data, game->player, &game->ray);
//		game->ray.z_buffer[x] = game->ray.perp_wall_dist;
		ft_draw_start_end(game, &game->data, &game->ray);
		ft_render_walls(x, game, &game->data, game->tex);
		x++;
	}
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->win, game->img->img_ptr, 0,0);
//	free(game->ray.z_buffer);
	return (0);
}

int		ft_game_loop(t_game *game, t_data *data)
{
	ft_key_events(game);
	ft_raycasting(game);
	return (0);
}

int		ft_game_init(t_game *game, t_data *data)
{
	ft_setup_player(game->player, &game->data);
	ft_init_raycasting(game);
	game->mlx->mlx_ptr = mlx_init();
	ft_setup_textures(game, data, game->mlx);
	game->mlx->win = (mlx_new_window(game->mlx->mlx_ptr, data->screen_w, 
	data->screen_h, "cub3D"));
	game->img->img_ptr = mlx_new_image(game->mlx->mlx_ptr, data->screen_w,
	data->screen_h);
	game->img->addr = (int*)mlx_get_data_addr(game->img->img_ptr, &game->img->bpp,
	&game->img->size_l, &game->img->endian);
	return (SUCCESS);
}

int		ft_game(t_game *game, t_data *data)
{
	if (ft_game_init(game, data) == ERROR)
		return (ERROR);
	mlx_hook(game->mlx->win, 17, 1L << 17, ft_exit, game);
	mlx_loop_hook(game->mlx->mlx_ptr, &ft_game_loop, game);
	mlx_hook(game->mlx->win, KEY_PRESS, 1L << 0, ft_press_key, game);
	mlx_hook(game->mlx->win, KEY_RELEASE, 1l << 1, ft_release_key, game);
	mlx_loop(game->mlx->mlx_ptr);
	return (SUCCESS);
}

int		main(int argc, char **argv)
{
	t_game		game;

	if (ft_check_arg(argc, argv) != SUCCESS)
		return (ERROR);
	ft_init_game(&game);
	if (ft_parser(argc, argv, &game.data) != SUCCESS)
		return (ERROR);
	if (ft_game(&game, &game.data) != SUCCESS)
		return (ERROR);
	return (0);
}
