/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: s72h <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 14:26:27 by s72h              #+#    #+#             */
/*   Updated: 2021/01/13 13:01:41 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"
#include <mlx.h>

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
	printf("OK\n");
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

int		ft_parse_line(t_data *data, char *line)
{
	int		len;
	int		i;

	len = 0;
	i = 0;
	len = ft_strlen(line);
	if (line[0] == '\n' || line[0] == '\0' || len == 0)
		return (SUCCESS);
	else if (line[0] == 'R' && line[1] == ' ')
		ft_get_res(data, line);
	else if (line[0] == 'N' && line[1] == 'O')
		data->north = 1;
	else if (line[0] == 'S' && line[1] == 'O')
		data->south = 1;
	else if (line[0] == 'W' && line[1] == 'E')
		data->west = 1;
	else if (line[0] == 'E' && line[1] == 'A')
		data->east = 1;
	else if (line [0] == 'S' && line[1] == ' ')
		data->sprite = 1;
	else if (line[0] == 'F' && line[1] == ' ')
		data->ground = 1;
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

int		ft_check_ext(char *str)
{
	int		len;
	char	*tmp;

	len = 0;
	len = ft_strlen(str);
	tmp = ft_substr(str, len - 4, len);
	if (!ft_strncmp(tmp, ".cub", 4))
		return (ERROR);
	return (SUCCESS);
}

int		ft_check_arg(int argc, char **argv)
{
	int		id_error;
	char	*type;

	id_error = 0;
	if (argc < 2)
		id_error = 1;
	if (argc > 3)
		id_error = 2;
	if (id_error != 0)// || ft_check_ext(argv[1]) == ERROR)
		return (ERROR);
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
