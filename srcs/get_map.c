/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 13:09:54 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/05 14:21:46 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

void	ft_replace_spaces_2(t_data *data, int x, int len)
{
	int y;

	y = 0;
	while (y <= len)
	{
		if (ft_isspace(data->map[x][y]))
			data->map[x][y] = '1';
		if (ft_is_player(data->map[x][y]))
			data->map[x][y] = '0';
		y++;
	}
}

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
		ft_replace_spaces_2(data, x, len);
		if (len < data->max_len)
		{
			while (len < data->max_len)
			{
				data->map[x][len] = '1';
				len++;
			}
			data->map[x][len] = '\0';
		}
		x++;
	}
}

int		ft_copy_map(t_data *data, char *line)
{
	static int	x = 0;
	int			y;
	int			y1;

	y = 0;
	y1 = 0;
	data->map[x] = ft_calloc(data->max_len + 1, sizeof(char));
	while (line[y1] != '\0')
	{
		if (line[y1] == '2')
			data->sprite_nb++;
		data->map[x][y] = line[y1];
		y++;
		y1++;
	}
	data->map[x][y] = '\0';
	x++;
	return (SUCCESS);
}

int		ft_get_map(t_data *data, char *line)
{
	int fd;
	int i;
	int ret;

	i = 0;
	ret = 1;
	fd = open(line, O_RDONLY);
	data->map = ft_calloc(data->nb_lines + 1, sizeof(char*));
	data->nb_total_lines = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		data->nb_total_lines++;
		if (data->nb_total_lines >= data->start_map)
		{
			if (ft_check_empty_line(data, line) == ERROR)
				return (ft_error(EMPTY_LINE));
			i = ft_skip_spaces(line, i);
			ft_copy_map(data, line);
			free(line);
		}
	}
	close(fd);
	return (SUCCESS);
}