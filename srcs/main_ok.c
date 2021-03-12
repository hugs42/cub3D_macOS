/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:36:27 by hugsbord          #+#    #+#             */
/*   Updated: 2021/03/08 15:41:39 by hugsbord         ###   ########.fr       */
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
	data->ground = 0;
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
	data->is_space = 0;
	return (0);
}

int		ft_init_img(t_game *game)
{
	if (!(game->img = (t_img *)malloc(sizeof(t_img))))
		return (ERROR);
	game->img->img_ptr = NULL;
	game->img->addr = NULL;
	game->img->size_l = 0;
	game->img->bpp = 0;
	game->img->endian = 0;
	return (SUCCESS);
}

int		ft_init_mlx(t_game *game)
{
	if (!(game->mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		return (ERROR);
	game->mlx->mlx_ptr = NULL;
	game->mlx->win = NULL;
	return (0);
}

int		ft_init_event(t_game *game)
{
	if (!(game->event = (t_event *)malloc(sizeof(t_event))))
		return (ERROR);
	game->event->forward = 0;
	game->event->back = 0;
	game->event->right = 0;
	game->event->left = 0;
	game->event->right_rot = 0;
	game->event->left_rot = 0;
	return (0);
}

int		ft_init_player(t_game *game)
{
	if (!(game->player = (t_player *)malloc(sizeof(t_player))))
		return (ERROR);
	game->player->pos_x = 0;
	game->player->pos_y = 0;
	game->player->dir_x = 0;
	game->player->dir_y = 0;
	game->player->move_speed = 0.05;
	game->player->rot_speed = 0.05;
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
	return (SUCCESS);
}

int		ft_is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

void	ft_fill_spaces(t_data *data)
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

void	ft_get_player(t_data *data, int x, int y)
{
	if (data->map[x][y] == 'N')
		data->player_dir = NORTH;
	else if (data->map[x][y] == 'S')
		data->player_dir = SOUTH;
	else if (data->map[x][y] == 'E')
		data->player_dir = EAST;
	else if (data->map[x][y] == 'W')
		data->player_dir = WEST;
	data->player_pos_x = x;
	data->player_pos_y = y;
//	printf("\nplayer: x=%d y=%d\n\n", data->player_pos_x, data->player_pos_y);
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

int		ft_check_neighborhood(t_data *data, int x, int y)
{
	if ((data->map[x][y - 1] != '1') && (!(ft_is_not_wall(data->map[x][y - 1]))))
		return (ERROR);
	if ((data->map[x][y + 1] != '1') && (!(ft_is_not_wall(data->map[x][y + 1]))))
		return (ERROR);
	if ((data->map[x - 1][y] != '1') && (!(ft_is_not_wall(data->map[x - 1][y]))))
		return (ERROR);
	if ((data->map[x + 1][y] != '1') && (!(ft_is_not_wall(data->map[x + 1][y]))))
		return (ERROR);
	if ((data->map[x - 1][y - 1] != '1') && (!(ft_is_not_wall(data->map[x - 1][y - 1]))))
		return (ERROR);
	if ((data->map[x - 1][y + 1] != '1') && (!(ft_is_not_wall(data->map[x - 1][y + 1]))))
		return (ERROR);
	if ((data->map[x + 1][y - 1] != '1') && (!(ft_is_not_wall(data->map[x + 1][y - 1]))))
		return (ERROR);
	if ((data->map[x + 1][y + 1] != '1') && (!(ft_is_not_wall(data->map[x + 1][y + 1]))))
		return (ERROR);
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
//		while (ft_isspace(data->map[x][y]))
//			y++;
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

int		ft_get_map(t_data *data, char *line)
{
	static int x = 0;
	int y;

	y = 0;
	data->map[x] = NULL;
	if (!(data->map[x] = (char*)malloc(sizeof(char) * data->max_len + 1)))
		return (ERROR);
	while (line[y] != '\0')
	{
		data->map[x][y] = line[y];
		y++;
	}
	data->map[x][y] = '\0';
	x++;
	return (SUCCESS);
}

int		ft_check_space(t_data *data, char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (ft_is_not_wall(line[i]))
			data->is_space = 1;
		i++;
	}
	return (0);
}

int		ft_parse_info_map(t_data *data, char *line)
{
	if (ft_check_char(data, line) == ERROR)
		return (ft_error(WRONG_CHAR));
	ft_check_space(data, line);
	if (data->len > data->max_len)
		data->max_len = data->len;
	return (SUCCESS);
}

int		ft_parse_map(t_data *data, char *line)
{
	int		fd;
	int		ret;
	char	*str;
	int i = 0;

	ret = 1;
	fd = open(line, O_RDONLY);
	if (!(data->map = (char**)malloc(sizeof(char*) * data->nb_lines + 1)))
		return (ft_error(MALLOC_ERR));
	data->nb_total_lines = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		data->nb_total_lines++;
		if (data->nb_total_lines >= data->start_map)
		{
			if (ft_check_empty_line(data, line) == ERROR)
				return (ft_error(EMPTY_LINE));
			i = ft_skip_spaces(line, i);
			if (ft_get_map(data, line) != SUCCESS)
				return (ft_error(MALLOC_ERR));
		}
	}
	if (ft_check_map_size(data) != SUCCESS)
		return (ERROR);
	if (ft_check_border(data) != SUCCESS)
		return (ERROR);
	if (ft_check_wall(data) != SUCCESS)
		return (ERROR);
	if (ft_check_player(data) != SUCCESS)
		return (ERROR);
	ft_fill_spaces(data);
	close(fd);
	i = 0;
	while (i <= data->nb_lines)
	{
		printf(" %s -%d\n", data->map[i], i);
		i++;
	}
//	free(data->map);
	return (SUCCESS);
}

int		ft_parse_config(t_data *data,  char *line, int i)
{
//	printf("ok ");
	static int x = 0;
	x++;
//	printf("line= %d %s\n", x, line);
//	printf("start_map= %d \n", data->start_map);

//	while (ft_isspace(line[i]))
//		i++;
	if (line[i] == 'R' && line[i + 1] == ' ')
		ft_get_res(data, line);
	else if (line[i] == 'N' && line[i + 1] == 'O')
	{
		data->north += 1;
//		ft_textures(data, line);
	}
	else if (line[i] == 'S' && line[i + 1] == 'O')
		data->south += 1;
	else if (line[i] == 'W' && line[i + 1] == 'E')
		data->west += 1;
	else if (line[i] == 'E' && line[i + 1] == 'A')
		data->east += 1;
	else if (line[i] == 'S' && line[i + 1] == ' ')
		data->sprite += 1;
	else if (line[i] == 'F' && line[i + 1] == ' ')
		data->ground += 1;
	else if (line[i] == 'C' && line[i + 1] == ' ')
		data->ceiling += 1;
/*	else if (line[i] == '1' && line[i + 1] == '1' && line[i + 1] == '1')
	
//		data->start_map2 = 1;
		if ((data->config_done == 0) && (line[i] != ' '))
			return ft_error(ERR_ARG_SAVE);
	}*/
	ft_check_config_double(data);
	if (data->config_double != 0)
		return (ft_error(CONFIG_DOUBLE));
	return (SUCCESS);
}

int		ft_parse_line(t_data *data, char *line)
{
	int		len;
	int		i;
	static int		x = 0;

	len = 0;
	i = 0;
//	printf("start_map= %d \n", data->start_map);
	len = ft_strlen(line);
	data->nb_total_lines += 1;
	ft_check_config_done(data);
	i = ft_skip_spaces(line, i);
	if (line[i] == '\n' || line[i] == '\0' || len == 0)
		return (SUCCESS);
	else if (ft_parse_config(data, line, i) != SUCCESS)
		return (ERROR);
	if (data->start_map == 0 && data->config_done == 1)
	{
		if (ft_check_char_first_line(data, line) == ERROR)
			return (ERROR);
		if (ft_start_map(data, line) == ERROR)
			return (ERROR);
	}
	else if (data->start_map != 0 && data->nb_total_lines >= data->start_map)
	{
		i = ft_skip_spaces(line, i);
		if (!(ft_isspace(line[i])))
		{
			if (ft_parse_info_map(data, line) != SUCCESS)
				return (ERROR);
		}
	}
	return (SUCCESS);
}

int		ft_parser(int argc, char **argv, t_data *data)
{
	int			ret;
	char		*line;

	ret = 1;
	if ((data->fd = open(argv[1], O_DIRECTORY) != -1))
		return (ft_error(DIRECTORY));
	if ((data->fd = open(argv[1], O_RDONLY)) < 0)
		return (ft_error(WRONG_FILE));
	while ((ret = get_next_line(data->fd, &line)) > 0)
	{
		if (ft_parse_line(data, line) != SUCCESS)
			return (ERROR);
		free(line);
	}
	if (data->start_map == 0)
		return (ft_error(MISSING_MAP));
	if (data->config_done == 0)
		return (ft_error(WRONG_CONFIG));
	if (data->is_space == 0)
		return (ft_error(ERR_PLAYER));
	if (data->config_double != 0)
		return (ft_error(CONFIG_DOUBLE));
	close(data->fd);
	if (ft_parse_map(data, argv[1]) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}

int		ft_init_player_pos(t_game *game)
{
//	printf("posx%d poxy %d\n", game->data.player_pos_x, game->data.player_pos_y);
	game->player->pos_x = game->data.player_pos_x;
	game->player->pos_y = game->data.player_pos_y;
/*	if (game->data.player_dir == NORTH || game->data.player_dir == SOUTH)
	{
		game->ray.dir_x = -1;
		if (game->data.player_dir == NORTH)
		{
			game->ray.dir_y = 0;
			game->ray.plan_x = 0;
			game->ray.plan_y = 0.66;
		}
//		else if  (game->data.player_dir == SOUTH)
//			game->ray.dir_y = 1;
	}
	else if (game->data.player_dir == EAST || game->data.player_dir == WEST)
	{

	}*/
	return (0);
}

void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->size_l + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

int		ft_deal_key(int key, t_game *game)
{
//	if (key == 
//	ft_putnbr_fd(key, 1);
//	ft_mlx_pixel_put(game->img, 5, 5, 0x00FFF000);
//	mlx_pixel_put(game->mlx->mlx_ptr, game->mlx->win, 5, 5, 0x00FFF000);
	return (0);
}

int		ft_game_init(t_game *game, t_data *data)
{
	ft_init_player_pos(game);
	ft_init_ray(game);
	game->mlx->mlx_ptr = mlx_init();
	game->mlx->win = (mlx_new_window(game->mlx->mlx_ptr, data->screen_w, 
	data->screen_h, "cub3D"));
	game->img->img_ptr = mlx_new_image(game->mlx->mlx_ptr, data->screen_w,
	data->screen_h);
	game->img->addr = mlx_get_data_addr(game->img->img_ptr, &game->img->bpp,
	&game->img->size_l, &game->img->endian);
	return (0);
}

/*void	ft_draw(t_game *game, int x)
{
	int i;

	i = 0;
	while (i < game->ray.draw_start)
	{
		*(game->img->addr + (i * game->data.screen_w) + x) =  0x0000FF;;
		i++;
	}
	while (i < game->ray.draw_end)
	{
		en->tex.y = (int)en->tex.pos &
		(en->mlx.texture[en->tex.num].height - 1);
		en->tex.pos += en->tex.step;
		en->color = en->mlx.texture[en->tex.num].data[en->mlx.texture
		[en->tex.num].height * en->tex.y + en->tex.x];
		*(en->mlx.img.data + (i * g_config.r.x) + x) = en->color;
		i++;
	}
	while (i < g_config.r.y - 1)
	{
		*(en->mlx.img.data + (i * g_config.r.x) + x) = g_config.f.rgb_int;
		i++;
	}
}*/

void	ft_vert_line(t_game *game, int x, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
//		printf("OK ");
		mlx_pixel_put(game->mlx->mlx_ptr, game->mlx->win, x, y, color);
		y++;
	}
}

int		ft_color(t_game *game, int x)
{
	int color;

	color = 0;
//	printf("OK");
	if (game->data.map[game->ray.map_x][game->ray.map_y] == 1)
		color = 0xFF0000;
	else if (game->data.map[game->ray.map_x][game->ray.map_y] == 2)
	{
		color = 0x00FFF0;
	}
	else if (game->data.map[game->ray.map_x][game->ray.map_y] == 3)
		color = 0x0000FF;
	else if (game->data.map[game->ray.map_x][game->ray.map_y] == 4)
		color = 0xFFFFFF;
	else
		color = 0xFFFF00;
	if (game->ray.side == 1)
			color = color / 2;
	ft_vert_line(game, x, game->ray.draw_start, game->ray.draw_end, color);
	return (0);
}

/*static void		ft_set_wall(t_game *game)
{
	int		text_x;
	t_image	*texture;

	texture = game->we_texture;
	if (ray->side == 1)
		texture = game->ea_texture;
	else if (ray->side == 2)
		texture = game->no_texture;
	else if (ray->side == 3)
		texture = game->so_texture;
	text_x = (int)(ray->wall_x * (double)texture->width);
	if ((ray->side == 0 || ray->side == 1) && ray->ray_dir_x > 0)
		text_x = texture->width - text_x - 1;
	if ((ray->side == 2 || ray->side == 3) && ray->ray_dir_y < 0)
		text_x = texture->width - text_x - 1;
	ray->text_x = text_x;
	set_texture_on_image(game, texture, ray);


void		ftt_pixel_put(t_img *img, int x, int y, int color)
	{
		unsigned char *src;
		unsigned char r;
		unsigned char g;
		unsigned char b;

		src = (unsigned char *)&color;
		r = src[0];
		g = src[1];
		b = src[2];
		img->addr[y * img->size_l + x * img->bpp / 8] = r;
		img->addr[y * img->size_l + x * img->bpp / 8 + 1] = g;
		img->addr[y * img->size_l + x * img->bpp / 8 + 2] = b;
	}

void		set_color_on_image(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->ray.draw_start)
		ftt_pixel_put(game->img, game->ray.x, y++, 184,113,39);
	y = ray->draw_end + 1;
	while (y < game->window->height)
		ftt_pixel_put(game->image, game->ray-.x, y++, 54,198,227);
}*/


void		draw_col(t_game *game)
{
	game->ray.draw_start = game->ray.line_height / 2 + game->data.screen_h / 2;
	game->ray.draw_end = game->ray.line_height / 2 + game->data.screen_h / 2;
	if (game->ray.draw_start < 0)
		game->ray.draw_start = 0;
	if (game->ray.draw_end >= game->data.screen_h)
		game->ray.draw_end = game->data.screen_h - 1;
	if (game->ray.side == 0 || game->ray.side == 1)
		game->ray.wall_x = game->player->pos_y +
			game->ray.perp_wall_dist * game->ray.ray_dir_y;
	else
		game->ray.wall_x = game->player->pos_x +
			game->ray.perp_wall_dist * game->ray.ray_dir_x;
	game->ray.wall_x -= floor(game->ray.wall_x);
//	set_wall(game, ray);
//	set_color_on_image(game);
}

/*static void	ft_draw_start_end(t_game *game)
{
	game->ray.draw_start = -game->ray.line_height / 2 + game->data.screen_h / 2;
	if (game->ray.draw_start < 0)
		game->ray.draw_start = 0;
	game->ray.draw_end = game->ray.line_height / 2 + game->data.screen_h / 2;
	if (game->ray.draw_end >= game->data.screen_h || game->ray.draw_end <= 0)
		game->ray.draw_end = game->data.screen_h - 1;
}*/

int		ft_draw_start_end(t_game *game)
{
	game->ray.line_height = (int)(game->data.screen_h / game->ray.perp_wall_dist);
	game->ray.draw_start = -game->ray.line_height / 2 + game->data.screen_h / 2;

	if (game->ray.draw_start < 0)
		game->ray.draw_start = 0;
	game->ray.draw_end = game->ray.line_height / 2 + game->data.screen_h / 2;
	if (game->ray.draw_end >= game->data.screen_h)
		game->ray.draw_end = game->data.screen_h - 1;
	return (0);
}


/*int		ft_dda(t_game *game)
{
	game->ray.hit = 0;
	while (game->ray.hit == 0)
	{
		if (game->ray.side_dist_x < game->ray.side_dist_y)
		{
			game->ray.side_dist_x += game->ray.delta_dist_x;
			game->ray.map_x += game->ray.step_x;
			if (game->ray.step_x == -1)
				game->ray.side = 0;
			else
				game->ray.side = 1;
		}
		else
		{
			game->ray.side_dist_y += game->ray.delta_dist_y;
			game->ray.map_y += game->ray.step_y;
			if (game->ray.step_y == -1)
				game->ray.side = 2;
			else
				(game->ray.side = 3);
		}
		if (game->data.map[game->ray.map_x][game->ray.map_y] >= 1 &&
		game->data.map[game->ray.map_x][game->ray.map_y] != 2)
			game->ray.hit = 1;
		}
	if (game->ray.side == 0)
		game->ray.perp_wall_dist = (game->ray.map_x - game->ray.pos_x + (1 - game->ray.step_x) / 2) / game->ray.ray_dir_x;
	else
		game->ray.perp_wall_dist = (game->ray.map_y - game->ray.pos_y + (1 - game->ray.step_y) / 2) / game->ray.ray_dir_y;
	return (0);
}*/

int		ft_dda(t_game *game)
{
	game->ray.hit = 0;
	while (game->ray.hit == 0)
	{
		if (game->ray.side_dist_x < game->ray.side_dist_y)
		{
			game->ray.side_dist_x += game->ray.delta_dist_x;
			game->ray.map_x += game->ray.step_x;
			game->ray.side = 0;
		}
		else
		{
			game->ray.side_dist_y += game->ray.delta_dist_y;
			game->ray.map_y += game->ray.step_y;
			game->ray.side = 1;
		}
		if (game->data.map[game->ray.map_x][game->ray.map_y] == '1')
			game->ray.hit = 1;
		}
	if (game->ray.side == 0)
		game->ray.perp_wall_dist = (game->ray.map_x - game->ray.pos_x + (1 - game->ray.step_x) / 2) / game->ray.ray_dir_x;
	else
		game->ray.perp_wall_dist = (game->ray.map_y - game->ray.pos_y + (1 - game->ray.step_y) / 2) / game->ray.ray_dir_y;
	game->ray.line_height = (int)(game->data.screen_h / game->ray.perp_wall_dist);
	return (0);
}


static void	ft_get_delta_dist(t_game *game)
{
/*	if (game->ray.ray_dir_y == 0)
		game->ray.delta_dist_x = 0;
	else if (game->ray.ray_dir_x == 0)
		game->ray.delta_dist_x = 1;
	else
		game->ray.delta_dist_x = fabs(1 / game->ray.ray_dir_x);
	if (game->ray.ray_dir_x == 0)
		game->ray.delta_dist_y = 0;
	else if (game->ray.ray_dir_y == 0)
		game->ray.delta_dist_y = 1;
	else
		game->ray.delta_dist_y = fabs(1 / game->ray.ray_dir_y);*/
}

static void	ft_get_perp_and_height(t_game *game)
{
	if (game->ray.side == 0 || game->ray.side == 1)
		game->ray.perp_wall_dist = (game->ray.map_x - game->player->pos_x + (1 - game->ray.step_x)
		/ 2) / game->ray.ray_dir_x;
	else if (game->ray.side == 2 || game->ray.side == 3)
		game->ray.perp_wall_dist = (game->ray.map_y - game->player->pos_y + (1 - game->ray.step_y)
		/ 2) / game->ray.ray_dir_y;
	game->ray.line_height = (int)(game->data.screen_h / game->ray.perp_wall_dist);
	game->ray.z_buffer[game->ray.x] = game->ray.perp_wall_dist;
}

int		ft_step_side_dist(t_game *game)
{
//	game->ray.delta_dist_x = fabs(1 / game->ray.ray_dir_x);
//	game->ray.delta_dist_y = fabs(1 / game->ray.ray_dir_y);
	if (game->ray.ray_dir_x < 0)
	{
		game->ray.step_x = -1;
		game->ray.side_dist_x = (game->player->pos_x - game->ray.map_x) * game->ray.delta_dist_x; 
	}
	else
	{
		game->ray.step_x = 1;
		game->ray.side_dist_x = ( game->ray.map_x -  game->player->pos_x + 1.0) * game->ray.delta_dist_x; 
	}
	if (game->ray.ray_dir_y < 0)
	{
		game->ray.step_y = -1;
		game->ray.side_dist_y = (game->player->pos_y - game->ray.map_y) * game->ray.delta_dist_y; 
	}
	else
	{
		game->ray.step_y = 1;
		game->ray.side_dist_y = (game->ray.map_y -  game->player->pos_y + 1.0) * game->ray.delta_dist_y; 
	}
	return (0);
}

int		ft_setup(t_game *game)
{
//	game->ray.pos_x = 12;
//	game->ray.pos_y = 5;
	game->ray.dir_x = -1;
	game->ray.dir_y = 0;
	game->ray.plan_x = 0;
 	game->ray.plan_y = 0.66;
	return (0);
}

int		ft_raycasting(t_game *game)
{
	int x;

	x = 0;
//	printf("%d \n", game->data.screen_w);
//	printf("posx%d poxy %d\n", game->player->pos_x, game->player->pos_x);
	ft_setup(game);
	if (!(game->ray.z_buffer = (double *)malloc(sizeof(double) * game->data.screen_w)))
		return (MALLOC_ERR);
	ft_bzero(game->ray.z_buffer, sizeof(double) * game->data.screen_h);
	while (x < game->data.screen_w)
	{
//		ft_init_raycasting(game);
		game->ray.cam_x = 2 * x / (double)game->data.screen_w - 1;
		game->ray.ray_dir_x = game->player->dir_x + game->player->plan_x * game->ray.cam_x;
		game->ray.ray_dir_y = game->player->dir_y + game->player->plan_y * game->ray.cam_x;
//		ft_get_delta_dist(game);
		game->ray.map_x = (int)game->player->pos_x;
		game->ray.map_y = (int)game->player->pos_y;
		game->ray.delta_dist_x = fabs(1 / game->ray.ray_dir_x);
		game->ray.delta_dist_y = fabs(1 / game->ray.ray_dir_y);
//		game->ray.line_height = 0;
		game->ray.y = 0;
		ft_step_side_dist(game);
		ft_dda(game);
		ft_get_perp_and_height(game);
		game->ray.z_buffer[x] = game->ray.perp_wall_dist;
		ft_draw_start_end(game);
		ft_color(game, x);
//		game->ray.ray_x++;
		x++;
	}
	return (0);
}

/*int		ft_destroy_create_image(t_game *game)
{
	mlx_destroy_image(game->mlx->mlx_ptr, game->mlx->img);
	en->mlx.img.ptr = mlx_new_image(en->mlx.ptr, g_config.r.x, g_config.r.y);
	en->mlx.img.data = (int*)mlx_get_data_addr(en->mlx.img.ptr,
	&en->mlx.img.bpp, &en->mlx.img.endian, &en->mlx.img.size_line);
}*/

int		ft_game_loop(t_game *game, t_data *data)
{
	ft_key_events(game);
//	mlx_clear_window(game->mlx->win, game->mlx->mlx_ptr);
	ft_raycasting(game);
	return (0);
}


int		ft_game(t_game *game, t_data *data)
{
	ft_game_init(game, data);
	mlx_key_hook(game->mlx->win, ft_deal_key, game);
	mlx_hook(game->mlx->win, KEY_PRESS, 1L << 0, ft_press_key, game);
	mlx_hook(game->mlx->win, KEY_RELEASE, 1l << 1, ft_release_key, game);
//	mlx_hook(game->mlx->win, 17, 1L << 17, ft_exit, game);
	mlx_loop_hook(game->mlx->mlx_ptr, &ft_game_loop, game);
	mlx_loop(game->mlx->mlx_ptr);
	return (0);
}

int		main(int argc, char **argv)
{
	t_game		game;

	if (ft_check_arg(argc, argv) != SUCCESS)
		return (ERROR);
	ft_init_game(&game);
	if (ft_parser(argc, argv, &game.data) != SUCCESS)
		return (ERROR);
	ft_game(&game, &game.data);
	return (0);
}
