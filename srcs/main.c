/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:36:27 by hugsbord          #+#    #+#             */
/*   Updated: 2021/02/28 11:29:07 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_init_data(t_data *data)
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

int		ft_init_game(t_game *game)
{
	ft_init_data(&game->data);
	ft_init_img(game);
	ft_init_mlx(game);
	game->sprite = NULL;

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
	printf("\nplayer: x=%d y=%d\n\n", data->player_pos_x, data->player_pos_y);
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
//			while (ft_isspace(data->map[x][y]))
//				y++;
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
//	while (ft_isspace(data->map[x][y]))
//		y++;
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
//	printf("datanb_lines %d", data->nb_lines);
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
//			while (ft_isspace(line[i]))
//				i++;
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
	free(data->map);
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
	{
//		printf("TOP");
		return (ft_error(CONFIG_DOUBLE));
	}
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

void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->size_l + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

int		ft_deal_key(int key, void *param, t_mlx *mlx)
{
	ft_putnbr_fd(key, 1);
//	mlx_pixel_put(mlx->mlx_ptr, mlx->win, 5, 5, 0x00FFF000);
	return (0);
}

int		ft_game_init(t_game *game, t_data *data)
{
	game->mlx->mlx_ptr = mlx_init();
	game->mlx->win =
	game->mlx->win = (mlx_new_window(game->mlx->mlx_ptr, data->screen_w, 
	data->screen_h, "cub3D"));
	game->img->img_ptr = mlx_new_image(game->mlx->mlx_ptr, data->screen_w,
	data->screen_h);
	game->img->addr = mlx_get_data_addr(game->img->img_ptr, &game->img->bpp,
	&game->img->size_l, &game->img->endian);

	return (0);
}

int		ft_game_hook(t_game *game, t_data *data)
{
//	mlx_hook(game->
	return (0);
}

int		ft_game(t_game *game, t_data *data)
{
	ft_game_init(game, data);
	mlx_loop(game->mlx->mlx_ptr);
	return (0);
}

/*int		ft_mlx(t_data *data, t_img *img, t_mlx *mlx)
{
	int x;
	int y;
	x = 0;
	y = 0;
	int z = 0;
	mlx->mlx_ptr = mlx_init();
	mlx->win = (mlx_new_window(mlx->mlx_ptr, data->screen_w, data->screen_h, "cub3D"));
	img->img_ptr = mlx_new_image(mlx->mlx_ptr, data->screen_w, data->screen_h);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_l, &img->endian);
	while (x < data->screen_w)
	{
		int y = 0;
		while (y < data->screen_h / 2)
		{
//			ft_mlx_pixel_put(img, x, y, 0xFFFFF30);
			mlx_pixel_put(mlx->mlx_ptr, mlx->win, x, y, 0x00FFFFFF);
			y++;
		}
		x++;
	}
//	x = 0;
	while (x < data->screen_h)
	{
		int y = 0;
		while (y < 155)
		{
			ft_mlx_pixel_put(img, x, y, 0x00FFF000);
			y++;
		}
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, img->img_ptr, 0, 0);
	mlx_key_hook(mlx->win, deal_key, (void *)0);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}*/

int		main(int argc, char **argv)
{
	t_game		game;

	if (ft_check_arg(argc, argv) != SUCCESS)
		return (ERROR);
	ft_init_game(&game);
	if (ft_parser(argc, argv, &game.data) != SUCCESS)
		return (ERROR);
//	ft_mlx(&game.data, &game.img, &game.mlx);
	ft_game(&game, &game.data);
	return (0);
}
