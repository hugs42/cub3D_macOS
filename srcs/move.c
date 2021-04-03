/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 09:08:34 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/03 12:18:30 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

void	ft_move_forward(t_data *data, t_player *player)
{
	if (data->map[(int)(player->pos_x + player->dir_x * player->move_speed)]
	[(int)(player->pos_y)] == '0')
		player->pos_x += player->dir_x * player->move_speed;
	if (data->map[(int)(player->pos_x)][(int)(player->pos_y + player->dir_y *
	player->move_speed)] == '0')
		player->pos_y += player->dir_y * player->move_speed;
}

void	ft_move_backward(t_data *data, t_player *player)
{
	if (data->map[(int)(player->pos_x - player->dir_x * player->move_speed)]
	[(int)(player->pos_y)] == '0')
		player->pos_x -= player->dir_x * player->move_speed;
	if (data->map[(int)(player->pos_x)][(int)(player->pos_y + player->dir_y *
	player->move_speed)] == '0')
		player->pos_y -= player->dir_y * player->move_speed;
}

void	ft_move_right(t_data *data, t_player *player)
{
	if (data->map[(int)(player->pos_x + player->plan_x *
	player->move_speed)][(int)(player->pos_y)] == '0')
		player->pos_x += player->plan_x * player->move_speed;
	if (data->map[(int)(player->pos_x)][(int)(player->pos_y + player->plan_y *
	player->move_speed)] == '0')
		player->pos_y += player->plan_y * player->move_speed;
}

void	ft_move_left(t_data *data, t_player *player)
{
	if (data->map[(int)(player->pos_x - player->plan_x *
	player->move_speed)][(int)(player->pos_y)] == '0')
		player->pos_x += -(player->plan_x * player->move_speed);
	if (data->map[(int)(player->pos_x)][(int)(player->pos_y - player->plan_y *
	player->move_speed)] == '0')
		player->pos_y += -(player->plan_y * player->move_speed);
}
