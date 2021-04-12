/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 10:19:26 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/10 11:24:20 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

void	ft_get_player(t_data *data, int x, int y)
{
	if (data->map[x][y] == 'N')
		data->player_dir = NORTH;
	else if (data->map[x][y] == 'S')
		data->player_dir = SOUTH;
	else if (data->map[x][y] == 'E')
		data->player_dir = EAST;
	else if (data->map[x][y] == 'W')
		data->player_dir = WEST;
	data->player_pos_x = x;
	data->player_pos_y = y;
}

void	ft_pos_north_south(t_player *player, t_data *data)
{
	player->dir_y = 0;
	player->plan_x = 0;
	player->pos_y += 0.5;
	if (data->player_dir == NORTH)
	{
		player->dir_x = -1;
		player->plan_y = 0.66;
	}
	else
	{
		player->dir_x = 1;
		player->plan_y = -0.66;
	}
}

void	ft_pos_east_west(t_player *player, t_data *data)
{
	player->dir_x = 0;
	player->plan_y = 0;
	player->pos_x += 0.5;
	if (data->player_dir == EAST)
	{
		player->dir_y = -1;
		player->plan_x = -0.66;
	}
	else
	{
		player->dir_y = -1;
		player->plan_x = 0.66;
	}
}

int		ft_setup_player(t_player *player, t_data *data)
{
	player->pos_x = data->player_pos_x;
	player->pos_y = data->player_pos_y;
	player->move_speed = 0.05;
	player->rot_speed = 0.04;
	if (data->player_dir == WEST || data->player_dir == EAST)
		ft_pos_east_west(player, data);
	else if (data->player_dir == NORTH || data->player_dir == SOUTH)
		ft_pos_north_south(player, data);
	return (0);
}
