/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 09:49:03 by hugsbord          #+#    #+#             */
/*   Updated: 2021/03/12 15:10:22 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int			ft_skip_spaces2(t_data  *data, int x, int y)
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

int			ft_get_nb(int i, char *line,t_data *data)
{
	int		j;
	int		k;
	char	*tmp;

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

	if (data->screen_w == 0)// || data->screen_h == 0)
		return (ft_error(RES_ERR));
	if (data->res == 1)
		if (data->screen_h == 0)// || data->screen_h == 0)
			return (ft_error(RES_ERR));
	if (data->screen_w > 2560)
		data->screen_w = 2560;
	if (data->screen_h > 1440)
		(data->screen_h = 1440);
	return (j);
}

int				ft_get_res(t_data *data, char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		if (line[i] == '-')
			return (ERROR);
		if (ft_isdigit(line[i]))
		{
			i += ft_get_nb(i, line, data);
			data->is_width = 1;
		}
		else if (ft_isdigit(line[i]) && data->is_width  == 1)
			i += ft_get_nb(i, line, data);
			i++;
		}
	data->res = 1;
	return (0);
}
