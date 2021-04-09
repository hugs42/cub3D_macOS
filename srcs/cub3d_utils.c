/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 09:49:03 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/09 17:25:18 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int			ft_skip_spaces2(t_data *data, int x, int y)
{
	while (ft_isspace(data->map[x][y]))
		y++;
	return (y);
}

int			ft_skip_spaces(char *str, int i)
{
	while (ft_isspace(str[i]))
		i++;
	return (i);
}

int			ft_is_not_wall(char c)
{
	if (c == '0' || c == '2' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int			ft_check_wrong_line(t_data *data, char *line, int i)
{
	if ((line[i] != 'R' && line[i + 1] != ' ') && (line[i] != 'R' &&
	line[i + 1] != ' ') && (line[i] != 'S' && line[i + 1] != 'O') &&
	(line[i] != 'N' && line[i + 1] != 'O') && (line[i] != 'E'
	&& line[i + 1] != 'A') && (line[i] != 'W' && line[i + 1] != 'E') &&
	(line[i] != 'S' && line[i + 1] != ' ') && (line[i] != 'C' && line[i + 1]
	!= ' ') && (line[i] != 'F' && line[i + 1] != ' '))
	{
		while (line[i] != '\0')
		{
			if (line[i] != ' ')
				return (ft_error(WRONG_LINE));
		}
	}
	return (0);
}
