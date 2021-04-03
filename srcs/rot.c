/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 10:19:57 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/03 10:21:18 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

void	ft_rot_right(t_player *player)
{
	double		old_dir_x;
	double		old_plan_x;

	old_dir_x = player->dir_x;
	old_plan_x = player->plan_x;
	player->dir_x = player->dir_x * cos(-player->rot_speed) - player->dir_y *
	sin(-player->rot_speed);
	player->dir_y = old_dir_x * sin(-player->rot_speed) + player->dir_y *
	cos(-player->rot_speed);
	player->plan_x = player->plan_x * cos(player->rot_speed) - player->plan_y *
	sin(-player->rot_speed);
	player->plan_y = old_plan_x * sin(-player->rot_speed) + player->plan_y *
	cos(-player->rot_speed);
}

void	ft_rot_left(t_player *player)
{
	double		old_dir_x;
	double		old_plan_x;

	old_dir_x = player->dir_x;
	old_plan_x = player->plan_x;
	player->dir_x = player->dir_x * cos(player->rot_speed) - player->dir_y *
	sin(player->rot_speed);
	player->dir_y = old_dir_x * sin(player->rot_speed) + player->dir_y *
	cos(player->rot_speed);
	player->plan_x = player->plan_x * cos(player->rot_speed) - player->plan_y *
	sin(player->rot_speed);
	player->plan_y = old_plan_x * sin(player->rot_speed) + player->plan_y *
	cos(player->rot_speed);
}
