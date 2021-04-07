/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 11:50:39 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/07 12:55:09 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_check_char_color(char *line, int i, int len)
{
	int		count;

	count = 0;
	while (i < len)
	{
		if (ft_isdigit(line[i]) || line[i] == ',' || ft_isspace(line[i]))
		{
			if (line[i] == ',')
				count++;
			i++;
		}
		else
			return (ERROR);
	}
	if (count != 2)
		return (ERROR);
	return (SUCCESS);
}

int		ft_check_digit(char *line, int i)
{
	int d;

	d = 0;
	while (line[i] != '\0')
	{
		if (ft_isdigit(line[i]))
			d++;
		i++;
	}
	if (d == 0)
		return (ERROR);
	return (SUCCESS);
}

void	ft_free_tmp(char **tmp)
{
	int len;

	len = 0;
	while (tmp[len])
	{
		free(tmp[len]);
		len++;
	}
	free(tmp);
}

int		ft_get_nb_color(t_data *data, char *line, int i)
{
	char	**tmp;

	tmp = ft_split(line + i, ',');
	data->r = ft_atoi(*tmp);
	ft_free_tmp(tmp);
	tmp = NULL;
	while (line[i] != ',')
		i++;
	i++;
	tmp = ft_split(line + i, ',');
	data->g = ft_atoi(*tmp);
	ft_free_tmp(tmp);
	tmp = NULL;
	while (line[i] != ',')
		i++;
	i++;
	tmp = ft_split(line + i, ',');
	if (ft_check_digit(line, i) == ERROR)
		return (ERROR);
	data->b = ft_atoi(*tmp);
	ft_free_tmp(tmp);
	if (data->r > 255 || data->g > 255 || data->b > 255 || data->r < 0 ||
	data->g < 0 || data->b < 0)
		return (ERROR);
	return (SUCCESS);
}

int		ft_get_color(t_data *data, char *line, int i)
{
	int		len;
	int		color;

	len = ft_strlen(line);
	color = 0;
	i++;
	while (ft_isspace(line[i]))
		i++;
	while (ft_isspace(line[len]))
		len--;
	if (ft_check_char_color(line, i, len) == ERROR)
		return (ERROR);
	if (ft_get_nb_color(data, line, i) == ERROR)
		return (ERROR);
	color = (data->r * 256 * 256 + data->g * 256 + data->b);
	if (data->floor == 2)
		data->floor_col = color;
	else if (data->ceiling == 2)
		data->ceiling_col = color;
	return (SUCCESS);
}
