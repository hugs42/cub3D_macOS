/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 13:41:07 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/03 15:15:04 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_check_map_size(t_data *data)
{
	int count;

	data->x = 0;
	data->y = 0;
	count = 0;
	if (data->nb_lines < 2)
		return (ft_error(SMALL_MAP));
	ft_check_first_space(data);
	data->x = data->first_space_x - 1;
	data->z = data->first_space_x + 1;
	while (data->x <= data->z)
	{
		data->y = 0;
		count = 0;
		while (data->map[data->x][data->y] != '\0')
		{
			if (!(ft_isspace(data->map[data->x][data->y])))
				count++;
			data->y++;
		}
		if (count < 3)
			return (ft_error(SMALL_MAP));
		data->x++;
	}
	return (SUCCESS);
}

int		ft_check_player(t_data *data)
{
	static int		x;
	int				y;

	y = 0;
	while (x <= data->nb_lines)
	{
		y = 0;
		while (data->map[x][y] != '\0')
		{
			if (data->map[x][y] == 'N' || data->map[x][y] == 'S' ||
			data->map[x][y] == 'E' || data->map[x][y] == 'W')
			{
				data->is_player++;
				ft_get_player(data, x, y);
			}
			y++;
		}
		x++;
	}
	if (data->is_player == 0 || data->is_player > 1)
		return (ft_error(ERR_PLAYER));
	return (SUCCESS);
}

int		ft_check_wall(t_data *data)
{
	static int	x;
	int			y;

	x = 0;
	y = 0;
	while (x <= data->nb_lines)
	{
		y = 0;
		while (data->map[x][y] != '\0')
		{
			y = ft_skip_spaces2(data, x, y);
			if (ft_is_not_wall(data->map[x][y]))
				if (ft_check_neighborhood(data, x, y) != SUCCESS)
					return (ft_error(MISSING_WALL));
			y++;
		}
		x++;
	}
	return (SUCCESS);
}

int		ft_check_border_bottom(t_data *data)
{
	int x;
	int y;

	x = data->nb_lines;
	y = 0;
	y = ft_skip_spaces2(data, x, y);
	while (data->map[x][y] != '\0')
	{
		if (ft_is_not_wall(data->map[x][y]))
			return (ft_error(MISSING_WALL));
		y++;
	}
	return (SUCCESS);
}

int		ft_check_border(t_data *data)
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
		x++;
	}
	x = 0;
	while (x <= data->nb_lines)
	{
		y = ft_strlen(data->map[x]);
		x++;
	}
	ft_check_border_bottom(data);
	return (SUCCESS);
}
