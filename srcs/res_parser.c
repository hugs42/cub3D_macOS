/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   res_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 17:05:06 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/12 14:47:12 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int			ft_get_nb(int i, char *line, t_data *data)
{
	int		j;
	int		k;
	char	*tmp;

	j = 0;
	k = i;
	while (ft_isdigit(line[k]))
		k++;
	if (data->is_width == 1 && data->screen_h != 0)
		return (0);
	tmp = ft_calloc(k - i + 1, sizeof(char));
	while (ft_isdigit(line[i]))
		tmp[j++] = line[i++];
	tmp[j] = '\0';
	if (data->is_width == 0)
		data->screen_w = ft_atoi(tmp);
	else
	{
		data->screen_h = ft_atoi(tmp);
		data->is_height = 1;
	}
	free(tmp);
	return (j);
}

int			ft_parse_res(t_data *data, char *line, int i)
{
	while (line[i])
	{
		if (line[i] == ' ')
			while (line[i] == ' ')
				i++;
		if (ft_isdigit(line[i]))
		{
			i += ft_get_nb(i, line, data);
			data->is_width = 1;
		}
		else if (!(ft_isdigit(line[i]) && line[i] != ' '))
			ft_error(RES_ERR);
		if (data->is_width == 1 && data->is_height == 1)
		{
			while (line[i] != '\0')
				if (line[i++] != ' ')
					ft_error(RES_ERR);
			break ;
		}
		i++;
	}
	return (SUCCESS);
}

int			ft_get_res(t_data *data, char *line)
{
	int		i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == 'R')
		i++;
	ft_parse_res(data, line, i);
	if (data->screen_w <= 0)
		ft_error(RES_ERR);
	if (data->screen_h <= 0)
		ft_error(RES_ERR);
	data->res += 1;
	return (0);
}
