
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:02:43 by hugsbord          #+#    #+#             */
/*   Updated: 2021/03/02 17:03:15 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_press_key(int key, t_game *game)
{
	if (key == KEY_FORWARD)
		game->event.forward = 1;
	else if (key == KEY_BACK)
		game->event.back = 1;
	else if (key == KEY_RIGHT)
		game->event.right = 1;
	else if (key == KEY_LEFT)
		game->event.left = 1;
	else if (key == KEY_RIGHT_ROT)
		game->event.right_rot = 1;
	else if (key == KEY_LEFT_ROT)
		game->event.left_rot = 1;
	return (0);
}

int		ft_release_key(int key, t_game *game)
{
	if (key == KEY_FORWARD)
		game->event.forward = 0;
	else if (key == KEY_BACK)
		game->event.back = 0;
	else if (key == KEY_RIGHT)
		game->event.right = 0;
	else if (key == KEY_LEFT)
		game->event.left = 0;
	else if (key == KEY_RIGHT_ROT)
		game->event.right_rot = 0;
	else if (key == KEY_LEFT_ROT)
		game->event.left_rot = 0;
	return (0);
}

int		ft_key_events(t_game *game)
{
//	if (game->event.forward == 1)
//		ft_move_left(game->player,game->layout);
	
	return (0);
}

int		ft_exit(t_game *game)
{

	exit(0);
}
