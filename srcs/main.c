/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:36:27 by hugsbord          #+#    #+#             */
/*   Updated: 2021/03/18 14:25:09 by hugsbord         ###   ########.fr       */
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
	data->is_space = 0;
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
	game->img->width = 0;
	game->img->height = 0;
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
	game->player->move_speed = 0;
	game->player->rot_speed = 0;
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
	return (SUCCESS);
}

int		ft_get_path(t_data *data, char *line, int i)
{
	int len;
	int j;

	j = 0;
	len = ft_strlen(line);
	i += 2;
	while (ft_isspace(line[i]))
		i++;
	while (ft_isspace(line[len]))
		len--;
	if (!(data->path = (char*)malloc(sizeof(char) * len - i + 1)))
		return (ERROR);
	if (line[i] == '.' && line [i + 1] == '/')
	{
		while (i < len)
		{
			data->path[j] = line[i];
			i++;
			j++;
		}
		data->path[j] = '\0';
	}
	i = 0;
	if (ft_strlen(data->path) == 0)
		return (ERROR);
	while (data->path[i] !=  '\0')
	{
		if (ft_isspace(data->path[i]))
			return (ERROR);
		i++;
	}
	if (ft_check_xpm_ext(data->path) == ERROR)
		return (ft_error(XPM_ERR));
	return (0);
}

int		ft_texture(t_data *data, char *line, int i)
{
	if (ft_get_path(data, line, i) == ERROR)
		return (ERROR);
	if (data->north == 2)
		data->path_no = ft_strdup(data->path);
	else if (data->south == 2)
		data->path_so = ft_strdup(data->path);
	else if (data->east == 2)
		data->path_ea = ft_strdup(data->path);
	else if (data->west == 2)
		data->path_we = ft_strdup(data->path);
	else if (data->sprite == 2)
		data->path_sp = ft_strdup(data->path);
	free(data->path);
	return (0);
}

int		ft_parse_config(t_data *data,  char *line, int i)
{
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == 'R' && line[i + 1] == ' ')
	{
		if (ft_get_res(data, line) == ERROR)
			return (ft_error(RES_ERR));
	}
	else if (line[i] == 'N' && line[i + 1] == 'O')
	{
		data->north += 2;
		if (ft_texture(data, line, i) == ERROR)
			return (ft_error(PATH_ERR));
		data->north -= 1;
	}
	else if (line[i] == 'S' && line[i + 1] == 'O')
	{
		data->south += 2;
		if (ft_texture(data, line, i) == ERROR)
			return (ft_error(PATH_ERR));
		data->south -= 1;
	}
	else if (line[i] == 'W' && line[i + 1] == 'E')
	{
		data->west += 2;
		if (ft_texture(data, line, i) == ERROR)
			return (ft_error(PATH_ERR));
		data->west -= 1;
	}
	else if (line[i] == 'E' && line[i + 1] == 'A')
	{
		data->east += 2;
		if (ft_texture(data, line, i) == ERROR)
			return (ft_error(PATH_ERR));
		data->east -= 1;
	}
	else if (line[i] == 'S' && line[i + 1] == ' ')
	{
		data->sprite += 2;
		if (ft_texture(data, line, i) == ERROR)
			return (ft_error(PATH_ERR));
		data->sprite -= 1;
	}
	else if (line[i] == 'F' && line[i + 1] == ' ')
	{
		data->floor += 2;
		if (ft_get_color(data, line, i) == ERROR)
			return (ft_error(COLOR_ERR));
		data->floor -= 1;
	}
	else if (line[i] == 'C' && line[i + 1] == ' ')
	{
		data->ceiling += 2;
		if (ft_get_color(data, line, i) == ERROR)
			return (ft_error(COLOR_ERR));
		data->ceiling -= 1;
	}
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

void	ft_pos_west_east(t_player *player, t_data *data)
{
	player->dir_x = 0;
	player->plan_y = 0;
	player->pos_x += 0.5;
	if (data->player_dir == WEST)
	{
	player->dir_y = -1;
	player->plan_x = 0.66;
	}
	else
	{
		player->dir_y = 1;
		player->plan_x = -0.66;
	}
}

void	ft_pos_north_south(t_player *player, t_data *data)
{
	player->dir_y = 0;
	player->plan_x = 0;
	player->pos_y += 0.5;
	if (data->player_dir == NORTH)
	{
		player->dir_x = -1;
		player->plan_y = -0.66;
	}
	else
	{
		player->dir_x = 1;
		player->plan_y = 0.66;
	}
}

int		ft_setup_player(t_player *player, t_data *data, t_ray *ray)
{
	player->pos_x = data->player_pos_x;
	player->pos_y = data->player_pos_y;
	player->move_speed = 0.3;
	player->rot_speed = 0.05;
	if (data->player_dir == WEST || data->player_dir == EAST)
		ft_pos_west_east(player, data);
	else if (data->player_dir == NORTH || data->player_dir ==  SOUTH)
		ft_pos_north_south(player, data);
	return (0);
}




void	ft_vert_line(t_game *game, int x, int y1, int y2, int color)
{
	int	y;
	int	z;

	y = y1;
	z = 0;
	game->data.ceiling_col = mlx_get_color_value(game->mlx->mlx_ptr, game->data.ceiling_col);
	game->data.floor_col = mlx_get_color_value(game->mlx->mlx_ptr, game->data.floor_col);
	// walls
	while (y <= y2)
	{
		mlx_pixel_put(game->mlx->mlx_ptr, game->mlx->win, x, y, color);
		y++;
	}
	// ceiling
	while (z < game->ray.draw_start)
	{
		mlx_pixel_put(game->mlx->mlx_ptr, game->mlx->win, x, z,  game->data.ceiling_col);
		z++;
	}
	// floor
	z = game->ray.draw_end + 1;
	while (z < game->data.screen_h)
	{
		mlx_pixel_put(game->mlx->mlx_ptr, game->mlx->win, x, z, game->data.floor_col);
		z++;
	}
}

int		ft_color_tmp(t_game *game, int x)
{
	int color;

	color = 0;
	if (game->data.map[game->ray.map_x][game->ray.map_y] == '1')
	{
		color = 0xFFFF00;
	}
	else if (game->data.map[game->ray.map_x][game->ray.map_y] == '2')
		color = 0x00FFF0;
	else
		color = 0xFFFFF0;
	if (game->ray.side == 1)
		color = color / 2;
	else if (game->ray.side == 2)
		color = color / 3;
	else if (game->ray.side == 3)
		color = color / 4;
	ft_vert_line(game, x, game->ray.draw_start, game->ray.draw_end, color);
//	ft_color_floor_ceil(game);
	return (0);
}

int		ft_set_walls(t_game *game)
{
	t_tex *texture;

	if (game->ray.side == 1)
	{
//		texture = game->tex[0];
	}
	return (SUCCESS);
}

int		ft_draw_start_end(t_game *game)
{
	game->ray.draw_start = -game->ray.line_height / 2 + game->data.screen_h / 2;

	if (game->ray.draw_start < 0)
		game->ray.draw_start = 0;
	game->ray.draw_end = game->ray.line_height / 2 + game->data.screen_h / 2;
	if (game->ray.draw_end >= game->data.screen_h)
		game->ray.draw_end = game->data.screen_h - 1;
	if (game->ray.side == 0 || game->ray.side == 1)
		game->ray.wall_x = game->player->pos_y +
			game->ray.perp_wall_dist * game->ray.ray_dir_y;
	else
		game->ray.wall_x = game->player->pos_x +
			game->ray.perp_wall_dist * game->ray.ray_dir_x;
	game->ray.wall_x -= floor(game->ray.wall_x);
	ft_set_walls(game);
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
		game->ray.z_buffer[x] = game->ray.perp_wall_dist;
		ft_draw_start_end(game);
		ft_color_tmp(game, x);
		x++;
	}
	free(game->ray.z_buffer);
	return (0);
}

int		ft_game_loop(t_game *game, t_data *data)
{
	ft_key_events(game);
	ft_raycasting(game);
	return (0);
}

void	ft_copy_addr_content(int *addr, int *tmp_addr, int width, int height)
{
	int		x;
	int		y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			addr[width * y + x] = tmp_addr[width * y + x];
			x++;
		}
		y++;
	}
}

int		ft_load_texture(char *path, t_mlx *mlx, t_tex *tex)
{
	void	*img_tmp_ptr;
	int		*addr_tmp;
	int		tmp;

	if (!(img_tmp_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, path, &tex->width,
	&tex->height)))
		return (ERROR);
	addr_tmp = (int *)mlx_get_data_addr(img_tmp_ptr, &tmp, &tmp, &tmp);
	tex->addr = (int *)malloc(sizeof(int) * tex->width * tex->height);
	ft_copy_addr_content(tex->addr, addr_tmp, tex->width, tex->height);
	mlx_destroy_image(mlx->mlx_ptr, img_tmp_ptr);
	return (SUCCESS);
}

int		ft_setup_textures(t_game *game, t_data *data, t_mlx *mlx)
{
	t_img	*tex;

	if (ft_load_texture(data->path_no, game->mlx, &game->tex[0]) == ERROR)
		return (ft_error(TEX_ERR));
	if (ft_load_texture(data->path_so, game->mlx, &game->tex[1]) == ERROR)
		return (ft_error(TEX_ERR));
	if (ft_load_texture(data->path_ea, game->mlx, &game->tex[2]) == ERROR)
		return (ft_error(TEX_ERR));
	if (ft_load_texture(data->path_we, game->mlx, &game->tex[3]) == ERROR)
		return (ft_error(TEX_ERR));
	return (SUCCESS);
}

int		ft_game_init(t_game *game, t_data *data)
{
	ft_setup_player(game->player, &game->data, &game->ray);
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
//	printf("OK\n");
	if (ft_game_init(game, data) == ERROR)
		return (ERROR);
//	game->mlx->texture = ft_init_texture(game, data, game->mlx);
//	ft_load_texture(game, data, game->mlx, &game->tex[0]);
//	mlx_hook(game->mlx->win, 17, 1L << 17, ft_exit, game);
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
