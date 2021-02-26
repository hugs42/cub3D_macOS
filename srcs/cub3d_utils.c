/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 09:49:03 by hugsbord          #+#    #+#             */
/*   Updated: 2021/02/26 10:12:36 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int			ft_is_not_wall(char c)
{
	if (c == '0' || c == '2' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

void		**ft_calloc_buff(void **buff, int len, int j)
{
	void	**dest;
	int		i;

	i = 0;
	dest = ft_calloc(j + 2, len);
	while (i < j)
	{
		dest[i] = buff[i];
		i++;
	}
	if (j > 0)
		free(buff);
	return (dest);
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
		if (ft_isdigit(line[i]))// || (ft_isspace(line[i])))
		{
			i += ft_get_nb(i, line, data);
			data->is_width = 1;
		}
		else if (ft_isdigit(line[i]) && data->is_width  == 1)
			i += ft_get_nb(i, line, data);
			i++;
		}
	data->res = 1;
	printf("%d\n", data->screen_w);
	printf("%d\n", data->screen_h);
	return (0);
}
