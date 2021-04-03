/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 15:16:35 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/03 15:26:15 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_check_first_space(t_data *data)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < data->nb_lines)
	{
		y = 0;
		while (data->map[x][y] != '\0')
		{
			if (ft_is_not_wall(data->map[x][y]))
			{
				data->first_space_x = x;
				return (SUCCESS);
			}
			y++;
		}
		x++;
	}
	return (ERROR);
}

int		ft_check_empty_line(t_data *data, char *line)
{
	int i;
	int y;

	i = 0;
	y = 0;
	if (ft_strlen(line) == 0)
		return (ERROR);
	while (line[i] != '\0')
	{
		if (ft_strchr(line, '1') == NULL && (ft_strchr(line, '0') == NULL))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int		ft_start_map(t_data *data, char *line)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(line);
	while (line[i] != '\0')
	{
		if (line[i] == '1' || ft_isspace(line[i]))
			i++;
		else if (line[i] == '0')
			return (ft_error(MISSING_WALL));
		else
			return (0);
	}
	if (i == len)
		data->start_map = data->nb_total_lines;
	return (SUCCESS);
}

int		ft_check_char_first_line(t_data *data, char *line)
{
	int len;

	len = 0;
	while (line[len] != '\0')
	{
		if (line[len] == '1' || line[len] == ' ' || line[len] == '\n' ||
		line[len] == '\t')
			len++;
		else if (ft_is_not_wall(line[len]))
			return (ft_error(MISSING_WALL));
		else
			return (ft_error(WRONG_CHAR));
	}
	return (SUCCESS);
}

int		ft_check_char(t_data *data, char *line)
{
	int			len;
	static int	i = 0;

	i++;
	len = 0;
	data->nb_lines++;
	while (line[len] != '\0')
	{
		if (line[len] == '0' || line[len] == '1' || line[len] == ' ' ||
		line[len] == '\n' || line[len] == '2' || line[len] == 'N' || line[len]
		== 'S' || line[len] == 'E' || line[len] == 'W' || line[len] == '\t')
			len++;
		else
			return (ERROR);
	}
	data->len = len;
	return (SUCCESS);
}
