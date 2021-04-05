/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 10:33:54 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/05 14:06:45 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_init_data_1(t_data *data)
{
	data->screen_w = 0;
	data->screen_h = 0;
	data->is_width = 0;
	data->tmp = 0;
	data->len = 0;
	data->max_len = 0;
	data->nb_lines = 0;
	data->nb_total_lines = 0;
	data->map = NULL;
	data->x = 0;
	data->y = 0;
	data->start_map = 0;
	data->res = 0;
	data->floor = 0;
	data->north = 0;
	data->south = 0;
	data->east = 0;
	data->west = 0;
	data->ceiling = 0;
	return (0);
}

int		ft_init_data_2(t_data *data)
{
	data->sprite = 0;
	data->config_done = 0;
	data->config_double = 0;
	data->is_player = 0;
	data->player_dir = 0;
	data->first_space_x = 0;
	data->path = NULL;
	data->path_no = NULL;
	data->path_so = NULL;
	data->path_ea = NULL;
	data->path_we = NULL;
	data->path_sp = NULL;
	data->r = 0;
	data->g = 0;
	data->b = 0;
	data->floor_col = 0;
	data->ceiling_col = 0;
	data->sprite_nb = 0;
	return (0);
}

int		ft_init_tex(t_game *game)
{
	game->tex = ft_calloc(5, sizeof(t_tex));
	return (0);
}

int		ft_init_raycasting(t_game *game)
{
	game->ray = ft_calloc(1, sizeof(t_ray));
	game->ray->cam_x = 0;
	game->ray->ray_dir_x = 0;
	game->ray->ray_dir_y = 0;
	game->ray->map_x = 0;
	game->ray->map_y = 0;
	game->ray->line_height = 0;
	game->ray->delta_dist_x = 0;
	game->ray->delta_dist_y = 0;
	game->ray->step_x = 0;
	game->ray->step_y = 0;
	game->ray->side_dist_x = 0;
	game->ray->side_dist_y = 0;
	game->ray->hit = 0;
	game->ray->side = 0;
	game->ray->perp_wall_dist = 0;
	game->ray->draw_start = 0;
	game->ray->draw_end = 0;
	game->ray->wall_x = 0;
	return (0);
}

int		ft_init_game(t_game *game)
{
	ft_init_data_1(&game->data);
	ft_init_data_2(&game->data);
	ft_init_img(game);
	ft_init_mlx(game);
	ft_init_event(game);
	ft_init_player(game);
	ft_init_tex(game);
	game->spr = NULL;
	game->z_buffer = NULL;
	game->save = 0;
	return (SUCCESS);
}
