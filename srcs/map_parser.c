/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 19:06:49 by hugsbord          #+#    #+#             */
/*   Updated: 2021/03/26 11:44:52 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_copy_map(t_data *data, char *line)
{
	static int	x = 0;
	int			y;
	int			y1;

	y = 0;
	y1 = 0;
	data->map[x] = NULL;
	if (!(data->map[x] = (char*)malloc(sizeof(char) * data->max_len + 1)))
		return (ERROR);
	while (line[y1] != '\0')
	{
		if (line[y1] == ' ')
			while (line[y1] == ' ')
				y1++;
		data->map[x][y] = line[y1];
		y++;
		y1++;
	}
	data->map[x][y] = '\0';
	x++;
	return (SUCCESS);
}

/*int		ft_copy_map(t_data *data, char *line)
{
	static int	x = 0;
	int			y;
	int			y1;

	y = 0;
	y1 = ft_strlen(line);;
	data->map[x] = NULL;
	if (!(data->map[x] = (char*)malloc(sizeof(char) * data->max_len + 1)))
		return (ERROR);
	while (line[y1] >= line[0])
	{
		if (line[y1] == ' ')
			while (line[y1] == ' ')
				y1--;
		data->map[x][y] = line[y1];
		y++;
		y1--;
	}
	data->map[x][y] = '\0';
	x++;
	return (SUCCESS);
}*/


int		ft_get_map(t_data *data, char *line)
{
	int fd;
	int i;
	int ret;

	i = 0;
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
			if (ft_copy_map(data, line) != SUCCESS)
				return (ft_error(MALLOC_ERR));
		}
	}
	close(fd);
	return (SUCCESS);
}

int		ft_parse_map(t_data *data, char *line)
{
	if (ft_get_map(data, line) != SUCCESS)
		return (ERROR);
	if (ft_check_map_size(data) != SUCCESS)
		return (ERROR);
	if (ft_check_border(data) != SUCCESS)
		return (ERROR);
	if (ft_check_wall(data) != SUCCESS)
		return (ERROR);
	if (ft_check_player(data) != SUCCESS)
		return (ERROR);
	ft_replace_spaces(data);
	return (SUCCESS);
}
