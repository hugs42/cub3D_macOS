/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:36:27 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/02 11:07:13 by hugsbord         ###   ########.fr       */
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
	printf("%d - %s\n", data->nb_lines, data->map[x]);
	while (data->map[x][y] != '\0')
	{
		if (ft_is_not_wall(data->map[x][y]))
		{
//			printf("TOPPPPPPPP\n");
			return (ft_error(MISSING_WALL));
		}
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
//		if ((ft_check_border_left(data, x, y, len) == ERROR))
//			return (ERROR);
		x++;
	}
	x = 0;
	while (x <= data->nb_lines)
	{
		y = ft_strlen(data->map[x]);
//		if ((ft_check_border_right(data, x, y) == ERROR))
//			return (ERROR);
		x++;
	}
	if (ft_check_border_bottom(data) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}

int		ft_parse_info_map(t_data *data, char *line)
{
	static int i = 0;
//	printf("%i*", i);
	i++;
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

void	sort_order(t_pair *orders, int amount)
{
	t_pair	tmp;

	for (int i = 0; i < amount; i++)
	{
		for (int j = 0; j < amount - 1; j++)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
		}
	}
}

int		ft_order_sprite(t_game *game, t_data *data, t_sprites *sprites)
{
	int			i;
	int			j;
	double		tmp;

	i = 0;
	j = 0;
	while (i < data->sprite_nb)
	{
		j  = 0;
		while (j < data->sprite_nb - 1)
		{
			if (sprites->distance[j] < sprites->distance[j + 1])
			{
				tmp = sprites->distance[j];
				sprites->distance[j] = sprites->distance[j + 1];
				sprites->distance[j + 1] = tmp;
				tmp = sprites->order[j];
				sprites->order[j] = sprites->order[j + 1];
				sprites->order[j + 1] = (int)tmp;
			}
			j++;
		}
		i++;

	}
	return (SUCCESS);
}

int		ft_sort_sprites(t_game *game, t_data *data, t_sprites *sprites, t_sprite *sprite)
{
	int i;

	i = 0;
	if (!(sprites->order = (int *)malloc(sizeof(int) * game->data.sprite_nb +1)))
		return (ERROR);
	if (!(sprites->distance = (double *)malloc(sizeof(double) * game->data.sprite_nb+1)))
		return (ERROR);

	while (i <= data->sprite_nb)
	{
		sprites->order[i] = i;
		sprites->distance[i] = ((game->player->pos_x - sprite[i].x) * (game->player->pos_x - sprite[i].x) + (game->player->pos_y - sprite[i].y) * (game->player->pos_y - sprite[i].y));
		i++;
	}
//	sortSprites(sprites->order, sprites->distance, game->data.sprite_nb);
	ft_order_sprite(game, data, sprites);
	return (SUCCESS);
}

int		ft_draw_sprite(t_game *game, t_sprites *sprites)
{
	int		i;
	int		d;
	int		stripe;
	int		tex_x;
	int		tex_y;
	int		color;
	int		tmp;

	tex_x = 0;
	tex_y = 0;
	i = -1;
	d = 0;
	color = 0;
	stripe = sprites->draw_start_x;
	while (stripe < sprites->draw_end_x)
	{
		tex_x = (int)(256 * (stripe - (-sprites->sprite_width / 2 +
		sprites->sprite_screen_x)) * game->tex[4].width / sprites->sprite_width) / 256;
		if (sprites->transform_y > 0 && stripe >= 0 && stripe < game->data.screen_w
		&& sprites->transform_y < game->z_buffer[stripe])
		{
			i = sprites->draw_start_y;
			while (i < sprites->draw_end_y)
			{
				d = (i) * 256 - game->data.screen_h * 128 + sprites->sprite_height * 128;
				tex_y = ((d * game->tex[4].height) / sprites->sprite_height) / 256;
//				color = game->tex[4].addr[game->tex[4].width * tex_y + tex_x];
				color = game->tex[4].addr[game->tex[4].width * tex_y + tex_x];
//				if (game->tex[4].addr[tex_y * game->img->size_l / 4 +
//					tex_x] != -16777216)
//					{
						if ((color & 0x00FFFFFF) != 0)
						{
							game->img->addr[i * game->img->size_l / 4 + stripe] = color;
//							game->img2->addr[i *game->img2->size_l / 4 - stripe] =  0x00FFFFFF;
						}
//				}
				i++;
			}
		}
		stripe++;
	}
	return (SUCCESS);
}
int		ft_sprite(t_game *game, t_sprites *sprites, t_sprite *sprite)
{
	int i;

	i = 0;

	ft_sort_sprites(game, &game->data, sprites, game->sprites->sprite);
	while (i < game->data.sprite_nb)
	{
		sprites->sprite_x = sprite[sprites->order[i]].x - game->player->pos_x;
		sprites->sprite_y = sprite[sprites->order[i]].y - game->player->pos_y;

		sprites->invdet = 1.0 / (game->player->plan_x * game->player->dir_y - game->player->dir_x * game->player->plan_y);

		sprites->transform_x = sprites->invdet * (game->player->dir_y * sprites->sprite_x - game->player->dir_x * sprites->sprite_y);
		sprites->transform_y = sprites->invdet * (-game->player->plan_y * sprites->sprite_x + game->player->plan_x * sprites->sprite_y);

		sprites->sprite_screen_x = (int)(game->data.screen_w / 2) * (1 + sprites->transform_x / sprites->transform_y);
//		#define uDiv 1
//		#define vDiv 1
		#define vMove 0.0
		sprites->v_move_screen = (int)(vMove / sprites->transform_y);
		sprites->sprite_height = abs((int)(game->data.screen_h / sprites->transform_y));
		sprites->draw_start_y = -sprites->sprite_height / 2 + game->data.screen_h / 2 + sprites->v_move_screen;
		if (sprites->draw_start_y < 0)
			sprites->draw_start_y = 0;
		sprites->draw_end_y = sprites->sprite_height / 2 + game->data.screen_h / 2 + sprites->v_move_screen;
		if (sprites->draw_end_y >= game->data.screen_h)
			sprites->draw_end_y = game->data.screen_h - 1;
		sprites->sprite_width = abs((int)(game->data.screen_h / sprites->transform_y));
		sprites->draw_start_x = -sprites->sprite_width / 2 + sprites->sprite_screen_x;
		if (sprites->draw_start_x < 0)
			sprites->draw_start_x = 0;
		sprites->draw_end_x = sprites->sprite_width / 2 + sprites->sprite_screen_x;
//		if (sprites->draw_end_x >= game->data.screen_w)
//			sprites->draw_end_x = game->data.screen_w - 1;
		ft_draw_sprite(game, sprites);
		i++;
	}
	return (SUCCESS);
}

int		ft_init_sprites(t_sprites *sprites)
{
	sprites->sprite_x = 0;
	sprites->sprite_y = 0;
	sprites->invdet = 0;
	sprites->transform_x = 0;
	sprites->transform_y = 0;
	sprites->sprite_screen_x = 0;
	sprites->sprite_height = 0;
	sprites->sprite_width = 0;
	sprites->draw_start_x = 0;
	sprites->draw_start_y = 0;
	sprites->draw_end_x = 0;
	sprites->draw_end_y = 0;
	sprites->pos_x = 0;
	sprites->distance = NULL;
	sprites->order = NULL;
	sprites->sprite->x = 0;
	sprites->sprite->y = 0;
	sprites->v_move_screen = 0;
	return (SUCCESS);
}

int		ft_setup_sprites(t_game *game, t_data *data)//, t_sprites *sprites)
{
	int			x;
	int			y;
	int			i;
//	t_sprites	*sprites;
//	t_sprite	*sprite;

	x = 0;
	y = 0;
	i = 0;
//	printf("OK\n");
	if (!(game->sprites = (t_sprites *)malloc(sizeof(t_sprites))))
		return (ERROR);
	if (!(game->sprites->sprite = (t_sprite *)malloc(sizeof(t_sprite) * game->data.sprite_nb)))
		return (ERROR);
	ft_init_sprites(game->sprites);
	while (x <= data->nb_lines)
	{
		y = 0;
		while (data->map[x][y] != '\0')
		{
			if (data->map[x][y] == '2')
			{
				game->sprites->sprite[i].x = (double)x + 0.5;
				game->sprites->sprite[i].y = (double)y + 0.5;
				i++;
			}
			y++;
		}
		x++;
	}
	return (SUCCESS);
}

void	ft_swaps(t_game *game)
{
	void *tmp;

	tmp = game->img;
	game->img = game->img2;
	game->img2 = tmp;
	tmp = game->img->addr;
	game->img->addr = game->img2->addr;
	game->img2->addr = tmp;
}


int		ft_raycasting(t_game *game)
{
	int x;

	x = 0;
	if (!(game->z_buffer = (double *)malloc(sizeof(double) * game->data.screen_w)))
		return (MALLOC_ERR);
//	if (game->data.sprite_nb > 0)
//		ft_sprite(game, game->sprites, game->sprites->sprite);
	while (x < game->data.screen_w)
	{
		ft_init_rays(&game->data, game->player, &game->ray, x);
		ft_step_side_dist(game->player, &game->ray);
		ft_dda(&game->ray, &game->data);
		ft_calc_perp_height(&game->data, game->player, &game->ray);
		game->z_buffer[x] = game->ray.perp_wall_dist;
		ft_draw_start_end(game, &game->data, &game->ray);
		ft_render_walls(x, game, &game->data, game->tex);
		x++;
	}
	if (game->data.sprite_nb > 0)
		ft_sprite(game, game->sprites, game->sprites->sprite);
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->win, game->img->img_ptr, 0,0);

//mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->win, game->img2->img_ptr, game->tex[4].width,game->tex[4].height);

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
	if (data->sprite_nb > 0)
		ft_setup_sprites(game, &game->data);
	game->mlx->win = (mlx_new_window(game->mlx->mlx_ptr, data->screen_w, 
	data->screen_h, "cub3D"));
	game->img->img_ptr = mlx_new_image(game->mlx->mlx_ptr, data->screen_w,
	data->screen_h);
	game->img2->img_ptr = mlx_new_image(game->mlx->mlx_ptr, data->screen_w,
	data->screen_h);
	game->img->addr = (int*)mlx_get_data_addr(game->img->img_ptr, &game->img->bpp,
	&game->img->size_l, &game->img->endian);
	game->img2->addr = (int*)mlx_get_data_addr(game->img2->img_ptr, &game->img2->bpp,
	&game->img2->size_l, &game->img2->endian);
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
