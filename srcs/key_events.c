
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
	{
		ft_putstr_fd("z ", 1);
		game->event->forward = 1;
	}
	else if (key == KEY_BACK)
	{
		ft_putstr_fd("s ", 1);
		game->event->back = 1;
	}
	else if (key == KEY_RIGHT)
	{
		ft_putstr_fd("d ", 1);
		game->event->right = 1;
	}
	else if (key == KEY_LEFT)
	{
		ft_putstr_fd("q ", 1);
		game->event->left = 1;
	}
	else if (key == KEY_RIGHT_ROT)
	{
		ft_putstr_fd("-> ", 1);
		game->event->right_rot = 1;
	}
	else if (key == KEY_LEFT_ROT)
	{
		ft_putstr_fd("<- ", 1);
		game->event->left_rot = 1;
	}
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

void	set_position(t_game *game, double pos_x, double pos_y)
{
	game->player->pos_x += pos_x;
	game->player->pos_y += pos_y;
}


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
	if (data->map[(int)player->pos_x][(int)(player->pos_y + player->dir_x *
	player->move_speed)] == '0')
		player->pos_y -= player->dir_y * player->move_speed;
	if (data->map[(int)(player->pos_x)][(int)(player->pos_y + player->dir_y *
	player->move_speed)] == '0')
		player->pos_x -= player->dir_y * player->move_speed;
}

void	ft_move_left(t_data *data, t_player *player)
{
	if (data->map[(int)(player->pos_x + player->dir_x * player->move_speed)]
	[(int)(player->pos_y)] == '0')
		player->pos_x += player->dir_y * player->move_speed;
	if (data->map[(int)(player->pos_x)][(int)(player->pos_y + player->dir_y *
	player->move_speed)] == '0')
		player->pos_y += player->dir_y * player->move_speed;
}

void	ft_rot_right(t_player *player)
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

void	ft_rot_left(t_player *player)
{
	double		old_dir_x;
	double		old_plan_x;

	old_dir_x = player->dir_x;
	old_plan_x = player->plan_x;
	player->dir_x = player->dir_x * cos(-player->rot_speed) - player->dir_y *
	sin(-player->rot_speed);
	player->dir_y = old_dir_x * sin(-player->rot_speed) + player->dir_y *
	cos(-player->rot_speed);
	player->plan_x = player->plan_x * cos(-player->rot_speed) - player->plan_y *
	sin(-player->rot_speed);
	player->plan_y = old_plan_x * sin(-player->rot_speed) + player->plan_y *
	cos(-player->rot_speed);
}

int		ft_key_events(t_game *game)
{
	if (game->event->forward == 1)
		ft_move_forward(&game->data, game->player);
	else if (game->event->back == 1)
		ft_move_backward(&game->data, game->player);
	else if (game->event->right == 1)
		ft_move_right(&game->data, game->player);
	else if (game->event->left == 1)
		ft_move_left(&game->data, game->player);
	else if (game->event->right_rot == 1)
		ft_rot_right(game->player);
	else if (game->event->left_rot == 1)
		ft_rot_left(game->player);
	return (0);
}

int		ft_exit(t_game *game)
{

	exit(0);
}
