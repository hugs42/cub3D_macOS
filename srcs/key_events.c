/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:02:43 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/04 10:48:31 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_press_key(int key, t_game *game)
{
	if (key == KEY_FORWARD)
		game->event->forward = 1;
	else if (key == KEY_BACK)
		game->event->back = 1;
	else if (key == KEY_RIGHT)
		game->event->right = 1;
	else if (key == KEY_LEFT)
		game->event->left = 1;
	else if (key == KEY_RIGHT_ROT)
		game->event->right_rot = 1;
	else if (key == KEY_LEFT_ROT)
		game->event->left_rot = 1;
	else if (key == KEY_EXIT)
		game->event->exit = 1;
	return (0);
}

int		ft_release_key(int key, t_game *game)
{
	if (key == KEY_FORWARD)
		game->event->forward = 0;
	else if (key == KEY_BACK)
		game->event->back = 0;
	else if (key == KEY_RIGHT)
		game->event->right = 0;
	else if (key == KEY_LEFT)
		game->event->left = 0;
	else if (key == KEY_RIGHT_ROT)
		game->event->right_rot = 0;
	else if (key == KEY_LEFT_ROT)
		game->event->left_rot = 0;
	return (0);
}

int		ft_key_events(t_game *game)
{
	if (game->event->forward == 1)
		ft_move_forward(&game->data, game->player);
	if (game->event->back == 1)
		ft_move_backward(&game->data, game->player);
	if (game->event->right == 1)
		ft_move_right(&game->data, game->player);
	if (game->event->left == 1)
		ft_move_left(&game->data, game->player);
	if (game->event->right_rot == 1)
		ft_rot_right(game->player);
	if (game->event->left_rot == 1)
		ft_rot_left(game->player);
	if (game->event->exit == 1)
		ft_exit(game);
	return (0);
}

int		ft_exit(t_game *game)
{
	exit(0);
	return (0);
}
