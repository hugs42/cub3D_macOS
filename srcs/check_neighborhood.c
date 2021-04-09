/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_neighborhood.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 20:28:37 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/09 17:12:24 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_check_neighborhood_2(t_data *data, int x, int y)
{
	if ((data->map[x - 1][y - 1] != '1') &&
		(!(ft_is_not_wall(data->map[x - 1][y - 1]))))
		return (ERROR);
	if ((data->map[x - 1][y + 1] != '1') &&
		(!(ft_is_not_wall(data->map[x - 1][y + 1]))))
		return (ERROR);
	if ((data->map[x + 1][y - 1] != '1') &&
		(!(ft_is_not_wall(data->map[x + 1][y - 1]))))
		return (ERROR);
	if ((data->map[x + 1][y + 1] != '1') &&
		(!(ft_is_not_wall(data->map[x + 1][y + 1]))))
		return (ERROR);
	return (SUCCESS);
}

int		ft_check_neighborhood(t_data *data, int x, int y)
{
	if ((data->map[x][y - 1] != '1') &&
	(!(ft_is_not_wall(data->map[x][y - 1]))))
		return (ERROR);
	if ((data->map[x][y + 1] != '1') &&
	(!(ft_is_not_wall(data->map[x][y + 1]))))
		return (ERROR);
	if ((data->map[x - 1][y] != '1') &&
	(!(ft_is_not_wall(data->map[x - 1][y]))))
		return (ERROR);
	if ((data->map[x + 1][y] != '1') &&
	(!(ft_is_not_wall(data->map[x + 1][y]))))
		return (ERROR);
	ft_check_neighborhood_2(data, x, y);
	return (SUCCESS);
}
