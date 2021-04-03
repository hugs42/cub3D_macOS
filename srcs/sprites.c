/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 13:42:35 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/03 13:57:04 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_order_sprite(t_game *game, t_data *data, t_spr *spr)
{
	int			i;
	int			j;
	double		tmp;

	i = 0;
	while (i < data->sprite_nb)
	{
		j = 0;
		while (j < data->sprite_nb - 1)
		{
			if (spr->distance[j] < spr->distance[j + 1])
			{
				tmp = spr->distance[j];
				spr->distance[j] = spr->distance[j + 1];
				spr->distance[j + 1] = tmp;
				tmp = spr->order[j];
				spr->order[j] = spr->order[j + 1];
				spr->order[j + 1] = (int)tmp;
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int		ft_sort_sprites(t_game *game, t_data *data, t_spr *spr, t_s *s)
{
	int i;

	i = 0;
	spr->order = ft_calloc(game->data.sprite_nb + 1, sizeof(int));
	spr->distance = ft_calloc(game->data.sprite_nb + 1, sizeof(double));
	while (i <= data->sprite_nb)
	{
		spr->order[i] = i;
		spr->distance[i] = ((game->player->pos_x - s[i].x) *
		(game->player->pos_x - s[i].x) + (game->player->pos_y - s[i].y) *
		(game->player->pos_y - s[i].y));
		i++;
	}
	ft_order_sprite(game, data, spr);
	return (SUCCESS);
}

int		ft_calc_sprite(int i, t_game *game, t_spr *spr, t_s *s)
{
	spr->sprite_x = s[spr->order[i]].x - game->player->pos_x;
	spr->sprite_y = s[spr->order[i]].y - game->player->pos_y;
	spr->invdet = 1.0 / (game->player->plan_x * game->player->dir_y -
	game->player->dir_x * game->player->plan_y);
	spr->transform_x = spr->invdet * (game->player->dir_y * spr->sprite_x -
	game->player->dir_x * spr->sprite_y);
	spr->transform_y = spr->invdet * (-game->player->plan_y * spr->sprite_x +
	game->player->plan_x * spr->sprite_y);
	spr->sprite_screen_x = (int)(game->data.screen_w / 2) *
	(1 + spr->transform_x / spr->transform_y);
	spr->sprite_height = abs((int)(game->data.screen_h / spr->transform_y));
	return (SUCCESS);
}

int		ft_calc_sprite_2(t_game *game, t_spr *spr, t_s *s)
{
	spr->draw_start_y = -spr->sprite_height / 2 + game->data.screen_h / 2;
	spr->draw_end_y = spr->sprite_height / 2 + game->data.screen_h / 2;
	if (spr->draw_start_y < 0)
		spr->draw_start_y = 0;
	if (spr->draw_end_y >= game->data.screen_h)
		spr->draw_end_y = game->data.screen_h - 1;
	spr->sprite_width = abs((int)(game->data.screen_h / spr->transform_y));
	spr->draw_start_x = -spr->sprite_width / 2 + spr->sprite_screen_x;
	if (spr->draw_start_x < 0)
		spr->draw_start_x = 0;
	spr->draw_end_x = spr->sprite_width / 2 + spr->sprite_screen_x;
	return (SUCCESS);
}

int		ft_sprite(t_game *game, t_spr *spr, t_s *s)
{
	int i;

	i = 0;
	ft_sort_sprites(game, &game->data, spr, game->spr->s);
	while (i < game->data.sprite_nb)
	{
		ft_calc_sprite(i, game, spr, s);
		ft_calc_sprite_2(game, spr, s);
		ft_draw_sprite(game, spr);
		i++;
	}
	return (SUCCESS);
}
