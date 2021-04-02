/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 13:42:35 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/02 14:00:40 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_order_sprite(t_game *game, t_data *data, t_sprites *sprites)
{
	int			i;
	int			j;
	double		tmp;

	i = 0;
	j = 0;
	while (i < data->sprite_nb)
	{
		j  = 0;
		while (j < data->sprite_nb - 1)
		{
			if (sprites->distance[j] < sprites->distance[j + 1])
			{
				tmp = sprites->distance[j];
				sprites->distance[j] = sprites->distance[j + 1];
				sprites->distance[j + 1] = tmp;
				tmp = sprites->order[j];
				sprites->order[j] = sprites->order[j + 1];
				sprites->order[j + 1] = (int)tmp;
			}
			j++;
		}
		i++;

	}
	return (SUCCESS);
}

int		ft_sort_sprites(t_game *game, t_data *data, t_sprites *sprites, t_sprite *sprite)
{
	int i;

	i = 0;
	sprites->order = ft_calloc(game->data.sprite_nb + 1, sizeof(int));
	sprites->distance = ft_calloc(game->data.sprite_nb + 1, sizeof(double));
	while (i <= data->sprite_nb)
	{
		sprites->order[i] = i;
		sprites->distance[i] = ((game->player->pos_x - sprite[i].x) * (game->player->pos_x - sprite[i].x) + (game->player->pos_y - sprite[i].y) * (game->player->pos_y - sprite[i].y));
		i++;
	}
	ft_order_sprite(game, data, sprites);
	return (SUCCESS);
}

int		ft_sprite(t_game *game, t_sprites *sprites, t_sprite *sprite)
{
	int i;

	i = 0;

	ft_sort_sprites(game, &game->data, sprites, game->sprites->sprite);
	while (i < game->data.sprite_nb)
	{
		sprites->sprite_x = sprite[sprites->order[i]].x - game->player->pos_x;
		sprites->sprite_y = sprite[sprites->order[i]].y - game->player->pos_y;

		sprites->invdet = 1.0 / (game->player->plan_x * game->player->dir_y - game->player->dir_x * game->player->plan_y);

		sprites->transform_x = sprites->invdet * (game->player->dir_y * sprites->sprite_x - game->player->dir_x * sprites->sprite_y);
		sprites->transform_y = sprites->invdet * (-game->player->plan_y * sprites->sprite_x + game->player->plan_x * sprites->sprite_y);

		sprites->sprite_screen_x = (int)(game->data.screen_w / 2) * (1 + sprites->transform_x / sprites->transform_y);
		sprites->sprite_height = abs((int)(game->data.screen_h / sprites->transform_y));
		sprites->draw_start_y = -sprites->sprite_height / 2 + game->data.screen_h / 2;
		if (sprites->draw_start_y < 0)
			sprites->draw_start_y = 0;
		sprites->draw_end_y = sprites->sprite_height / 2 + game->data.screen_h / 2;
		if (sprites->draw_end_y >= game->data.screen_h)
			sprites->draw_end_y = game->data.screen_h - 1;
		sprites->sprite_width = abs((int)(game->data.screen_h / sprites->transform_y));
		sprites->draw_start_x = -sprites->sprite_width / 2 + sprites->sprite_screen_x;
		if (sprites->draw_start_x < 0)
			sprites->draw_start_x = 0;
		sprites->draw_end_x = sprites->sprite_width / 2 + sprites->sprite_screen_x;
		ft_draw_sprite(game, sprites);
		i++;
	}
	return (SUCCESS);
}
