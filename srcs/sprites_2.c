/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:58:24 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/02 15:02:49 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_draw_sprite(t_game *game, t_spr *spr)
{
	int		i;
	int		d;
	int		stripe;
	int		tex_x;
	int		tex_y;
	int		color;
	int		tmp;

	tex_x = 0;
	tex_y = 0;
	i = -1;
	d = 0;
	color = 0;
	stripe = spr->draw_start_x;
	while (stripe < spr->draw_end_x)
	{
		tex_x = (int)(256 * (stripe - (-spr->sprite_width / 2 +
		spr->sprite_screen_x)) * game->tex[4].width / spr->sprite_width) / 256;
		if (spr->transform_y > 0 && stripe >= 0 && stripe < game->data.screen_w
		&& spr->transform_y < game->z_buffer[stripe])
		{
			i = spr->draw_start_y;
			while (i < spr->draw_end_y)
			{
				d = (i) * 256 - game->data.screen_h * 128 + spr->sprite_height * 128;
				tex_y = ((d * game->tex[4].height) / spr->sprite_height) / 256;
				color = game->tex[4].addr[game->tex[4].width * tex_y + tex_x];
				if ((color & 0x00FFFFFF) != 0)
					game->img->addr[i * game->img->size_l / 4 + stripe] = color;
				i++;
			}
		}
		stripe++;
	}
	return (SUCCESS);
}

int		ft_setup_sprites(t_game *game, t_data *data)
{
	int			x;
	int			y;
	int			i;

	x = 0;
	y = 0;
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
