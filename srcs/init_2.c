/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 10:48:42 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/03 12:45:43 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_init_img(t_game *game)
{
	game->img = ft_calloc(1, sizeof(t_img));
	game->img->img_ptr = NULL;
	game->img->addr = NULL;
	game->img->size_l = 0;
	game->img->bpp = 0;
	game->img->endian = 0;
	game->img->width = 0;
	game->img->height = 0;
	return (SUCCESS);
}

int		ft_init_mlx(t_game *game)
{
	game->mlx = ft_calloc(1, sizeof(t_mlx));
	game->mlx->mlx_ptr = NULL;
	game->mlx->win = NULL;
	return (0);
}

int		ft_init_event(t_game *game)
{
	game->event = ft_calloc(1, sizeof(t_event));
	game->event->forward = 0;
	game->event->back = 0;
	game->event->right = 0;
	game->event->left = 0;
	game->event->right_rot = 0;
	game->event->left_rot = 0;
	game->event->exit = 0;
	return (0);
}

int		ft_init_player(t_game *game)
{
	game->player = ft_calloc(1, sizeof(t_player));
	game->player->pos_x = 0;
	game->player->pos_y = 0;
	game->player->dir_x = 0;
	game->player->dir_y = 0;
	game->player->move_speed = 0;
	game->player->rot_speed = 0;
	return (0);
}

int		ft_init_sprites(t_spr *spr)
{
	spr->sprite_x = 0;
	spr->sprite_y = 0;
	spr->invdet = 0;
	spr->transform_x = 0;
	spr->transform_y = 0;
	spr->sprite_screen_x = 0;
	spr->sprite_height = 0;
	spr->sprite_width = 0;
	spr->draw_start_x = 0;
	spr->draw_start_y = 0;
	spr->draw_end_x = 0;
	spr->draw_end_y = 0;
	spr->distance = NULL;
	spr->order = NULL;
	spr->s->x = 0;
	spr->s->y = 0;
	return (SUCCESS);
}
