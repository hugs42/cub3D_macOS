/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:58:24 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/06 12:25:36 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_draw_sprite_2(t_game *game, t_spr *spr, int stripe)
{
	int y;
	int d;
	int color;

	d = 0;
	color = 0;
	y = spr->draw_start_y;
	while (y < spr->draw_end_y)
	{
		d = (y) * 256 - game->data.screen_h * 128 + spr->sprite_h * 128;
		spr->tex_y = ((d * game->tex[4].height) / spr->sprite_h) / 256;
		color = game->tex[4].addr[game->tex[4].width * spr->tex_y + spr->tex_x];
		if ((color & 0x00FFFFFF) != 0)
			game->img->addr[y * game->img->size_l / 4 + stripe] = color;
		y++;
	}
	return (SUCCESS);
}

int		ft_draw_sprite(t_game *game, t_spr *spr)
{
	int		stripe;

	stripe = spr->draw_start_x;
	while (stripe < spr->draw_end_x)
	{
		spr->tex_x = (int)(256 * (stripe - (-spr->sprite_w / 2 +
		spr->sprite_screen_x)) * game->tex[4].width / spr->sprite_w) / 256;
		if (spr->transform_y > 0 && stripe >= 0 && stripe < game->data.screen_w
		&& spr->transform_y < game->z_buffer[stripe])
			ft_draw_sprite_2(game, spr, stripe);
		stripe++;
	}
	return (SUCCESS);
}

int		ft_setup_sprites(t_game *game, t_data *data)
{
	int x;
	int y;
	int i;

	x = 0;
	i = 0;
	game->spr = ft_calloc(1, sizeof(t_spr));
	game->spr->s = ft_calloc(game->data.sprite_nb, sizeof(t_s));
	ft_init_sprites(game->spr);
	while (x <= data->nb_lines)
	{
		y = 0;
		while (data->map[x][y] != '\0')
		{
			if (data->map[x][y] == '2')
			{
				game->spr->s[i].x = (double)x + 0.5;
				game->spr->s[i].y = (double)y + 0.5;
				i++;
			}
			y++;
		}
		x++;
	}
	return (SUCCESS);
}
