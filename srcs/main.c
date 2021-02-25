/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:36:27 by hugsbord          #+#    #+#             */
/*   Updated: 2021/02/25 11:16:23 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_init_map(t_data *data)
{
//	if (!(data->map = malloc(sizeof(t_map))))
//		return (ERROR);
	return (0);
}

int		ft_init_data(t_data *data)
{
	data->screen_w = WIN_W;
	data->screen_h = WIN_H;
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
	data->is_player = 0;
	data->player_dir = 0;
	//	ft_init_sprite();
//	ft_init_map(data);
//	ft_init_user();
//	ft_init_sounds();
return (0);
}

int		ft_init_game(t_game *game)
{
	ft_init_data(&game->data);
	game->sprite = NULL;

	return (SUCCESS);
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
	printf("x=%d y=%d\n", data->player_pos_x, data->player_pos_y);
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
			while (ft_isspace(data->map[x][y]))
				y++;
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

//	printf("%d total\n", data->nb_lines);
	x = data->nb_lines;
//	y = ft_strlen(data->map[x]);
	y = 0;
	while (ft_isspace(data->map[x][y]))
		y++;
	while (data->map[x][y] != '\0')
	{
		if (ft_is_not_wall(data->map[x][y]))// || (!(ft_isspace(data->map[x][y]))))
			return (ft_error(MISSING_WALL));
		if (ft_isspace(data->map[x][y]))
		{
//				ft_check_border_inside(data, x, y);
		}
		y++;
	}
	return (SUCCESS);
}

int		ft_check_border_left(t_data *data, int x, int y, int len)
{
	while (y <= len)
	{
		while (ft_isspace(data->map[x][y]))
			y++;
		if (ft_is_not_wall(data->map[x][y]))
		{
			if (data->map[x][y - 2] == '1')
				break;
			if (data->map[x][y - 1] != '1')
			{
				ft_putstr_fd("map non fermee first ", 1);
				return (ERROR);
			}
			if (data->map[x - 1][y - 1] != '1')
			{
				ft_putstr_fd("map non fermee top ", 1);
				return (ERROR);
			}
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
			{
				ft_putstr_fd("map non fermee last ", 1);
				return (ERROR);
			}
			if (data->map[x - 1][y + 1] != '1')
			{
				ft_putstr_fd("map non fermee toplst ", 1);
				return (ERROR);
			}
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
	static int i = 0;
	int j;
	int len;

	j = 0;
	len = ft_strlen(line);
	data->map[i] = NULL;
	if (!(data->map[i] = (char*)malloc(sizeof(char) * data->max_len + 1)))
		return (ERROR);
	while (line[j] != '\0')
	{
		data->map[i][j] = line[j];
		j++;
	}
	data->map[i][j] = '\0';
	i++;
	return (SUCCESS);
}

int		ft_parse_info_map(t_data *data, char *line)
{
	if (ft_check_char(data, line) == ERROR)
		return (ft_error(WRONG_CHAR));
//	if (data->nb_total_lines == data->start_map)
//		if (ft_check_border_top_bottom(data, line) != SUCCESS)
//			return (ERROR);
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
	if (!(data->map = (char**)malloc(sizeof(char*) * data->nb_lines)))
		return (ft_error(MALLOC_ERR));
	data->nb_total_lines = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		data->nb_total_lines += 1;
		if (data->nb_total_lines >= data->start_map)
		{
			if (ft_check_empty_line(data, line) == ERROR)
				return (ft_error(EMPTY_LINE));
			while (ft_isspace(line[i]))
				i++;
			if (line[i] == '1' || line[i] == '0')
			{
				if (ft_get_map(data, line) != SUCCESS)
					return (ft_error(MALLOC_ERR));
			}
		}
	}
	if (ft_check_border(data) != SUCCESS)
		return (ERROR);
	if (ft_check_map_size(data) != SUCCESS)
		return (ERROR);
	if (ft_check_wall(data) != SUCCESS)
		return (ERROR);
	if (ft_check_player(data) != SUCCESS)
		return (ERROR);
	ft_fill_spaces(data);
	close(fd);
	return (SUCCESS);
}

int		ft_parse_line(t_data *data, char *line)
{
	int		len;
	int		i;

	len = 0;
	i = 0;
	len = ft_strlen(line);
	data->nb_total_lines += 1;
	ft_check_config(data);
	if (line[i] == '\n' || line[i] == '\0' || len == 0)
		return (SUCCESS);
	else if (line[0] == 'R' && line[i + 1] == ' ')
		ft_get_res(data, line);
	else if (line[0] == 'N' && line[i + 1] == 'O')
		data->north = 1;
	else if (line[0] == 'S' && line[i + 1] == 'O')
		data->south = 1;
	else if (line[0] == 'W' && line[i + 1] == 'E')
		data->west = 1;
	else if (line[0] == 'E' && line[i + 1] == 'A')
		data->east = 1;
	else if (line[0] == 'S' && line[i + 1] == ' ')
		data->sprite = 1;
	else if (line[0] == 'F' && line[i + 1] == ' ')
		data->ground = 1;
	else if (line[0] == 'C' && line[i + 1] == ' ')
		data->ceiling = 1;
	else if (data->start_map == 0 && data->config_done == 1)
	{
		if (ft_check_char_first_line(data, line) == ERROR)
			return (ERROR);
		if (ft_start_map(data, line) == ERROR)
			return (ERROR);
	}
	else if (data->start_map != 0 && data->nb_total_lines >= data->start_map)
	{
		while (ft_isspace(line[i]))
			i++;
		if (!(ft_isspace(line[i])))
		{
			if (ft_parse_info_map(data, line) != SUCCESS)
				return (ERROR);
		}
	}
	return (SUCCESS);
}


int		ft_parse_arg(int argc, char **argv, t_data *data)
{
	int			fd;
	int			ret;
	char		*line;
	t_data		*map_buff;

	ret = 1;
	if ((fd = open(argv[1], O_RDWR)) < 0)
		return (ERROR);
	while ((ret =  get_next_line(fd, &line)) > 0)
	{
		if (ft_parse_line(data, line) != SUCCESS)
			return (ERROR);
		free(line);
	}
	close(fd);
	if (ft_parse_map(data, argv[1]) != SUCCESS)
		return (ERROR);
	int i = 0;
	while (i <= data->nb_lines)
	{
		printf("%s\n", data->map[i]);
		i++;
	}
	printf("\n %d", data->start_map);
	return (SUCCESS);
}

int		main(int argc, char **argv)
{
	t_game		game;

	if (ft_check_arg(argc, argv) != SUCCESS)
		return (ERROR);
	ft_init_game(&game);
	if (ft_parse_arg(argc, argv, &game.data) != SUCCESS)
		return (ERROR);
//	mlx_loop(game);
	return (0);
}
