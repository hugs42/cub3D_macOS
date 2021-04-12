/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 18:46:38 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/12 15:33:09 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_copy_path(t_data *data, char *line, int i, int j)
{
	int len;

	len = ft_strlen(line);
	if (line[len - 1] == ' ')
		while (line[len - 1] == ' ')
			len--;
	data->path = ft_calloc(len - i + 1, sizeof(char));
	if (line[i] == '.' && line[i + 1] == '/')
	{
		while (i < len)
		{
			data->path[j] = line[i];
			i++;
			j++;
		}
		data->path[j] = '\0';
	}
	return (0);
}

int		ft_get_path(t_data *data, char *line, int i)
{
	int j;

	j = 0;
	i += 2;
	while (ft_isspace(line[i]))
		i++;
	ft_copy_path(data, line, i, j);
	i = 0;
	if (ft_strlen(data->path) == 0)
		return (ERROR);
	while (data->path[i] != '\0')
	{
		if (ft_isspace(data->path[i]))
			return (ERROR);
		i++;
	}
	if (ft_check_tex_ext(data->path) == ERROR)
		ft_error(XPM_ERR);
	return (0);
}
