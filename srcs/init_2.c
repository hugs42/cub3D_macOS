/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 10:48:42 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/01 12:09:40 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_init_img2(t_game *game)
{
	if (!(game->img2 = (t_img *)malloc(sizeof(t_img))))
		return (ERROR);
	game->img2->img_ptr = NULL;
	game->img2->addr = NULL;
	game->img2->size_l = 0;
	game->img2->bpp = 0;
	game->img2->endian = 0;
	game->img2->width = 0;
	game->img2->height = 0;
	return (SUCCESS);
}


int		ft_init_img(t_game *game)
{
	if (!(game->img = (t_img *)malloc(sizeof(t_img))))
		return (ERROR);
	game->img->img_ptr = NULL;
	game->img->addr = NULL;
	game->img->size_l = 0;
	game->img->bpp = 0;
	game->img->endian = 0;
	game->img->width = 0;
	game->img->height = 0;
	ft_init_img2(game);
	return (SUCCESS);
}

int		ft_init_mlx(t_game *game)
{
	if (!(game->mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		return (ERROR);
	game->mlx->mlx_ptr = NULL;
	game->mlx->win = NULL;
	return (0);
}

int		ft_init_event(t_game *game)
{
	if (!(game->event = (t_event *)malloc(sizeof(t_event))))
		return (ERROR);
	game->event->forward = 0;
	game->event->back = 0;
	game->event->right = 0;
	game->event->left = 0;
	game->event->right_rot = 0;
	game->event->left_rot = 0;
	return (0);
}

int		ft_init_player(t_game *game)
{
	if (!(game->player = (t_player *)malloc(sizeof(t_player))))
		return (ERROR);
	game->player->pos_x = 0;
	game->player->pos_y = 0;
	game->player->dir_x = 0;
	game->player->dir_y = 0;
	game->player->move_speed = 0;
	game->player->rot_speed = 0;
	return (0);
}
