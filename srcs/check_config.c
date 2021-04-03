/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 15:30:41 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/03 15:31:37 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_check_config_double(t_data *data)
{
	if (data->res > 1 || data->north > 1 || data->south > 1 || data->west
	> 1 || data->east > 1 || data->sprite > 1 || data->
	floor > 1 || data->ceiling > 1)
		data->config_double = 1;
	return (0);
}

int		ft_check_config_done(t_data *data)
{
	if (data->res == 1 && data->north == 1 && data->south == 1 && data->west
	== 1 && data->east == 1 && data->south == 1 && data->sprite == 1 && data->
	floor == 1 && data->ceiling == 1)
		data->config_done = 1;
	return (0);
}
