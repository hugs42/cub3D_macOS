/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:36:27 by hugsbord          #+#    #+#             */
/*   Updated: 2021/01/14 19:07:04 by hugsbord         ###   ########.fr       */
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
//	ft_init_textures();
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

int		ft_get_map(t_data *data, char *buff)
{
	t_map	*map;

	return (0);
}

int			ft_get_nb(int i, char *line,t_data *data)
{
	int			j;
	int			k;
	char		*tmp;

	j = 0;
	k = i;
	while (ft_isdigit(line[k]))
		k++;
	if (!(tmp = malloc(sizeof(char) * (k - i + 1))))
		return (-1);
	while (ft_isdigit(line[i]))
	{
		tmp[j] = line[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	if (data->is_width == 0)
		data->screen_w = ft_atoi(tmp);
	else
		data->screen_h = ft_atoi(tmp);
	free(tmp);
	return (j);
}


int		ft_get_res(t_data *data, char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]))// || (ft_isspace(line[i])))
		{
			i += ft_get_nb(i, line, data);
			data->is_width = 1;
		}
		else if (ft_isdigit(line[i]) && data->is_width  == 1)
			i += ft_get_nb(i, line, data);
		i++;
	}
	printf("%d\n", data->screen_w);
	printf("%d\n", data->screen_h);
	return (0);
}


int		ft_parse_map(t_data *data, char *line)
{
	if (ft_check_char(data, line) == ERROR)
	{
		ft_putstr_fd("Error : invalid map\n", 1);
		return (ERROR);
	}
	printf("%s\n", line);
	return (0);
}

int		ft_parse_line(t_data *data, char *line)
{
	int		len;
	int		i;

	len = 0;
	i = 0;
	len = ft_strlen(line);
	if (line[i] == '\n' || line[i] == '\0' || len == 0)
		return (SUCCESS);
	else if (line[i] == 'R' && line[i + 1] == ' ')
		ft_get_res(data, line);
	else if (line[i] == 'N' && line[i + 1] == 'O')
		data->north = 1;
	else if (line[i] == 'S' && line[i + 1] == 'O')
		data->south = 1;
	else if (line[i] == 'W' && line[i + 1] == 'E')
		data->west = 1;
	else if (line[i] == 'E' && line[i + 1] == 'A')
		data->east = 1;
	else if (line [i] == 'S' && line[i + 1] == ' ')
		data->sprite = 1;
	else if (line[i] == 'F' && line[i + 1] == ' ')
		data->ground = 1;
	else if (line[i] == ' ' || line[i] == '1')
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '1')
		{
			if (ft_parse_map(data, line))
				return (ERROR);
		}
	}
//	printf("%s\n", line);
	return (SUCCESS);
}


int		ft_parse_arg(int argc, char **argv, t_data *data)
{
	int			fd;
	int			ret;
	char		*line;

	ret = 1;
	fd = open(argv[1], O_RDWR);
	while ((ret =  get_next_line(fd, &line)) > 0)
	{
//		printf("%s\n", line);
		if (ft_parse_line(data, line) != SUCCESS)
			return (ERROR);
		free(line);
	}
	close(fd);
	return (SUCCESS);
}

int		main(int argc, char **argv)
{
	t_game		game;

	if (ft_check_arg(argc, argv) != SUCCESS)
		return (ERROR);

	ft_init_game(&game);
	ft_parse_arg(argc, argv, &game.data);
//	mlx_loop(game);
	return (0);
}
